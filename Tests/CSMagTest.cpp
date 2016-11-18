// Implement magnetometer test class


#include <Arduino.h>
#include "CSMagTest.h"

bool CSMagTest::debugMode;
bool CSMagTest::rawOutput;

void CSMagTest::debug(String s) {
    if (debugMode) {
        Serial.println(s);
    }
}

void CSMagTest::config() {
    // Pretend to configure device:
    debug("CSMagTest.config()");
    debug("\tEnabling auto-resets");
    debug("\tSetting to active mode");
    if (rawOutput) {
        calibrate();
    }
}

int CSMagTest::readx() {
    // Return different set of stuff depending on rawOutput flag
    int rawData[10] = {642, 632, 637, 635, 698, 623, 645, 622, 677, 645};
    int calibratedData[10] = {0, 0, 0, -12, 4, 6, 2, -3, 3, 7};

    // Choose which index to pull from
    int index = millis() % 10;

    // Fake it!
    if (rawOutput) {
        return rawData[index];
    } else {
        return calibratedData[index];
    }
}

int CSMagTest::ready() {
    // Return different set of stuff depending on rawOutput flag
    int rawData[10] = {642, 632, 637, 635, 698, 623, 645, 622, 677, 645};
    int calibratedData[10] = {0, 0, 0, -12, 4, 6, 2, -3, 3, 7};

    // Choose which index to pull from
    int index = millis() % 10;

    // Fake it!
    if (rawOutput) {
        return rawData[index];
    } else {
        return calibratedData[index];
    }
}

int CSMagTest::readz() {
    // Return different set of stuff depending on rawOutput flag
    int rawData[10] = {642, 632, 637, 635, 698, 623, 645, 622, 677, 645};
    int calibratedData[10] = {0, 0, 0, -12, 4, 6, 2, -3, 3, 7};

    // Choose which index to pull from
    int index = millis() % 10;

    // Fake it!
    if (rawOutput) {
        return rawData[index];
    } else {
        return calibratedData[index];
    }
}

void CSMagTest::calibrate() {

        debug("CSMag.calibrate():");

        int xSample[20];
        int ySample[20];
        int zSample[20];

        debug("\tSampling 20 times");
        for (int i = 0; i < 20; i++) { // Take 20 readings
            int x = readx();
            xSample[i] = x;
            int y = ready();
            ySample[i] = y;
            int z= readz();
            zSample[i] = z;
            Serial.println(String(x) + ", " + String(y) + ", " + String(z));
        }

        debug("\tFinding averages");
        int sum = 0;
        for (int i = 0; i < 20; i++) { // Find average of X
            sum = sum + xSample[i];
        }
        debug("\tAverage of x values:\n\t\t");
        debug(String(sum / 20));

        sum = 0;
        for (int i = 0; i < 20; i++) { // Find average of Y
            sum = sum + ySample[i];
        }
        debug("\tAverage of y values:\n\t\t");
        debug(String(sum / 20));

        sum = 0;
        for (int i = 0; i < 20; i++) { // Find average of Z
            sum = sum + zSample[i];
        }
        debug("\tAverage of z values:\n\t\t");
        debug(String(sum / 20));
}
