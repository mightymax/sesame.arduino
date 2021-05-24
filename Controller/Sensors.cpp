/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#include "utils.h"
#include "Sensors.h"

void Sensors::setup() {
  sht31.begin();
}
    
int Sensors::temperature() {
  return sht31.getTemperature();
}

int Sensors::humidity() {
  return sht31.getHumidity();
}

// get luminosity as percentage of total range
float Sensors::luminosity() {
  int lum = analogRead(A0);
  int lum_range = MAX_LUMINOSITY - MIN_LUMINOSITY;
  float lum_pct = ((float) lum / lum_range);
  return lum_pct;
}

int Sensors::range() {
  return ultrasonic.MeasureInCentimeters();
}
