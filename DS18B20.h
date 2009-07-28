#include <OneWire.h>

class DS18B20 {
  public:    
    DS18B20(OneWire &oneWire);
    void startConversion();
    void read();
    float temperature();
    
  private:
    OneWire        *oneWire_;
    bool           isSetUp_;
    bool           deviceFound_;
    unsigned char  address_[8];
    unsigned char  data_[9];
    
    void setup();
};
