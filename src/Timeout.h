/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_TIMEOUT_H
#define SESAME_TIMEOUT_H

class Timeout {
  public:
    Timeout(int interval) {
      this->interval = interval;
      this->previous = 0;
    }

    bool due() {
      unsigned long currentMillis = millis();
      if (currentMillis - previous >= interval || previous == 0) {
        previous = currentMillis;
        return true;
      }
      return false;
    }

    bool reset() {
      previous = millis();
    }

  private:
    unsigned long interval;
    unsigned long previous;
};

#endif
