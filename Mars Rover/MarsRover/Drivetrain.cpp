#include <Arduino.h>
#include "Drivetrain.h"

Drivetrain::Drivetrain(int pin_leftDrive_control1, int pin_leftDrive_control2, int pin_leftDrive_speed_control, int pin_rightDrive_control1, int pin_rightDrive_control2, int pin_rightDrive_speed_control) :
    _leftMotor(pin_leftDrive_control1, pin_leftDrive_control2, pin_leftDrive_speed_control, false), 
    _rightMotor(pin_rightDrive_control1, pin_rightDrive_control2, pin_rightDrive_speed_control, false){
}

void Drivetrain::tankDrive(float leftInput, float rightInput) {
    _leftDrive = leftInput;
    _rightDrive = rightInput;
}

void Drivetrain::drive(float forwardInput, float turnInput) {
    _leftDrive = clamp(forwardInput + turnInput, -1, 1) * _analogConstant;
    _rightDrive = clamp(forwardInput - turnInput, -1, 1) * _analogConstant;
}

void Drivetrain::loop() {
    _leftMotor.setPower(_leftDrive);
    _rightMotor.setPower(_rightDrive);
}

float Drivetrain::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}