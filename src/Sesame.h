/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */



#ifndef SESAME_H
#define SESAME_H

#include "Messages.h"
#include "Sensors.h"
#include "Door.h"
#include "Timeout.h"

struct Controller_Timeouts {
  Timeout rangeTop = Timeout(1000);
  Timeout rangeBottom = Timeout(1000);
  Timeout SHT31 = Timeout(60000);
  Timeout temperature = Timeout(60000);
  Timeout luminosity = Timeout(5000);
  Timeout doorStatus = Timeout(500);
};

enum SesameModus {SesameModusController, SesameModusRangesensor};

class Sesame {
  private:
    Controller_Timeouts timeouts = Controller_Timeouts();
    bool hasSubscribed = false;

  protected:
    SesameModus mode = SesameModusController;
    Sensors sensors = Sensors();
    void printSignature();

  public:
    Messages messages = Messages();
    Door door = Door();
    void setup();
    void loop();
};

#endif
