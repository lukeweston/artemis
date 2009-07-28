#include <AikoDeviceMCP320x.h>
#include <AikoEvents.h>
#include <Wire.h>
#include <OneWire.h>
#include "ADXL330.h"
#include "DS1307.h"
#include "DS18B20.h"
#include "MPX4101A.h"

using namespace Aiko;

Device::MCP320x   adc5v(47);
Device::MCP320x   adc3v(48);
ADXL330           accelerometer(adc3v);
MPX4101A          mapSensor(adc5v);
DS1307            clock;
OneWire           oneWire(2);
DS18B20           temperatureSensor(oneWire);

void reportNodeName() {
  Serial.println("(nodeName= artemis_1)");
}

void readClock() {
  clock.read();
  
  Serial.print("(clock= ");
  if (clock.hour_ < 10) Serial.print('0');
  Serial.print((int)clock.hour_);
  if (clock.minute_ < 10) Serial.print('0');
  Serial.print((int)clock.minute_);
  if (clock.second_ < 10) Serial.print('0');
  Serial.print((int)clock.second_);
  Serial.println(")");
}

void readAccelerometer() {
  int x = accelerometer.readX();
  int y = accelerometer.readY();
  int z = accelerometer.readZ();
  
  Serial.print("(acceleromter_x= ");
  Serial.print(x);
  Serial.println(")");
  
  Serial.print("(acceleromter_y= ");
  Serial.print(y);
  Serial.println(")");
  
  Serial.print("(acceleromter_z= ");
  Serial.print(z);
  Serial.println(")");
}

void readMapSensor() {
  Serial.print("(barometer= ");
  Serial.print(mapSensor.readPressure());
  Serial.println(")");
}

void readLDRs() {
  Serial.print("(light_a= ");
  Serial.print(analogRead(0));
  Serial.println(")");
  Serial.print("(light_b= ");
  Serial.print(analogRead(1));
  Serial.println(")");
}

void readVoltage() {
  float voltage = (float)analogRead(7) * (5.0 / 1024.0);
  
  Serial.print("(voltage= ");
  Serial.print(voltage);
  Serial.println(")");
}

void readTemperature() {
  temperatureSensor.read();
  
  Serial.print("(temperature= ");
  Serial.print(temperatureSensor.temperature());
  Serial.println(")");
  
  temperatureSensor.startConversion();
}

void setup() {
  clock.second_ = 0;
  clock.minute_ = 1;
  clock.hour_   = 2;
  clock.dayOfWeek_ = 3;
  clock.dayOfMonth_ = 4;
  clock.month_ = 5;
  clock.year_ = 6;
  clock.set();
  
  Serial.begin(9600);
  Events.addHandler(reportNodeName, 1000);
  Events.addHandler(readClock, 1000);
  Events.addHandler(readAccelerometer, 100);
  Events.addHandler(readMapSensor, 100);
  Events.addHandler(readLDRs, 100);
  Events.addHandler(readVoltage, 100);
  Events.addHandler(readTemperature, 1000);
}

void loop() {
  Events.loop();
}
