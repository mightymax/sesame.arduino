/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#include "ENV.h"
#include "utils.h"
#include "Messages.h"

void Messages::recieve() {
  client.loop();
}

void Messages::reconnect() {
  // Loop until we're connected
  bool connectResult = false;

  while (!client.connected()) {
    print("Attempting MQTT connection... ");
    #ifdef MQTT_BROKER_USERNAME
    connectResult = client.connect(MQTT_BROKER_CLIENT_ID, MQTT_BROKER_USERNAME, MQTT_BROKER_PASSWD);
    #else
    connectResult = client.connect(MQTT_BROKER_CLIENT_ID);
    #endif

    if (connectResult) {
      print("connected\n");
      client.subscribe(MQTT_TOPIC_COMMANDS);
      client.subscribe(MQTT_TOPIC_SENSORS_RANGE_BOTTOM);
    } else {
      char a = client.state();
      print("failed, rc=%s, try again in 5 seconds ...\n", client.state());
      delay(5000);
    }
  }
};

void Messages::publishRange(int range) {
  client.publish(MQTT_TOPIC_SENSORS_RANGE_TOP, String(range).c_str());
};

void Messages::publishTemperature(int degrees) {
  client.publish(MQTT_TOPIC_SENSORS_TEMPERATURE, String(degrees).c_str());
};

void Messages::publishHumidity(int humidity) {
  client.publish(MQTT_TOPIC_SENSORS_HUMIDITY, String(humidity).c_str());
};

void Messages::publishLuminosity(float luminosity) {
  client.publish(MQTT_TOPIC_SENSORS_LUMINOSITY, String(luminosity).c_str());
};

void Messages::publishDoorStatus(Doorstatus status) {
  client.publish(MQTT_TOPIC_DOOR_STATUS, Door::getStatusValue(status).c_str());
}

void Messages::publishDoorStatus(String status) {
  client.publish(MQTT_TOPIC_DOOR_STATUS, status.c_str());
}

String Messages::getMessage(byte* payload, unsigned int length) {
  String msg = "";
  for (int i=0;i<length;i++) {
    msg += String((char)payload[i]);
  }
  return msg;
} ;
