/*
 Name:		Testing_Rig.ino
 Created:	3/20/2024 3:09:07 PM
 Author:	Elliot Winterbottom [ID: 10918169]
*/

#include "Wire.h"
#include <Adafruit_DRV2605.h>


Adafruit_DRV2605 drv; // driver board object.
#define TCAADDR 0x70 // I2C multiplexer Address 

void tcaselect(uint8_t i) { // function selects address of component on multiplexer based on port number. 
    if (i > 7) return;

    Wire.beginTransmission(TCAADDR); //the code from this function was taken from: https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/arduino-wiring-and-test
    Wire.write(1 << i);
    Wire.endTransmission();
}

// the setup function runs once when you press reset or power the board
void setup() 
{

}

// the loop function runs over and over again until power down or reset
void loop() 
{
  
}
