#include <Arduino.h>
#include "Drivetrain.h"

Drivetrain::Drivetrain(int pin_leftDrive, int pin_rightDrive) {
    _pin_leftDrive = pin_leftDrive;
    _pin_rightRight = pin_rightDrive;
}

void Drivetrain::drive(float leftInput, float rightInput) {
    _leftDrive = leftInput;
    _rightDrive = rightInput;
}

void Drivetrain::loop() {
    analogWrite(_pin_leftDrive, _leftDrive);
}