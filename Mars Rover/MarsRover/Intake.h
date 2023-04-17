#ifndef Intake_h
#define Intake_h
#include "Arduino.h" 
#include "ControlledMotor.h" 

class Intake {
public:
    Intake(int pin_intake_control1, int pin_intake_control2, int pin_intake_speed, int pin_plunger_control1, int pin_plunger_control2, int pin_plunger_speed);
    void setIntakePower(float power);
    void setPlungerPower(float power);
    float clamp(float input, float min, float max);
    void loop();
private: 
    int _analogConstant = 255;
    float _intakePower;
    float _plungerPower;
    ControlledMotor _intakeMotor;
    ControlledMotor _plungerMotor;
};

#endif