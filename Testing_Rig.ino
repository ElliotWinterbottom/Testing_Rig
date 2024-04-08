/*
 Name:    Testing_Rig.ino
 Created: 3/20/2024 3:09:07 PM
 Author:  Elliot Winterbottom [ID: 10918169]
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
const int SIZE_OF_TEST_ARRAY = 45;
const int TEST_ARRAY[SIZE_OF_TEST_ARRAY] = { 1 ,1 ,1 ,1 ,1, 1 ,1 ,1 ,1 ,1, 1 ,1 ,1 ,1 ,1, 2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,3,3 ,3 ,3 ,3 ,3,3 ,3 ,3 ,3 ,3 }; // 5 tests for each effect. This array is const as test procedure should remain unchanged
int randomised_test_array[SIZE_OF_TEST_ARRAY];
bool testType = 0; // 0 for phantom sensation, 1 for apparent motion 

int testno = 0;
int inputSOA = 0;// value ranges from 0 to 1024

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
    else if (ONOFF == 0)
    {
        drv.setRealtimeValue(MINRTP);
    }

}


void phantom_sensation_playback(int motor_selector) // based on input will give a 3 second playback of motors: 0 - neither, 1 - upper, 2 - lower, 3 - both.
{

    if (motor_selector == 0)
    {
        setmotor(UPPERMOTOR, 0);
        setmotor(LOWERMOTOR, 0);
        delay(3000);
    }
    else if (motor_selector == 1)
    {
        delay(100);
        setmotor(UPPERMOTOR, 1);
        setmotor(LOWERMOTOR, 0);
        delay(3000);
        setmotor(UPPERMOTOR, 0);
        setmotor(LOWERMOTOR, 0);
    }
    else if (motor_selector == 2)
    {
        delay(100);
        setmotor(UPPERMOTOR, 0);
        setmotor(LOWERMOTOR, 1);
        delay(3000);
        setmotor(UPPERMOTOR, 0);
        setmotor(LOWERMOTOR, 0);
    }
    else if (motor_selector == 3)
    {
        delay(100);
        setmotor(UPPERMOTOR, 1);
        setmotor(LOWERMOTOR, 1);
        delay(3000);
        setmotor(UPPERMOTOR, 0);
        setmotor(LOWERMOTOR, 0);
    }
}

void apparent_tactile_motion_playback(int duration, int SOA)
{
    int playbackStart = millis();
    int secondMotorStart = playbackStart + SOA; // first motor is UPPER, second motor is LOWER

    int firstMotorEnd = playbackStart + duration;
    int secondMotorEnd = secondMotorStart + duration;

    while (1)
    {
        if (millis() <= firstMotorEnd)
        {
            setmotor(UPPERMOTOR, 1);
        }
        else
        {
            setmotor(UPPERMOTOR, 0);
        }
        if (millis() <= secondMotorEnd && millis() >= secondMotorStart)
        {
            setmotor(LOWERMOTOR, 1);
        }
        else if (millis() > secondMotorEnd)
        {
            setmotor(LOWERMOTOR, 0);
            return; // as soon as the second motor is done end the playback function
        }

    }
}

void test_array_scrambler()
{
    for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++) // pulling the values from const so that they can be shuffled 
    {
        randomised_test_array[i] = TEST_ARRAY[i];

    }
    for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++) // code for this function taken from https://forum.arduino.cc/t/shuffle-an-array-of-ints/333494/2
    {
        int n = random(0, SIZE_OF_TEST_ARRAY);
        int temp = randomised_test_array[n];
        randomised_test_array[n] = randomised_test_array[i];
        randomised_test_array[i] = temp;
    }
}

// the setup function runs once when you press reset or power the board

void setup()
{
    pinMode(3, INPUT_PULLUP);

    while (!Serial); // check if serial is working 
    Wire.begin(); // begin I2C comms
    Serial.begin(115200);
    Serial.println("please enter the test type: 0 for phantom sensation or 1 for apparent tactile motion");
    testType = Serial.read();

    Serial.println("TCA-Scanner ready! ");

    tcaselect(0); // select port to find driver board.

    if (!drv.begin())// due to multiplexing, code treats driver boards like a single board.
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


    Serial.println("_______");
    for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++) // pulling the values from const so that they can be shuffled 
    {
        Serial.println(TEST_ARRAY[i]);
    }
    Serial.println("_______");
}



// the loop function runs over and over again until power down or reset
void loop() {

    testno++;
    switch (int(testType))
    {
    case 0:
        test_array_scrambler();
        Serial.println(testno);
        for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++)
        {
            while (digitalRead(3) == HIGH)
            {
                delay(100);
            }
            phantom_sensation_playback(randomised_test_array[i]);
        }

        for (int i = 0; i < SIZE_OF_TEST_ARRAY; i++)
        {
            switch (randomised_test_array[i])
            {
            case 1:
                Serial.println("upper");
                break;
            case 2:
                Serial.println("lower");
                break;
            case 3:
                Serial.println("both");
                break;
            }
        }
        break;


    case 1:

        while (digitalRead(3) == HIGH)
        {
            delay(100);
        }
        inputSOA = map(analogRead(A0), 0, 1024, 0, 200);
        apparent_tactile_motion_playback(160, inputSOA);
        break;


    default:
        break;
    }
}
