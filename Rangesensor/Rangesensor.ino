#include <SPI.h>
#include <WiFi101.h>
#include <PubSubClient.h>
#include "Ultrasonic.h"
#include "secrets.h"
#include "wifi.h"
#include <ArduinoJson.h>

WiFiSSLClient client;
PubSubClient mqttClient("mqtt.lindeman.nu", 8883, client);

char TOPIC_RANGE[] = "hw40/garage/range";
char TOPIC_LOGS[]  = "hw40/garage/logs";

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
     // the WiFi radio's status
Ultrasonic ultrasonic(2);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  bool connected = wifiConnect(ssid, pass);
  if (false == connected) {
    while (true);
  }
  
  Serial.println("********************************************************");
  Serial.println("Range meter project for Garagedoor");
  Serial.println("See https://github.com/mightymax/sesame.arduino");
  Serial.println("********************************************************");
  printCurrentNet();
  printWiFiData();

}

void loop() {
  if (!mqttClient.connected()) {
    mqttReconnect();
  }
  
  delay(500);
  long range = ultrasonic.MeasureInCentimeters();
  const char* payload = std::to_string(range).c_str();
  mqttClient.publish(TOPIC_RANGE, payload);
//  Serial.println(range);
}

void mqttReconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(IOT_APP_CLIENT_ID, IOT_APP_USERNAME, IOT_APP_PASSWD)) {
      Serial.println("connected");
      Serial.print("Publishing range<Long> to Topic '");
      Serial.print(TOPIC_RANGE);
      Serial.println("'");
      mqttClient.publish(TOPIC_LOGS, "sensor is connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
