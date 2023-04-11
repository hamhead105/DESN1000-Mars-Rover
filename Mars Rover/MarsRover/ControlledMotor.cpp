#include <Arduino.h>
#include "ControlledMotor.h"

ControlledMotor::ControlledMotor(int controlPin1, int controlPin2, int controlPinSpeed) {
    _pin_control1 = controlPin1;
    _pin_control2 = controlPin2;
    _pin_controlSpeed = controlPinSpeed;
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    pinMode(controlPinSpeed, OUTPUT);
}

ControlledMotor::ControlledMotor(int controlPin1, int controlPin2, int controlPinSpeed, bool inverted) {
    _pin_control1 = controlPin1;
    _pin_control2 = controlPin2;
    _pin_controlSpeed = controlPinSpeed;
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    pinMode(controlPinSpeed, OUTPUT);
    if (inverted) {
        _inversionValue = -1;
    }
    else {
        _inversionValue = 1;
    }
}


float ControlledMotor::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}

void ControlledMotor::setPower(float power) {
    int pwmDutyCycle = (int) clamp(abs(round(power * _pwmCoeff)), 0, 255);
    
    analogWrite(_pin_controlSpeed, pwmDutyCycle);
    if (power * _inversionValue >= 0) {
        analogWrite(_pin_control1, 255);
        analogWrite(_pin_control2, 0);
    }
    else {
        analogWrite(_pin_control1, 0);
        analogWrite(_pin_control2, 255);
    }
}

