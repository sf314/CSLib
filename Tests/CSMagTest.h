// Test class for the magnetometer

#include "Arduino.h"


class CSMagTest {
public:
    static boolean debugMode;
    static boolean rawOutput;
    void config(void);
    int readx();
    int ready();
    int readz();

private:
    void debug(String s);
    //static int magaddress;
    void calibrate();
    // void debug(String s);
    // static int initX;
    // static int initY;
    // static int initZ;
    // Private stuff not needed
}
