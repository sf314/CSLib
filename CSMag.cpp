//
//  CSMag.cpp
//
//
//  Created by Tyler Lanes on 16/09/2016.
//
//
#include <Arduino.h>
#include <Wire.h>
#include <CSMag.h>

/*
Required:
Prior:
 #include <Wire.h>
 #include <CSMag.h>
 CSMag mag;
In setup():
 Wire.begin();
 mag.config();
In loop():
 mag.readx()
 
*/

#define magaddress 0x0E //
int CSMag::initX = 0;
int CSMag::initY = 0;
int CSMag::initZ = 0;
bool CSMag::debugMode = false; // override this in setup() to debug

void CSMag::config(void)
{
    debug("CSMag.config():");
    debug("\tEnabling auto-resets");
    Wire.beginTransmission(0x0E); // transmit to device 0x0E
    Wire.write(0x11);              // cntrl register2
    Wire.write(0x80);              // send 0x80, enable auto resets
    Wire.endTransmission();       // stop transmitting

    delay(15);
    
    debug("\tSetting to active mode");
    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x10);              // cntrl register1
    Wire.write(1);                 // send 0x01, active mode
    Wire.endTransmission();       // stop transmitting

    delay(15);
    calibrate(); // I am dumb
}

int CSMag::readx(void)
{
    int xl = 0;
    int xh = 0;  //define the MSB and LSB. Initialized to remove error

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x01);              // x MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        xh = Wire.read(); // receive the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x02);              // x LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        xl = Wire.read(); // receive the byte
    }

    int xout = (xl|(xh << 8)); //concatenate the MSB and LSB
    return xout - initX;
}

int CSMag::ready(void)
{
    int yl = 0;
    int yh = 0;  //define the MSB and LSB

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x03);              // y MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        yh = Wire.read(); // receive the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x04);              // y LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        yl = Wire.read(); // receive the byte
    }

    int yout = (yl|(yh << 8)); //concatenate the MSB and LSB
    return yout - initY;
}

int CSMag::readz(void)
{
    int zl = 0;
    int zh = 0;  //define the MSB and LSB

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x05);              // z MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        zh = Wire.read(); // receive the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(magaddress); // transmit to device 0x0E
    Wire.write(0x06);              // z LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(magaddress, 1); // request 1 byte
    while(Wire.available())    // slave may send less than requested
    {
        zl = Wire.read(); // receive the byte
    }

    int zout = (zl|(zh << 8)); //concatenate the MSB and LSB
    return zout - initZ;
}

// **************************************
/* Calibrate Function
 Takes 20 readings from the magnetometer
 Finds the average
 Sets the average as the offset for that direction (x,y,z)
 */
// **************************************
void CSMag::calibrate() {
    
    debug("CSMag.calibrate():");

    int xSample[20];
    int ySample[20];
    int zSample[20];

    debug("\tSampling 20 times");
    for (int i = 0; i < 20; i++) { // Take 20 readings
        xSample[i] = readx();
        ySample[i] = ready();
        zSample[i] = readz();
    }

    debug("\tFinding averages");
    int sum = 0;
    for (int i = 0; i < 20; i++) { // Find average of X
        sum = sum + xSample[i];
    }
    initX = sum / 20;
    debug("\tAverage of x values:\n\t\t");
    debug(String(initiX));

    sum = 0;
    for (int i = 0; i < 20; i++) { // Find average of Y
        sum = sum + ySample[i];
    }
    initY = sum / 20;
    debug("\tAverage of y values:\n\t\t");
    debug(String(initY));

    sum = 0;
    for (int i = 0; i < 20; i++) { // Find average of Z
        sum = sum + zSample[i];
    }
    initZ = sum / 20;
    debug("\tAverage of z values:\n\t\t");
    debug(String(initZ));
}

// **************************************
/* Debug Function
 Basically takes a string and makes a call to Serial.println();
 */
// **************************************
void CSMag::debug(String s) {
    if(debugMode) {
        Serial.println(s);
    }
}
