/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */



#ifndef SESAME_CONTROLLER_H
#define SESAME_CONTROLLER_H

#include <Sesame.h>
#include "MKR_WiFi_1010.h"

class Controller: public Sesame {
  public:
    MKR_WiFi_1010 board = MKR_WiFi_1010();
};

#endif
