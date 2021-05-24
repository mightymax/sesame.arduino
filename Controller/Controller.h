/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_CONTROLLER_H
#define SESAME_CONTROLLER_H

#include "Messages.h"
#include "Sensors.h"
#include "Door.h"
#include "Board.h"
#include "Timeout.h"

struct Controller_Timeouts {
  Timeout range = Timeout(200);
  Timeout SHT31 = Timeout(60000);
  Timeout luminosity = Timeout(5000);
};

class Controller {
  private:
    Controller_Timeouts timeouts = Controller_Timeouts();
    Board board = Board();

  public:
    Messages messages = Messages();
    Sensors sensors = Sensors();
    Door door = Door();
    void setup();
    void loop();
};

#endif
