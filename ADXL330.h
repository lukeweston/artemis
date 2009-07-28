#include <AikoDeviceMCP320x.h>

class ADXL330 {
  public:
    ADXL330(Aiko::Device::MCP320x& adc);
    int readX();
    int readY();
    int readZ();
      
  private:
    void setup();
    
    bool isSetUp_;
    Aiko::Device::MCP320x *adc_;
};
