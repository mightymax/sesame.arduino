/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_RANGESENSOR_H
#define SESAME_RANGESENSOR_H

#define RANGE_MARGIN 4

#include <SPI.h>
#include <Sesame.h>
#include "MKR1000.h"

class Rangesensor: public Sesame {
  public:
    Rangesensor() {
      this->mode = SesameModusRangesensor;
    }
    MKR1000 board = MKR1000();
};

#endif
