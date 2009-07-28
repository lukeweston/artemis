class DS1307 {
  public:
    DS1307();
    void read();
    void set();
    
    unsigned char second_, minute_, hour_, dayOfWeek_, dayOfMonth_, month_, year_;
    
  private:
    bool isSetUp_;
    
    unsigned char bcdToDecimal(unsigned char x);
    unsigned char decimalToBCD(unsigned char x);
    void setup();
};
