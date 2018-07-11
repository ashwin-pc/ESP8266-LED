/**
 * WIFI LED Lamp
 * Author: Ashwin P Chandran
 */

#include <time.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>   // Include the SPIFFS library


/**
 * Setup
 * Enter WiFI Credentials
 */
const char *ssid = "Username";
const char *password = "Password";

ESP8266WebServer server ( 80 );

/* Set the GPIO pin connected to the LED */
const int GPIO = 16;

// Global Variables
int dimValue = 0;
int stepSize = 100;
int sleepTime = 0;
bool power = false;
bool sleepMode = false;

/**
 * Handles unknown routes
 */
void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}

	server.send ( 404, "text/plain", message );
}

/**
 * Sets the PWM for the Light based on globally scoped power and dimValue Variables
 */
void setLight() {
  if (power) {
    analogWrite(GPIO, dimValue);
    sleepMode = false;
  } else {
    digitalWrite(GPIO, 1);
  }
}

void setup ( void ) {
  // Setup the Lamp in the OFF state
  pinMode ( GPIO, OUTPUT );
  digitalWrite ( GPIO, 1 );

  // Initiate Serial port for debugging
	Serial.begin ( 115200 );

  // Setup WIFI
	WiFi.mode ( WIFI_STA );
	WiFi.begin ( ssid, password );
	Serial.println ( "" );

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

	if ( MDNS.begin ( "esp8266" ) ) {
		Serial.println ( "MDNS responder started" );
	}

  // Start SPIFFS for serving the Website
  SPIFFS.begin(); 

  // Setup API routes
  server.on ( "/toggle", handleToggle );
  server.on ( "/dimup", handleDimUp );
  server.on ( "/dimdown", handleDimDown );
  server.on ( "/dim", handleDim );
  server.on ( "/time", handleTime );

  // Serve Static files
	server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      handleNotFound();
  });

	server.begin();
	Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  // Perform regular WiFi Actions
	server.handleClient();

  // Check for Sleep mode timeout
  if ((int)time(nullptr) > sleepTime && sleepMode == true) {
    power = false;
    setLight();
  }
}


