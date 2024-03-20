/*
 Name:		Testing_Rig.ino
 Created:	3/20/2024 3:09:07 PM
 Author:	Elliot Winterbottom [ID: 10918169]
*/

#include "Wire.h"
#include <Adafruit_DRV2605.h>


Adafruit_DRV2605 drv; // driver board object.
#define TCAADDR 0x70 // I2C multiplexer Address 
#define RTPMODE 5

const uint8_t MAXRTP = 120; // max value actually ~128
const uint8_t MIDRTP = 100;
const uint8_t MINRTP = 0;

const uint8_t UPPERMOTOR = 1; // motor connected to port 1 will always be placed on the upper portion of arm 
const uint8_t LOWERMOTOR = 0; // motor connected to port 0 will always be placed on the lower portion of arm 

void tcaselect(uint8_t i) { // function selects address of component on multiplexer based on port number. 
    if (i > 7) return;

    Wire.beginTransmission(TCAADDR); //the code from this function was taken from: https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/arduino-wiring-and-test
    Wire.write(1 << i);
    Wire.endTransmission();
}

void setmotor(uint8_t portNumber, bool ONOFF) 
{
    tcaselect(portNumber);
    if (ONOFF == 1) 
    {
        drv.setRealtimeValue(MIDRTP);
    }
    else if(ONOFF == 0)
    {
        drv.setRealtimeValue(MINRTP);
    }

}


// the setup function runs once when you press reset or power the board
void setup() 
{
    while (!Serial); // check if serial is working 
    Wire.begin(); // begin I2C comms
    Serial.begin(115200);


    Serial.println("TCA-Scanner ready! "); 

    tcaselect(0); // select port to find driver board.

    if(!drv.begin())// due to multiplexing, code treats driver boards like a single board.
    {
        Serial.println(" Driverboard boot up failed"); // displays error message if board is unvavialable 
        while (1);
    }

    for (uint8_t t = 0; t < 8; t++) { //the code from this function was taken from and modified: https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/arduino-wiring-and-test
        tcaselect(t);
        Serial.print("TCA Port #"); Serial.println(t);

        for (uint8_t addr = 0; addr <= 127; addr++) {
            if (addr == TCAADDR) continue; // skip over multiplexer address 

            Wire.beginTransmission(addr);
            if (!Wire.endTransmission()) {
                Serial.print("Found I2C 0x");  Serial.println(addr, HEX); // check for devices on each port
                drv.setMode(RTPMODE); // if the device is a drv then set it's mode to RTP mode 
                drv.setRealtimeValue(00); // makes sure that motor is turned off 
            }
        }
    }

}

// the loop function runs over and over again until power down or reset
void loop() 
{
   
}
