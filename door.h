void buttonPress() {
  digitalWrite(TR_GATE, HIGH);
  delay(TR_GATE_DELAY);
  digitalWrite(TR_GATE, LOW);
}

long getRange()
{
  long range = ultrasonic.MeasureInCentimeters();
  return range;
}

bool isOpen(long range) {
//  return range > MinRangeIfDoorIsOpen;
  return range < MaxRangeIfDoorIsClosed;
}

bool auth ()
{
  return true;
}

void publishStatus(long range, bool isError, String message)
{
  DynamicJsonDocument doc(200);
  doc["range"] = range;
  doc["error"] = isError;
  doc["message"] = message;
  
  doc["temperature"] = sht31.getTemperature();
  doc["humidity"] = sht31.getHumidity();
  doc["light"] = analogRead(A0);
    
  if (DOOR_STATUS != DOOR_CLOSING && DOOR_STATUS != DOOR_OPENING) {
     DOOR_STATUS = isOpen(range) ? DOOR_OPEN : DOOR_CLOSED;
  }
  doc["door"] = DOOR_STATUS;

  doc["ssid"] = WiFi.SSID();
  IPAddress ip = WiFi.localIP();
  doc["ip"] =   String(ip[0]) + String(".") + String(ip[1]) + String(".") + String(ip[2]) + String(".") + String(ip[3])  ; 
  doc["rssi"] = WiFi.RSSI();

  char output[200] ;
  serializeJson(doc, output);
  mqttClient.publish(TOPIC_STATUS,output);

}

void process(int whatToDo)
{
  if (!auth()) return;
  
  if (whatToDo != DO_OPEN_DOOR && whatToDo != DO_CLOSE_DOOR) {
    mqttClient.publish(TOPIC_LOGS, "process rejected: unkown process requested");
    return;
  }
  
  int timer = 0;
  long range = getRange();

  //can we process this request?
  if (DOOR_STATUS == DOOR_OPENING || DOOR_STATUS == DOOR_CLOSING) {
    return publishStatus(range, true, "door is busy");
  }

  //update OPEN/CLOSE status:
  DOOR_STATUS = isOpen(range) ? DOOR_OPEN : DOOR_CLOSED;

  if (whatToDo == DO_OPEN_DOOR && DOOR_STATUS == DOOR_OPEN) {
    return publishStatus(range, true, "door is already open");
  }

  if (whatToDo == DO_CLOSE_DOOR && DOOR_STATUS == DOOR_CLOSED) {
    return publishStatus(range, true, "door is already closed");
  }


  DOOR_STATUS = whatToDo == DO_OPEN_DOOR ? DOOR_OPENING : DOOR_CLOSING;
  publishStatus(range, false, whatToDo == DO_OPEN_DOOR ? "door is opening" : "door is closing");

  bool busy = true;
  buttonPress();
  Serial.print("WAITING for  ");
  Serial.print(DOOR_STATUS);
  
  while (busy) {
    delay(1000);
    timer++;
    range = getRange();
    if ((whatToDo == DO_CLOSE_DOOR && !isOpen(range)) || (whatToDo == DO_OPEN_DOOR && isOpen(range))) busy = false;
    else if ((whatToDo == DO_CLOSE_DOOR && timer > closingTimeoutAfter) || (whatToDo == DO_OPEN_DOOR && timer > openingTimeoutAfter)) {
      Serial.println("timeout");
      busy = false;
      DOOR_STATUS = whatToDo == DO_CLOSE_DOOR ? DOOR_OPEN : DOOR_CLOSED;
      return publishStatus(range, true, "a timeout occured");
    } else {
      Serial.print(".");
    }
  }

  DOOR_STATUS = whatToDo == DO_OPEN_DOOR ? DOOR_OPEN : DOOR_CLOSED;
  publishStatus(range, false, "done");

  Serial.println(DOOR_STATUS);
}
