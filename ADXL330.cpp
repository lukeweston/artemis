#include "ADXL330.h"
#include <WProgram.h>

ADXL330::ADXL330(Aiko::Device::MCP320x& adc) {
  adc_ = &adc;
  isSetUp_ = false;
}

int ADXL330::readX() { if (!isSetUp_) setup(); return adc_->readChannel(0) - 2048; }
int ADXL330::readY() { if (!isSetUp_) setup(); return adc_->readChannel(1) - 2048; }
int ADXL330::readZ() { if (!isSetUp_) setup(); return adc_->readChannel(2) - 2048; }

void ADXL330::setup() {
  // Make sure the accelerometer self-test pin stays low.
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  isSetUp_ = true;
}
