#include "DS18B20.h"

#define ONE_WIRE_DEVICE_18B20  0x28

#define ONE_WIRE_COMMAND_READ_SCRATCHPAD  0xBE
#define ONE_WIRE_COMMAND_START_CONVERSION 0x44
#define ONE_WIRE_COMMAND_MATCH_ROM        0x55
#define ONE_WIRE_COMMAND_SKIP_ROM         0xCC

DS18B20::DS18B20(OneWire &oneWire) {
  oneWire_ = &oneWire;
  isSetUp_ = false;
}

void DS18B20::setup() {
  deviceFound_ = false;
  oneWire_->reset_search();
  while (!deviceFound_ && oneWire_->search(address_)) {
    // FIXME: CRC check the address
    if (address_[0] == ONE_WIRE_DEVICE_18B20) deviceFound_ = true;
  }
  
  isSetUp_ = true;
}

void DS18B20::startConversion() {
  if (!isSetUp_) setup();
  oneWire_->reset();                                      // time: 1 millisecond
  oneWire_->select(address_);                             // time: 5 milliseconds
  oneWire_->write(ONE_WIRE_COMMAND_START_CONVERSION, 1);  // time: 1 millisecond
}

void DS18B20::read() {
  if (!isSetUp_) setup();
  oneWire_->reset();                                  // time: 1 millisecond
  oneWire_->select(address_);                         // time: 5 milliseconds
  oneWire_->write(ONE_WIRE_COMMAND_READ_SCRATCHPAD);  // time: 1 millisecond
  
  for (int i = 0; i < 9; i++) data_[i] = oneWire_->read();
}

float DS18B20::temperature() {
  int sign  = data_[1] & 0xF0 ? -1 : 1;
  int value = ((int)(data_[1] & 0x07) << 8) | data_[0];
  return ((float)(value * sign)) / 16.0;
}
