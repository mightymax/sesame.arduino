#include "MKR1000.h"

void MKR1000::connect()  {
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Communication with WiFi module failed!");
    while(true);
  }
  String latestFv;
    if (REV(GET_CHIPID()) >= REV_3A0) {
    latestFv = WIFI_FIRMWARE_LATEST_MODEL_B;
  } else {
    latestFv = WIFI_FIRMWARE_LATEST_MODEL_A;
  }
  firmwareCheck(latestFv);
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWiFiData();
}

void MKR1000::printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

bool MKR1000::firmwareCheck(String latestFv) {
  String fv = WiFi.firmwareVersion();

  if (fv < latestFv) {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Please upgrade the firmware, your version is '%s', latest is '%s'."), fv.c_str(), latestFv);
    Serial.println(s);
    return false;
  } else {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Your firmware is up to date (%s)."), fv.c_str());
    Serial.println(s);
    return true;
  }
}

void MKR1000::printCurrentNet() {
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

void MKR1000::printMacAddress(byte mac[]) {
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