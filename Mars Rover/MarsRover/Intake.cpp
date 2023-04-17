/*
 * Intake class written by Peter Jung 2023, for DESN1000 project.
 * Handles the digging claw or intake and the plunger system on the Mars Rover.
 */

#include <Arduino.h>
#include "Intake.h"

/*
 * Base constructor
 * @param pin_intake_control1 pin for logic pin 1 of intake
 * @param pin_intake_control2 pin for logic pin 2 of intake
 * @param pin_intake_speed pin for power or speed pin for intake
 * @param pin_plunger_control1 pin for logic pin 1 of plunger
 * @param pin_plunger_control2 pin for logic pin 2 of plunger
 * @param pin_plunger_speed pin for power or speed pin for plunger
 */
Intake::Intake(int pin_intake_control1, int pin_intake_control2, int pin_intake_speed, int pin_plunger_control1, int pin_plunger_control2, int pin_plunger_speed) :
    _intakeMotor(pin_intake_control1, pin_intake_control2, pin_intake_speed), 
    _plungerMotor(pin_plunger_control1, pin_plunger_control2, pin_plunger_speed){
}

/*
 * Set the power of the intake
 * @param power input power value from -1 to 1
 */
void Intake::setIntakePower(float power) {
    _intakePower = power;
}

/*
 * Set the power of the plunger
 * @param power input power value from -1 to 1
 */
void Intake::setPlungerPower(float power) {
    _plungerPower = power;
}

/*
 * Called every loop cycle, update the motor inputs for the intake and plunger.
 */
void Intake::loop() {
    _intakeMotor.setPower(_intakePower);
    _plungerMotor.setPower(_plungerPower);
}

/*
 * Returns the input, clamped between two values, when 1 is clamped between 2 and 5, 2 is returned.
 * @param input the value that should be clamped
 * @param min the minimum value 
 * @param max the maximum value
 * @return the clamped value
 */
float Intake::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}