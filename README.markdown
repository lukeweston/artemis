ARTEMIS: Arduino Rocket Telemetry Module and Instrumentation System
===================================================================

*more documentation to come later*

Hardware
--------

(I'm having some trouble learning how to make the markdown code block work properly...
...please bear with me here.)

                Hardware Arduino pin assignments:
    
                Function                                Mega pin                Duemilanove pin 
    
                UART Rx from XBee:                      Digital 0 (RX0)         (0) 
                UART Tx to XBee:                        Digital 1 (TX0)         (1) 
                1-Wire (DS18B20)                        Digital 2               (2) 
                Accelerometer (ADXL330) self-test       Digital 3               (3) 
    
                LDR 1:                                  Analog 0                (Analog 0)
                LDR 2:                                  Analog 1                (Analog 1)
                Battery voltage:                        Analog 7
    
                UART Tx to GPS module:                  18 (TX1)
                UART Rx from GPS module:                19 (RX1)
    
                I2C serial data for DS1307 RTC:         20 (SDA)
                I2C clock:                              21 (SCL)
    
                Atmel DataFlash SPI chip select:        46  
                MCP3204 ADC (5 V) SPI chip select:      47  
                MCP3208 ADC (3.3 V) SPI chip select:    48  
    
                SPI Master-in-slave-out (MISO):         50  
                SPI Master-out-slave-in (MOSI):         51  
                SPI clock (SCK):                        52  

(Note that pins 20, 21, 50 51 and 52 are hard-wired to the microcontroller's
internal hardware for those interface protocols, and cannot be changed.)

Although it is designed to be used with an Arduino Mega, some pins (The DS18B20, the LDRs and 
the XBee module) can be tested with the board plugged into an Arduino Duemilanove.

On future PCBs it would be nice to change the battery voltage measurement input from Analog 7 to Analog 5,
to allow this function to be tested on an Arduino Duemilanove. This was just a little bit of laziness on the 
part of the PCB designer, since pin 7 is the one closest to that part of the layout.

*The accelerometer self-test should be used with caution* since it is plugged straight into the microcontroller
and the accelerometer is a 3.3V device. Perhaps PWMing it would be appropriate - I should have added a capacitor
on this pin on the board to smooth off the PWM.


Software
--------

Clone this into your Arduino projects directory (~/Documents/Arduino on the Mac), and you should be able to open it in your Arduino IDE, build it, and run it.

The following bits are working:

- ADCs
- Accelerometer
- MAP sensor
- Real-time clock
- Temperature

The following bits still need to be done:

- Flash storage
- GPS

From there we have to work out formats for data storage and transmission.

