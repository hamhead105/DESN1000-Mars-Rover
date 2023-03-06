#ifndef Chassis_h
#define Chassis_h
#include "Arduino.h" 

class Chassis {
public:
    Chassis(int pin_leftDrive, int pin_rightDrive);
    void drive(float leftInput, float rightInput);
    void loop();
private:
    int _pin_leftDrive;
    int _pin_rightRight;
    float _leftDrive;
    float _rightDrive;
};

#endif