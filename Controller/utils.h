/**
 * Arduino project files to control Garagedoor
 * 
 * @Author Mark Lindeman <mark@Lindeman.nu>
 * @See https://github.com/mightymax/sesame.arduino
 */

#ifndef SESAME_PRINT_H
#define SESAME_PRINT_H

#include <SPI.h>

template <typename... T>
void print(const char *str, T... args) {
  int len = snprintf(NULL, 0, str, args...);
  if (len) {
    char buff[len];
    sprintf(buff, str, args...);
    Serial.print(buff);
  }
}

class StringPrinter : public Print
{
public:
    StringPrinter(char *buffer) : buf(buffer), pos(0) {}
    virtual size_t write(uint8_t c)
    {
        buf[pos++] = c;  // add the character to the string
        buf[pos] = 0;    // null perminator
        return 1;        // one character written
    }
private:
    char *buf;
    size_t pos;
};


#endif
