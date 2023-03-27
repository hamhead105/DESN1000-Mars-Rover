#ifndef Drivetrain_h
#define Drivetrain_h
#include "Arduino.h" 
#include "ControlledMotor.h" 

class Drivetrain {
public:
    Drivetrain(int pin_leftDrive_control1, int pin_leftDrive_control2, int pin_rightDrive_control1, int pin_rightDrive_control2);
    void tankDrive(float leftInput, float rightInput);
    void drive(float forwardInput, float turnInput);
    void driveTrain(float leftInput, float rightInput);
    float clamp(float input, float min, float max);
    void loop();
private: 
    int _analogConstant = 255;
    float _leftDrive;
    float _rightDrive;
    ControlledMotor _leftMotor;
    ControlledMotor _rightMotor;
};

#endif