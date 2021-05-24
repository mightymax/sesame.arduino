/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#ifndef SESAME_DOOR_H
#define SESAME_DOOR_H

// Status constants
#define STATUS_DOOR_OPEN          "OPEN"
#define STATUS_DOOR_CLOSED        "CLOSED"
#define STATUS_DOOR_OPENING       "OPENING"
#define STATUS_DOOR_CLOSING       "CLOSING"
#define STATUS_DOOR_ERROR         "ERROR"

// Available Commands:
#define COMMAND_DOOR_OPEN         "OPEN"
#define COMMAND_DOOR_CLOSE        "CLOSE"
#define COMMAND_DOOR_TOGGLE       "TOGGLE"

#define MAX_POSSIBLE_EXTERNAL_RANGE 517
#define MIN_MOVING_DELTA 2
#define MIN_RANGE_DOOR_IS_OPEN 10
#define DOOR_OPERATE_TIMEOUT 20 

#include <SPI.h>
#include <ArduinoJson.h>
#include "utils.h"
#include "Sensors.h"
#include "Doorbutton.h"
#include "Timeout.h"

enum Doorstatus {Open, Closed, Opening, Closing, Error, Unkown};

struct Range {
  public:
    int top = -1;
    int bottom = -1;
};

class DoorSettings {
  public:
    int max_possible_external_range = MAX_POSSIBLE_EXTERNAL_RANGE;
    int min_moving_delta = MIN_MOVING_DELTA;
    int min_range_door_is_open = MIN_RANGE_DOOR_IS_OPEN;
    int door_operate_timeout = DOOR_OPERATE_TIMEOUT;

  public:
    void edit(String key, String value);
    void edit(String jsonString) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, jsonString);
      if (error) {
        print("Failed to parse '%s' as JSON string\n", jsonString);
        return;
      }
      if (doc["max_possible_external_range"]) max_possible_external_range =   doc["max_possible_external_range"];
      if (doc["min_moving_delta"])            min_moving_delta =              doc["min_moving_delta"];
      if (doc["min_range_door_is_open"])      min_range_door_is_open =        doc["min_range_door_is_open"];
      if (doc["door_operate_timeout"])        min_moving_delta =              doc["door_operate_timeout"];
    }

};

class Door {
  private:
    String errorMessage = String();
    void error(String message);
    Doorstatus currentStatus = Unkown;
    Timeout movingTimout = Timeout(1000);
    Range range;
    Doorbutton button = Doorbutton();
    DoorSettings settings = DoorSettings();

    int previous_top_range = 0;
    bool open();
    bool close();
    bool toggle();
    
  public:
    bool exec(String command);
    Doorstatus getStatus();
    String getStatusValue();
    void editSettings(String settings);

    static String getStatusValue(Doorstatus status);
    Doorstatus setTopRange(int range);
    void setBottomRange(int range);
    void setBottomRange(String range);
    Range getRange();
} ;

#endif
