/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */
#include "Door.h"

void Door::error(String msg) {
  errorMessage = msg;
  Serial.println(msg);
};

bool Door::exec(String command) {
  if (command.equalsIgnoreCase(COMMAND_DOOR_OPEN)) return open();
  else if (command.equalsIgnoreCase(COMMAND_DOOR_CLOSE)) return close();
  else if (command.equalsIgnoreCase(COMMAND_DOOR_TOGGLE)) return toggle();
  else {
    char s[50];
    snprintf_P(s, sizeof(s), PSTR("Unkown command '%s'"), command.c_str());
    error(String(s));
  }
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


void Door::setTopRange(int range) {
  if (range >= -1) {
    this->range.top = range;
    if (this->previousRange.top <= -1) this->previousRange.top = range;
  }
}

void Door::setBottomRange(int range) {
  if (range >= -1 && range <= settings.max_possible_range_bottom) {
    this->range.bottom = range;
    if (this->previousRange.bottom <= -1) this->previousRange.bottom = range;
  }
}

void Door::setBottomRange(String range) {
  int range_as_int = range.toInt();
  if (range_as_int > 0) {
    setBottomRange(range_as_int);
  }
};

Doorstatus Door::getStatus() {
  const int delta = previousRange.bottom - range.bottom;
  if (range.top <= DOOR_MIN_RANGE_TOP_IF_DOOR_IS_OPEN) {
    currentStatus = Open;
  } else if (delta != 0 && delta < MIN_MOVING_DELTA ) {
    currentStatus = Opening;
    previousRange = range;
  } else if (delta != 0 && delta > MIN_MOVING_DELTA ) {
    currentStatus = Closing;
    previousRange = range;
  } else if (range.bottom <= DOOR_MIN_RANGE_BOTTOM_IF_DOOR_IS_CLOSED) {
    currentStatus = Closed;
  } else if (range.bottom > DOOR_MIN_RANGE_BOTTOM_IF_DOOR_IS_CLOSED) {
    currentStatus = PartlyOpen;
  } else {
    currentStatus = Unkown;
  }
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
   if (status == PartlyOpen) return "PartlyOpen";
   return "Unkown";
};
