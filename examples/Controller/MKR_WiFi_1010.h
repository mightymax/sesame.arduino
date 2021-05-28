/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_BOARD_MKR_WIFI_1010_H
#define SESAME_BOARD_MKR_WIFI_1010_H

#include <WiFiNINA.h>
// Internal LED's from MKR Wifi 1001
#define GREEN_LED 25
#define RED_LED   26
#define BLUE_LED  27

/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_BOARD_MKR1000_H
#define SESAME_BOARD_MKR1000_H

#include <WiFiNINA.h>
#include <SPI.h>
#include "ENV.h"

#endif

class MKR_WiFi_1010 {
  protected:
    void printWiFiData();
    void printCurrentNet();
    bool firmwareCheck();
    void printMacAddress(byte mac[]);

  public:
    void connect();

  protected:
    void rgb(String value);
    void ledNotice();
    void ledError();
    void ledOk();
};

#endif
