#include <Arduino.h>
#include "Intake.h"

Intake::Intake(int pin_upperMotor_control1, int pin_upperMotor_control2, int pin_lowerMotor_control1, int pin_lowerMotor_control2) :
    _intakeMotor(pin_upperMotor_control1, pin_upperMotor_control2), 
    _plungerMotor(pin_lowerMotor_control1, pin_lowerMotor_control2){
}

void Intake::setIntakePower(float power) {
    _intakePower = power;
}

void Intake::setPlungerPower(float power) {
    _plungerPower = power;
}

void Intake::loop() {
    _intakeMotor.setPower(_intakePower);
    _plungerMotor.setPower(_plungerPower);
}

float Intake::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}