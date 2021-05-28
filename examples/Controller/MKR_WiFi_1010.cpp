/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#include "MKR_WiFi_1010.h"

void MKR_WiFi_1010::connect() {
  WiFiDrv::pinMode(GREEN_LED, OUTPUT);         // Initialize the Green LED pin on the MKR1010 board
  WiFiDrv::pinMode(RED_LED, OUTPUT);         // Initialize the Red LED pin on the MKR1010 board
  WiFiDrv::pinMode(BLUE_LED, OUTPUT);         // Initialize the Blue LED pin on the MKR1010 board

  ledNotice();
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true) {
      ledError();
      delay(500);
      ledNotice();
      delay(500);
    }
  }
  firmwareCheck();
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Attempting to connect to WPA SSID: %s"), WIFI_SSID);
    Serial.println(s);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("You're connected to the network");
  ledOk();
  printCurrentNet();
  printWiFiData();
}

void MKR_WiFi_1010::printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

bool MKR_WiFi_1010::firmwareCheck() {
  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Please upgrade the firmware, your version is '%s', latest is '%s'."), fv.c_str(), WIFI_FIRMWARE_LATEST_VERSION);
    Serial.println(s);
    return false;
  } else {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Your firmware is up to date (%s)."), fv.c_str());
    Serial.println(s);
    return true;
  }
}

void MKR_WiFi_1010::ledNotice() {
  rgb("#ff9900");
}

void MKR_WiFi_1010::ledError() {
  rgb("#ff3300");
}

void MKR_WiFi_1010::ledOk() {
  rgb("#33cc33");
}

void MKR_WiFi_1010::rgb(String value) {                // Function that will be called when you pick a color on AllThingsTalk
  // Parses the received RGB information into three separate variables (R, G, B)
  long hexColor = (long) strtol(&value[1], NULL, 16);
  int r = hexColor >> 16;
  int g = hexColor >> 8 & 0xFF;
  int b = hexColor & 0xFF;
  WiFiDrv::analogWrite(GREEN_LED, g);          // Set the Green LED to received value
  WiFiDrv::analogWrite(RED_LED, r);          // Set the Red LED to received value
  WiFiDrv::analogWrite(BLUE_LED, b);          // Set the Blue LED to received value
}

void MKR_WiFi_1010::printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void MKR_WiFi_1010::printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}