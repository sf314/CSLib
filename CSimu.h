// Inertial Measurement Unit class definition
// 10DOF
// CSimu.h
// may need float rather than int

#include "Arduino.h"

// From Adafruit folder (messy, yes!)
#include "Adafruit/Adafruit_10DOF.h"
#include "Adafruit/Adafruit_BMP085_U.h"
#include "Adafruit/Adafruit_BMP085_U.h"
#include "Adafruit/Adafruit_L3GD20_U.h"
#include "Adafruit/Adafruit_LSM303_U.h"
#include "Adafruit/Adafruit_Sensor.h"


class CSimu {
public:
    static boolean debugMode();
    int accelX();
    int accelY();
    int accelZ();

    int gyroX();
    int gyroY();
    int gyroZ();

    int magX();
    int magY();
    int magZ();

    int temp(); // temp or pressure?

private:
    void calibrate();
    void debug(String s);
}
