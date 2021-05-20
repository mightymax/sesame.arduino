#include "secrets.h"
#include "defines.h"
#include "door.h"
#include "mqtt.h"

void setup() {
  Serial.begin(115200);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("Please upgrade the firmware: ");
    Serial.print(fv);
    Serial.print(" < ");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
  }
  
  
  //internal multicolor Led:
  WiFiDrv::pinMode(GREEN_LED, OUTPUT);         // Initialize the Green LED pin on the MKR1010 board
  WiFiDrv::pinMode(RED_LED, OUTPUT);         // Initialize the Red LED pin on the MKR1010 board
  WiFiDrv::pinMode(BLUE_LED, OUTPUT);         // Initialize the Blue LED pin on the MKR1010 board

  //Transistor/Relay for gate
  pinMode(TR_GATE, OUTPUT);

  WiFiDrv::analogWrite(RED_LED, HIGH);

  
  // attempt to connect to WiFi network:
  while (wifiStatus != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    wifiStatus = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  printWiFiStatus();

  sht31.begin();

  mqttClient.setCallback(mqttCallback);
}

void loop()
{
  if (!mqttClient.connected()) {
    WiFiDrv::analogWrite(RED_LED, HIGH);
    WiFiDrv::analogWrite(GREEN_LED, LOW);
    mqttReconnect();
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= sendStatusInterval) {
    previousMillis = currentMillis;
    long range = ultrasonic.MeasureInCentimeters();
    publishStatus(range, false, "");
  }

  
  mqttClient.loop();
}

void printWiFiStatus()
{
  Serial.println("Connected to the network");
  Serial.println("----------------------------------------");
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.println(rssi);
}
