/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_BOARD_H
#define SESAME_BOARD_H

#include <WiFiNINA.h>

// Internal LED's from MKR Wifi 1001
#define GREEN_LED 25
#define RED_LED   26
#define BLUE_LED  27

class Board {
  private:
    int wifiStatus = WL_IDLE_STATUS;
    void printWiFiStatus();
    bool hasModule();
    bool firmwareCheck();
    void connect();
    void rgb(String value);

  public:
    void setup();
    void ledNotice();
    void ledError();
    void ledOk();
};

#endif
