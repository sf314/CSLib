//CSMag.cpp
//Tyler Lanes & Stephen Flores

#include <Arduino.h>

// If Wire.available() resolves false prior to setting
// significant bits, then the values for x,y,z will
// resolve to zero (they're initialized to zero).
// This was done to remove the compiler error for
// uninitialized variables.


class CSMag {
public:
    static boolean debugMode;
    void config(void);
    int readx();
    int ready();
    int readz();
    
private:
    //static int magaddress;
    void calibrate();
    void debug(String s);
    static int initX;
    static int initY;
    static int initZ;
    
};
