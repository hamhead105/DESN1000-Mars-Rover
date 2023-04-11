#include <Arduino.h>
#include "Intake.h"

Intake::Intake(int pin_intake_control1, int pin_intake_control2, int pin_intake_speed, int pin_plunger_control1, int pin_plunger_control2, int pin_plunger_speed) :
    _intakeMotor(pin_intake_control1, pin_intake_control2, pin_intake_speed), 
    _plungerMotor(pin_plunger_control1, pin_plunger_control2, pin_plunger_speed){
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