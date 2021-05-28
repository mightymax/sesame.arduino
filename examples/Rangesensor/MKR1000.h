/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_BOARD_MKR1000_H
#define SESAME_BOARD_MKR1000_H

#include <SPI.h>
#include <WiFi101.h>
#include <driver/source/nmasic.h>
#include "ENV.h"

class MKR1000 {
  private:
    WiFiSSLClient wifiClient;
  protected:
    void printWiFiData();
    void printCurrentNet();
    bool firmwareCheck(String latestFv);
    void printMacAddress(byte mac[]);

  public:
    void connect();

};

#endif
