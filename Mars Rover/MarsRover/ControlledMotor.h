#ifndef ControlledMotor_h
#define ControlledMotor_h
#include "Arduino.h" 

class ControlledMotor {
public:
    ControlledMotor(int controlPin1, int controlPin2);
    ControlledMotor(int controlPin1, int controlPin2, bool inverted);
    void setPower(float power);
private:
    int _pin_control1;
    int _pin_control2;
    int _inversionValue = 1;
    int _pwmCoeff = 255;
};

#endif