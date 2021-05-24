/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#include "ENV.h"
#include "Board.h"
#include "utils.h"

void Board::connect() {
  int i = 1;
  while (wifiStatus != WL_CONNECTED) {
    print("Attempt #%d to connect to SSID '%s'\n", i, WIFI_SSID);
    wifiStatus = WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    // wait 10 seconds for connection:
    i++;
    delay(10000);
  }
  printWiFiStatus();
}

bool Board::hasModule() {
  return WiFi.status() != WL_NO_MODULE;
};


void Board::setup() {

  WiFiDrv::pinMode(GREEN_LED, OUTPUT);         // Initialize the Green LED pin on the MKR1010 board
  WiFiDrv::pinMode(RED_LED, OUTPUT);         // Initialize the Red LED pin on the MKR1010 board
  WiFiDrv::pinMode(BLUE_LED, OUTPUT);         // Initialize the Blue LED pin on the MKR1010 board

  ledNotice();

  if (!hasModule()) {
    print("Communication with WiFi module failed!");
    while (true) {
      ledError();
      delay(500);
      ledNotice();
      delay(500);
    }
  }
  
  firmwareCheck();
  connect();
  ledOk();
}

bool Board::firmwareCheck() {
  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    print("Please upgrade the firmware, your version is '%s', latest is '%s'.\n", fv, WIFI_FIRMWARE_LATEST_VERSION);
    return false;
  } else {
    print("Your firmware is up to date (%s).\n", fv.c_str());
    return true;
  }
}

void Board::ledNotice() {
  rgb("#ff9900");
}

void Board::ledError() {
  rgb("#ff3300");
}

void Board::ledOk() {
  rgb("#33cc33");
}

void Board::rgb(String value) {                // Function that will be called when you pick a color on AllThingsTalk
  // Parses the received RGB information into three separate variables (R, G, B)
  long hexColor = (long) strtol(&value[1], NULL, 16);
  int r = hexColor >> 16;
  int g = hexColor >> 8 & 0xFF;
  int b = hexColor & 0xFF;
  WiFiDrv::analogWrite(GREEN_LED, g);          // Set the Green LED to received value
  WiFiDrv::analogWrite(RED_LED, r);          // Set the Red LED to received value
  WiFiDrv::analogWrite(BLUE_LED, b);          // Set the Blue LED to received value
}

void Board::printWiFiStatus()
{
  print("Connected to the network\n");
  print("----------------------------------------\n");
  print("SSID: %s\n", WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  char ipString[15];
  StringPrinter(ipString).print(ip); 
  print("IP Address: %s", ipString);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  print("Signal strength (RSSI): %d\n", rssi);
}
