/*
 * ControlledMotor class written by Peter Jung 2023, for DESN1000 project.
 * Controls a motor using an H-Bridge using 3 pins: 2 for direction, 1 for speed.
 */

#include <Arduino.h>
#include "ControlledMotor.h"

/*
 * Base constructor for Controlled Motor
 * @param controlPin1 the pin corresponding to logic pin 1
 * @param controlPin2 the pin corresponding to logic pin 2
 * @param controlPinSpeed the pin corresponding to the speed / power pin
 */
ControlledMotor::ControlledMotor(int controlPin1, int controlPin2, int controlPinSpeed) {
    _pin_control1 = controlPin1;
    _pin_control2 = controlPin2;
    _pin_controlSpeed = controlPinSpeed;
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    pinMode(controlPinSpeed, OUTPUT);
}

/*
 * Constructor for whether motor is inverted
 * @param controlPin1 the pin corresponding to logic pin 1
 * @param controlPin2 the pin corresponding to logic pin 2
 * @param controlPinSpeed the pin corresponding to the speed / power pin
 * @param inverted whether the motor should be inverted
 */
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

/*
 * Returns the input, clamped between two values, when 1 is clamped between 2 and 5, 2 is returned.
 * @param input the value that should be clamped
 * @param min the minimum value 
 * @param max the maximum value
 * @return the clamped value
 */
float ControlledMotor::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}

/*
 * Converts a motor speed of -1 -> 1 and applies to motor using PWM.
 * @param power a power value of -1 - 1
 */
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

