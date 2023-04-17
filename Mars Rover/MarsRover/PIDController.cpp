/*
 * PID Controller class inspired by DESN1000 Lecture notes, written by Peter Jung
 */

#include <Arduino.h>
#include "PIDController.h"

/*
 * Constructor for PID Controller
 * @param kP proportional constant
 * @param kI integral constant
 * @param kD derivative constant
 */
PIDController::PIDController(float kP, float kI, float kD) {
    _kP = kP;
    _kI = kI;
    _kD = kD;
}

/*
 * get the output for this PID controller.
 * @param error the error for a given frame
 * @return the PID output
 */
float PIDController::getOutput(float error) {
    float deltaTime = millis() - lastTime;
    lastTime = millis();
    float output;
    if (deltaTime > 0)
    {
        errorAccumulation += error * deltaTime;
        errorDerivative = (error - lastError) * deltaTime;
    }
    else
    {
        errorDerivative = 0;
    }
    output = (error * _kP) + (errorAccumulation * _kI) + (errorDerivative * _kD);
    return output;
}