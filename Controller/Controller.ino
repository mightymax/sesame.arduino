/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#include "./utils.h"
#include "./Controller.h"

Controller controller = Controller();

void setup() {
  Serial.begin(115200);
  int i = 0;
  bool haveSerial = false;
  while(!haveSerial) {
    haveSerial = Serial;
    delay(100);
    i+=100;
    if (i > 1000) {
      // not important for us:
      haveSerial = true;
    }
  }
  

  controller.setup();
  controller.messages.client.setCallback(subscriptionCallback);
}

void loop() {
  controller.loop();
}

void subscriptionCallback(char* topic, byte* payload, unsigned int length) {
  String msg = Messages::getMessage(payload, length);
  if (strcmp(topic, MQTT_TOPIC_SENSORS_RANGE_BOTTOM) == 0) {
    controller.door.setBottomRange(msg);
  } else if (strcmp(topic, MQTT_TOPIC_COMMANDS) == 0) {
    controller.door.exec(msg);
  } else if (strcmp(topic, MQTT_TOPIC_SETTINGS) == 0) {
    controller.door.editSettings(msg);
  } else {
    print("Ignoring MQTT Message arrived at topic '%s':\n [%s]\n", topic, msg.c_str());
  }
}
