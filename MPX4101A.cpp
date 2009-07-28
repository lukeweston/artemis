#include "MPX4101A.h"

MPX4101A::MPX4101A(Aiko::Device::MCP320x &adc) {
  adc_ = &adc;
}

int MPX4101A::readPressure() {
  adc_->readChannel(0);
}
