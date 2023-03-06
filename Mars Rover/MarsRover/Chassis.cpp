#include <Arduino.h>
#include "Chassis.h"

Chassis::Chassis(int pin_leftDrive, int pin_rightDrive) {
    _pin_leftDrive = pin_leftDrive;
    _pin_rightRight = pin_rightDrive;
}

void Chassis::drive(float leftInput, float rightInput) {
    _leftDrive = leftInput;
    _rightDrive = rightInput;
}

void Chassis::loop() {
    analogWrite(_pin_leftDrive, _leftDrive);
}