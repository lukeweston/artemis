#include <WProgram.h>
#include "DS1307.h"
#include <Wire.h>

#define DS1307_I2C_ADDRESS 0x68

DS1307::DS1307() {
  isSetUp_ = false;
}

unsigned char DS1307::bcdToDecimal(unsigned char x) {
  return ((x >> 4) * 10) + (x & 0xF);
}

unsigned char DS1307::decimalToBCD(unsigned char x) {
  return ((x / 10) << 4) | (x % 10);
}

void DS1307::read() {
  if (!isSetUp_) setup();
  
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.send(0);
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  
  // A few of these need masks because certain bits are control bits
  second_     = bcdToDecimal(Wire.receive() & 0x7f);
  minute_     = bcdToDecimal(Wire.receive());
  hour_       = bcdToDecimal(Wire.receive() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek_  = bcdToDecimal(Wire.receive());
  dayOfMonth_ = bcdToDecimal(Wire.receive());
  month_      = bcdToDecimal(Wire.receive());
  year_       = bcdToDecimal(Wire.receive());
}

void DS1307::set() {
  if (!isSetUp_) setup();
  
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   Wire.send(0);
   Wire.send(decimalToBCD(second_));    // 0 to bit 7 starts the clock
   Wire.send(decimalToBCD(minute_));
   Wire.send(decimalToBCD(hour_));      // If you want 12 hour am/pm you need to set
                                       // bit 6 (also need to change readDateDs1307)
   Wire.send(decimalToBCD(dayOfWeek_));
   Wire.send(decimalToBCD(dayOfMonth_));
   Wire.send(decimalToBCD(month_));
   Wire.send(decimalToBCD(year_));
   Wire.send(0x10);
   Wire.endTransmission();
}

void DS1307::setup() {
  Wire.begin();
  isSetUp_ = true;
}
