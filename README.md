#Sesame Garage Door opener

Arduino Sketch file used to open the door of my garage, including Open/Close detection of door using Sensor.
*NOTE* Arduino & C are new to me, so be very caereful to reuse my code, it will probably break stuff.

## Install
Create a new file in this folder called "secrets.h". Add the following lines and save the file before compiling & uploading to your board:

```c_cpp
// Important Note: passord length must be 8+ characters or AP creation failed
char ssid[] = "YOUR-AP-SSID";
char pass[] = "YOUR-AP-PASSWD";

const char* IOT_APP_ID = "USERNAME-MQTT-BROKER";
const char* IOT_APP_PASSWD = "PASSWORD-MQTT-BROKER";
```

Upload Sketch to your board, Serial Monitor should provide you debug info if things fail. Use a multimeter to detect the right ports on your terminal from your door opener (should list no more than 5V, do not connect if 110V or higher!) and connect the relay to this terminal. This sketch uses SSL to connect to MQTT Broker (Mosquito in my case). I upoloded the SSL certificate for my broker using the Arduino tool.

## Hardware list
- [Arduino MKR 1010 WiFi](https://store.arduino.cc/arduino-mkr-wifi-1010)
- [Arduino MKR Connector Carrier (Grove compatible)](https://store.arduino.cc/arduino-mkr-connector-carrier)
- [Grove - Ultrasonic Distance Sensor ](https://www.seeedstudio.com/Grove-Ultrasonic-Distance-Sensor.html)
- [Grove - Temperature & Humidity Sensor (SHT31))](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-SHT31.html)
- [Grove - Light Sensor (P) v1.1](https://www.seeedstudio.com/Grove-Light-Sensor-P-v1-1.html)
- [Grove - Relay](https://www.seeedstudio.com/Grove-Relay.html)

## Grove connections
- Ultrasonic Distance Sensor: D2
- SHT31: TWI
- Light Sensor: A0
- Relay: D4
