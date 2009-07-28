#include <AikoDeviceMCP320x.h>

class MPX4101A {
  public:
    MPX4101A(Aiko::Device::MCP320x &adc);
    int readPressure();
    
  private:
    Aiko::Device::MCP320x *adc_;
};
