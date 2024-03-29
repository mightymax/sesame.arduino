/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_SENSORS_H
#define SESAME_SENSORS_H

#include <SHT31.h>
#include <Ultrasonic.h>

// Hardware PIN's
#define PIN_RELAY        4
#define PIN_RANGESENSOR_TOP  2
#define PIN_RANGESENSOR_BOTTOM  6

#define MIN_LUMINOSITY 10
#define MAX_LUMINOSITY 750

class Sensors {
  private:
    SHT31 sht31 = SHT31();
    Ultrasonic ultrasonicTop = Ultrasonic(PIN_RANGESENSOR_TOP);
    Ultrasonic ultrasonicBottom = Ultrasonic(PIN_RANGESENSOR_BOTTOM);
    bool started = false;
    
  public:
    void setup();
    int temperature();
    int humidity();
    float luminosity();
    int rangeTop();
    int rangeBottom();
};

#endif
