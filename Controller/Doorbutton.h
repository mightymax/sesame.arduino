/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_RELAY_H
#define SESAME_RELAY_H

#define RELAY_PIN 4
#define RELAY_OPEN_DURATION 500

class Doorbutton {
  public:
    Doorbutton() {
      pinMode(RELAY_PIN, OUTPUT);
    };

    void click() {
      digitalWrite(RELAY_PIN, HIGH);
      delay(RELAY_OPEN_DURATION);
      digitalWrite(RELAY_PIN, LOW);
    }

};

#endif