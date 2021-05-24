/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#include "Door.h"
#include "utils.h"

void Door::error(String msg) {
  errorMessage = msg;
  print(msg.c_str());
};

bool Door::exec(String command) {
  if (command.equalsIgnoreCase(COMMAND_DOOR_OPEN)) return open();
  else if (command.equalsIgnoreCase(COMMAND_DOOR_CLOSE)) return close();
  else if (command.equalsIgnoreCase(COMMAND_DOOR_TOGGLE)) return toggle();
};

bool Door::open() {
  if (currentStatus == Closed) {
    return toggle();
  }
  error("Door is not closed.");
  return false;
};

bool Door::close() {
  if (currentStatus == Open) {
    return toggle();
  }
  error("Door is not open.");
  return false;
};

bool Door::toggle() {
  button.click();
};

   
Range Door::getRange() {
  return range;
};

void Door::editSettings(String settings) {
  this->settings.edit(settings);
  //@TODO propegate settings to objects
}


Doorstatus Door::setTopRange(int range) {
  if (range >= -1 && range <= settings.max_possible_external_range) {
    Doorstatus newStatus = Unkown;
    this->range.top = range;
    int delta = previous_top_range - this->range.top;
    if (abs(delta) >= settings.min_moving_delta) {
      currentStatus = delta > 0 ? Closing : Opening;
      movingTimout.reset();
      previous_top_range = this->range.top;
    } else if (movingTimout.due()) {
      //publish current status only if no motion has been detected for the last second:
      currentStatus = this->range.top < settings.min_range_door_is_open ? Closed : Open;
    }
  }
  return currentStatus;
}

void Door::setBottomRange(int range) {
  if (range >= -1 && range <= settings.max_possible_external_range) {
    this->range.bottom = range;
  }
}

void Door::setBottomRange(String range) {
  int range_as_int = range.toInt();
  if (range_as_int > 0) {
    setBottomRange(range_as_int);
  }
};

Doorstatus Door::getStatus() {
  return currentStatus;
}

String Door::getStatusValue() {
   return Door::getStatusValue(getStatus());
};

String Door::getStatusValue(Doorstatus status) {
   if (status == Open) return "Open";
   if (status == Closed) return "Closed";
   if (status == Opening) return "Opening";
   if (status == Closing) return "Closing";
   if (status == Error) return "Error";
   if (status == Unkown) return "Unkown";
};
