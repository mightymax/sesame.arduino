/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#include "Sesame.h"

void Sesame::setup() {
  printSignature();
  sensors.setup();
}

void Sesame::loop() {
  if (!hasSubscribed) {
    if (mode == SesameModusController) {
      messages.client.subscribe(MQTT_TOPIC_SENSORS_RANGE_BOTTOM);
      messages.client.subscribe(MQTT_TOPIC_COMMANDS_CONTROLLER);
    } else {
      // Unused, maybe we need it later ..
      // messages.client.subscribe(MQTT_TOPIC_COMMANDS_RANGESENSOR);
    }
    hasSubscribed = true;
  }

  if (!messages.client.connected()) {
    messages.reconnect();
  }
  if (mode == SesameModusController) {
    if (timeouts.rangeTop.due()) {
      int range = sensors.rangeTop();
      door.setTopRange(range);
      messages.publishRangeTop(range);
    }

    if (timeouts.doorStatus.due()) {
      messages.publishDoorStatus(door.getStatus());
    }

    if (timeouts.SHT31.due()) {
      messages.publishTemperature(sensors.temperature());
      messages.publishHumidity(sensors.humidity());
    }
    
    if (timeouts.luminosity.due()) {
      messages.publishLuminosity(sensors.luminosity());
    }

    if (timeouts.temperature.due()) {
      messages.publishTemperature(sensors.temperature());
    }

    messages.recieve();

  } else if (timeouts.rangeBottom.due()) {
    int range = sensors.rangeBottom();
    messages.publishRangeBottom(range);
  }

}

void Sesame::printSignature() {
  Serial.print("================================================\n");
  Serial.print("Opening/Closing project for Garagedoor\n");
  Serial.print("See https://github.com/mightymax/sesame.arduino\n");
  Serial.print("================================================\n");
}