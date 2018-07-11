/**
 * Switch power between ON and OFF state
 */
void handleToggle() {
  power = !power;
  setLight();
  server.send ( 200, "application/json", "{\"success\": true, \"msg\": \"💡 Lights turned " + String((power) ? "On" : "Off") + " ..\"}");
}

/**
 * Increment dimValue by stepSize
 */
void handleDimUp() {
  dimValue += stepSize;
  dimValue = (dimValue > 1023) ? 1023 : dimValue;
  setLight();
  server.send ( 200, "application/json", "{\"success\": true, \"msg\": \"💡 Dimmer set to : " + String(dimValue) + " ..\"}");
}

/**
 * Decrement dimValue by stepSize
 */
void handleDimDown() {
  dimValue -= stepSize;
  dimValue = (dimValue < 0) ? 0 : dimValue;
  setLight();
  server.send ( 200, "application/json", "{\"success\": true, \"msg\": \"💡 Dimmer set to : " + String(dimValue) + " ..\"}");
}

/**
 * set dimValue based on query parameter
 */
void handleDim() {
  if (server.arg("val") != "") {
    dimValue = server.arg("val").toInt();
  }

  dimValue = (dimValue < 0) ? 0 : dimValue;
  dimValue = (dimValue > 1023) ? 1023 : dimValue;
  setLight();
  server.send ( 200, "application/json", "{\"success\": true, \"msg\": \"💡 Dimmer set to : " + String(dimValue) + " ..\"}");
}