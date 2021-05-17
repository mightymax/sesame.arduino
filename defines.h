#include <SPI.h>
#include <WiFiNINA.h>
#include "Ultrasonic.h"
#include <ArduinoJson.h>
#include "SHT31.h"
#include <PubSubClient.h>

SHT31 sht31 = SHT31(); //temp and humidity
WiFiSSLClient client;
Ultrasonic ultrasonic(2);
PubSubClient mqttClient("mqtt.lindeman.nu", 8883, client);


char TOPIC_STATUS[]   = "hw40/garage/status";
char TOPIC_COMMANDS[] = "hw40/garage/commands";
char TOPIC_LOGS[]     = "hw40/garage/logs";

unsigned long previousMillis = 0; 
unsigned long lastTimeout = 0;
const long sendStatusInterval = 2000;

long MinRangeIfDoorIsOpen = 20 ; //if measured range is larger then door is open
long MaxRangeIfDoorIsClosed = 40 ; //if measured range is larger then door is open

int closingTimeoutAfter = 5;
int openingTimeoutAfter = 20;


const int TR_GATE = 4;
const int TR_GATE_DELAY = 200; //How long should the key be pressed?

const int GREEN_LED = 25;
const int RED_LED = 26;
const int BLUE_LED = 27;

const char* DOOR_OPEN = "OPEN";
const char* DOOR_CLOSED = "CLOSED";
const char* DOOR_OPENING = "OPENING";
const char* DOOR_CLOSING = "CLOSING";
const char* DOOR_ERROR = "ERROR";
const int DO_OPEN_DOOR = 1;
const int DO_CLOSE_DOOR = 2;
String DOOR_STATUS = "";


int wifiStatus = WL_IDLE_STATUS; 
