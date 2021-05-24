/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_MESSAGES_H
#define SESAME_MESSAGES_H

#ifndef MQTT_TOPIC_COMMANDS
  #define MQTT_TOPIC_COMMANDS "garage/commands"
#endif

#ifndef MQTT_TOPIC_SETTINGS
  #define MQTT_TOPIC_SETTINGS "garage/settings"
#endif

#ifndef MQTT_TOPIC_SENSORS
  #define MQTT_TOPIC_SENSORS   "garage/sensors"
#endif

#ifndef MQTT_TOPIC_SENSORS_TEMPERATURE
  #define MQTT_TOPIC_SENSORS_TEMPERATURE     "garage/sensors/temperature"
#endif

#ifndef MQTT_TOPIC_SENSORS_HUMIDITY
  #define MQTT_TOPIC_SENSORS_HUMIDITY     "garage/sensors/humidity"
#endif

#ifndef MQTT_TOPIC_SENSORS_LUMINOSITY
  #define MQTT_TOPIC_SENSORS_LUMINOSITY     "garage/sensors/luminosity"
#endif

#ifndef MQTT_TOPIC_SENSORS_RANGE_TOP
  #define MQTT_TOPIC_SENSORS_RANGE_TOP     "garage/sensors/range/top"
#endif

#ifndef MQTT_TOPIC_SENSORS_RANGE_BOTTOM
  #define MQTT_TOPIC_SENSORS_RANGE_BOTTOM     "garage/sensors/range/bottom"
#endif

#ifndef MQTT_TOPIC_DOOR_STATUS
  #define MQTT_TOPIC_DOOR_STATUS     "garage/sensors/door/status"
#endif

#include <WiFiNINA.h>
#include <PubSubClient.h>

#include "ENV.h"
#include "Door.h"

class Messages {
  private:
    WiFiSSLClient wifiClient;
  
  public:
    PubSubClient client = PubSubClient(MQTT_BROKER_SERVER, MQTT_BROKER_PORT, wifiClient);
    static String getMessage(byte* payload, unsigned int length);
    void reconnect();
    void recieve();
    void publishRange(int range);
    void publishTemperature(int degrees);
    void publishHumidity(int humidity);
    void publishLuminosity(float luminisity);
    void publishDoorStatus(Doorstatus status);
    void publishDoorStatus(String status);

};

#endif
