/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#include "Controller.h"

// IMPORTANT: make sure to change/add include in Messages.h
// to match the correct board: 
// (because I do not want to waste more time on doing this properly in  C++)
// - WiFiNINA.h for MKR WiFi 1010
// - WiFi101.h for MKR1000

Controller controller = Controller();

void setup() {
  controller.setup();
  controller.board.connect();
  controller.messages.connect("SesameGarageOpener-Controller");
  controller.messages.client.setCallback(subscriptionCallback);
}

void loop() {
  controller.loop();
}

void subscriptionCallback(char* topic, byte* payload, unsigned int length) {
  String msg = Messages::getMessage(payload, length);
  if (strcmp(topic, MQTT_TOPIC_SENSORS_RANGE_BOTTOM) == 0) {
    controller.door.setBottomRange(msg);
  } else if (strcmp(topic, MQTT_TOPIC_COMMANDS_CONTROLLER) == 0) {
    Serial.println(msg);
    controller.door.exec(msg);
  } else if (strcmp(topic, MQTT_TOPIC_SETTINGS_CONTROLLER) == 0) {
    controller.door.editSettings(msg);
  } else {
    char s[150];
    snprintf_P(s, sizeof(s), PSTR("Ignoring MQTT Message arrived at topic '%s':\n [%s]"), topic, msg.c_str());
    Serial.println(s);
  }
}
