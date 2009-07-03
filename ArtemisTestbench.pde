
/*  Some simple test code for the ARTEMIS board, to take the temperature measurement from the DS18B20 sensor as well
    as the analog reading of the light level from the two LDRs, and display the values from these sensors on the
    serial terminal, as a simple test to confirm that the board, or at least these sensors, are working at the
    hardware level.
    
    This code was developed, and works, with the ARTEMIS board plugged into an Arduino Duemilanove, not an
    Arduino Mega. However, it's simply a matter of knowing the appropriate pin numbers to use.
    
    This simple code borrows heavily from the example code supplied for the DallasTemperature library by Miles Burton,
    as available on the Arduino Playground page.
*/

#include <DallasTemperature.h>

DallasTemperature tempSensor;

void setup(void) {
  // initialize devices
  Serial.begin(9600);   // start serial port
  tempSensor.begin(2); // The ARTEMIS board, plugged into an Arduino Duemilanove, brings the 1-Wire bus to pin 2.                        
}

void loop(void) {

    // Ask the library whether the device is valid
    switch(tempSensor.isValid())
    {
        case 1:
            Serial.println("Invalid CRC");
			tempSensor.reset(); // Attempts to redetect IC
            return;
        case 2:
            Serial.println("Not a valid device");
			tempSensor.reset();
            return;
    }

  Serial.print("Temperature: ");
  Serial.print(tempSensor.getTemperature());
  Serial.print(" C");
  Serial.println();
  
  Serial.print("LDR 1: ");
  Serial.print(analogRead(0));
  Serial.print("/1024");
  Serial.println();
  
  Serial.print("LDR 2: ");
  Serial.print(analogRead(1));
  Serial.print("/1024");
  Serial.println("\n");
 
  delay(1000);
  
}
