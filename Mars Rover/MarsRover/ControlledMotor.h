#ifndef ControlledMotor_h
#define ControlledMotor_h
#include "Arduino.h" 

class ControlledMotor {
public:
    ControlledMotor(int controlPin1, int controlPin2, int controlPinSpeed);
    ControlledMotor(int controlPin1, int controlPin2, int controlPinSpeed, bool inverted);
    void setPower(float power);
    float clamp(float input, float min, float max);
private:
    int _pin_control1;
    int _pin_control2;
    int _pin_controlSpeed;
    int _inversionValue = 1;
    int _pwmCoeff = 255;
};

#endif