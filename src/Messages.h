/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

// - WiFiNINA.h for MKR WiFi 1010
// - WiFi101.h for MKR1000

// #include <WiFi101.h>
#include <WiFiNINA.h>


#ifndef SESAME_MESSAGES_H
#define SESAME_MESSAGES_H


#ifndef MQTT_TOPIC_COMMANDS_CONTROLLER
  #define MQTT_TOPIC_COMMANDS_CONTROLLER "sesame/commands/controller"
#endif

// Unused, maybe we need it later ..
#ifndef MQTT_TOPIC_COMMANDS_RANGESENSOR
  #define MQTT_TOPIC_COMMANDS_RANGESENSOR "sesame/commands/rangesensor"
#endif

// Unused, maybe we need it later ...
#ifndef MQTT_TOPIC_SETTINGS_CONTROLLER
  #define MQTT_TOPIC_SETTINGS_CONTROLLER "sesame/settings/controller"
#endif

#ifndef MQTT_TOPIC_SETTINGS_RANGESENSOR
  #define MQTT_TOPIC_SETTINGS_RANGESENSOR "sesame/settings/rangesensor"
#endif

#ifndef MQTT_TOPIC_SETTINGS
  #define MQTT_TOPIC_SETTINGS "sesame/settings"
#endif

#ifndef MQTT_TOPIC_SENSORS
  #define MQTT_TOPIC_SENSORS   "sesame/sensors"
#endif

#ifndef MQTT_TOPIC_SENSORS_TEMPERATURE
  #define MQTT_TOPIC_SENSORS_TEMPERATURE     "sesame/sensors/temperature"
#endif

#ifndef MQTT_TOPIC_SENSORS_HUMIDITY
  #define MQTT_TOPIC_SENSORS_HUMIDITY     "sesame/sensors/humidity"
#endif

#ifndef MQTT_TOPIC_SENSORS_LUMINOSITY
  #define MQTT_TOPIC_SENSORS_LUMINOSITY     "sesame/sensors/luminosity"
#endif

#ifndef MQTT_TOPIC_SENSORS_RANGE_TOP
  #define MQTT_TOPIC_SENSORS_RANGE_TOP     "sesame/sensors/range/top"
#endif

#ifndef MQTT_TOPIC_SENSORS_RANGE_BOTTOM
  #define MQTT_TOPIC_SENSORS_RANGE_BOTTOM     "sesame/sensors/range/bottom"
#endif

#ifndef MQTT_TOPIC_DOOR_STATUS
  #define MQTT_TOPIC_DOOR_STATUS     "sesame/sensors/door/status"
#endif

#ifndef MQTT_BROKER_PORT
  #define MQTT_BROKER_PORT 8883
#endif

#include <PubSubClient.h>

#include "ENV.h"
#include "Door.h"

class Messages {
  private:
    WiFiSSLClient wifiClient;
    char *id;
  
  public:
    PubSubClient client = PubSubClient(MQTT_BROKER_SERVER, MQTT_BROKER_PORT, wifiClient);
    static String getMessage(byte* payload, unsigned int length);
    void reconnect();
    void connect() {
      return reconnect();
    }
    void connect(char *id) {
      this->id = id;
      return reconnect();
    }

    void recieve();
    void publishRangeTop(int range);
    void publishRangeBottom(int range);
    void publishTemperature(int degrees);
    void publishHumidity(int humidity);
    void publishLuminosity(float luminisity);
    void publishDoorStatus(Doorstatus status);
    void publishDoorStatus(String status);

};

#endif
