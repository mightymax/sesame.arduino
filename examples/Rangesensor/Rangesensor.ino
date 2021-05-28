/**
   Arduino project files to control Garagedoor

   @Author Mark Lindeman <mark@Lindeman.nu>
   @See https://github.com/mightymax/sesame.arduino
*/

#include "Rangesensor.h"

// IMPORTANT: make sure to change/add include in Messages.h
// to match the correct board:
// (because I do not want to waste more time on doing this properly in  C++)
// - WiFiNINA.h for MKR WiFi 1010
// - WiFi101.h for MKR1000

Rangesensor rangesensor = Rangesensor();

void setup() {
  rangesensor.setup();
  rangesensor.board.connect();
  rangesensor.messages.connect("SesameGarageOpener-Rangesensor");
}

void loop() {
  rangesensor.loop();
}
