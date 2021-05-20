



void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String command = "";
  for (int i=0;i<length;i++) {
    command += String((char)payload[i]);
  }
  Serial.print(" `");
  Serial.print(command);
  Serial.println("`");
  
  if (command.equals("open"))  return process(DO_OPEN_DOOR);
  else if (command.equals("close")) return process(DO_CLOSE_DOOR);
  else if (command.equals("close")) return buttonPress();
  else if (command.equals("status")) {
    long range = getRange();
    return publishStatus(range, false, "");
  }
  else {
    Serial.println("Unkown command");
    String logMsgAsString = "hw40/garage/commands\t unkown command `" + command; + "`";
    char msg[200];
    logMsgAsString.toCharArray(msg, 200);
    mqttClient.publish(TOPIC_LOGS, msg); 
  }
}

void mqttReconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(IOT_APP_ID, IOT_APP_ID, IOT_APP_PASSWD)) {
      Serial.println("connected");
      mqttClient.publish(TOPIC_LOGS, "door is connected");
      WiFiDrv::analogWrite(RED_LED, LOW);
      WiFiDrv::analogWrite(GREEN_LED, HIGH);
      
      mqttClient.subscribe(TOPIC_COMMANDS);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
