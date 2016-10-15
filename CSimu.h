// Inertial Measurement Unit class definition
// 10DOF
// CSimu.h
// may need float rather than int


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
