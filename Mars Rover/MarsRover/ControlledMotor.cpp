#include <Arduino.h>
#include "ControlledMotor.h"

ControlledMotor::ControlledMotor(int controlPin1, int controlPin2) {
    _pin_control1 = controlPin1;
    _pin_control2 = controlPin2;
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
}

ControlledMotor::ControlledMotor(int controlPin1, int controlPin2, bool inverted) {
    _pin_control1 = controlPin1;
    _pin_control2 = controlPin2;
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    if (inverted) {
        _inversionValue = -1;
    }
    else {
        _inversionValue = 1;
    }
}

void ControlledMotor::setPower(float power) {
    int pwmDutyCycle = (int) abs(round(power * _pwmCoeff));
    Serial.println(power);
    if (power * _inversionValue >= 0) {
        analogWrite(_pin_control1, pwmDutyCycle);
        analogWrite(_pin_control2, 0);
    }
    else {
        analogWrite(_pin_control1, 0);
        analogWrite(_pin_control2, pwmDutyCycle);
    }
}
