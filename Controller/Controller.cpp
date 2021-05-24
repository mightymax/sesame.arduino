/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#include "Controller.h"
#include "utils.h"

void Controller::setup() {
  print("================================================\n");
  print("Controller project for Garagedoor\n");
  print("See https://github.com/mightymax/sesame.arduino\n");
  print("================================================\n");
  board.setup();
  sensors.setup();
}

void Controller::loop() {
  if (!messages.client.connected()) {
    messages.reconnect();
  }
  
  if (timeouts.range.due()) {
    int range = sensors.range();
    Doorstatus currentStatus = door.getStatus();
    Doorstatus newStatus = door.setTopRange(range);
    if (newStatus != currentStatus) {
      messages.publishDoorStatus(newStatus);
    }
    messages.publishRange(range);
  }
  
  if (timeouts.SHT31.due()) {
    messages.publishTemperature(sensors.temperature());
    messages.publishHumidity(sensors.humidity());
  }
  
  if (timeouts.luminosity.due()) {
    messages.publishLuminosity(sensors.luminosity());
  }

  messages.recieve();
}
