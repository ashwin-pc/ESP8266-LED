/**
 * Sets sleeptime based on query params and sets sleepMode to true
 */
void handleTime() {
  int secondsVal = 0;
  float minuteVal = 0;

  if (server.arg("sec") != "") {
    secondsVal = server.arg("sec").toInt();
  }
  if (server.arg("min") != "") {
    secondsVal += 60 * server.arg("min").toInt();
  }
  if (server.arg("hour") != "") {
    secondsVal += 60 * 60 * server.arg("hour").toInt();
  }

  // check if time has been set
  if (secondsVal == 0){     //Parameter not found
    server.sendHeader("Location", String("/") + "#⏱ Timer not set", true);
    server.send ( 302, "text/plain", "");
  } else {     //Parameter found
    sleepMode = true;
    sleepTime = (int)time(nullptr) + secondsVal;   
    server.send ( 200, "application/json", "{\"success\": true, \"msg\": \"⏱ Timer set for : " + String(secondsVal/60) + " minutes..\"}");
  }
}