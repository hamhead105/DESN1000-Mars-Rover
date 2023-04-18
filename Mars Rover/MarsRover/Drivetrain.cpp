/*
 * Drivetrain class written by Peter Jung 2023, for DESN1000 project.
 * Controls the drivetrain of the Mars Rover, handling driving and controls for driving.
 */

#include <Arduino.h>
#include "Drivetrain.h"

/*
 * Base constructor for drivetrain
 */
Drivetrain::Drivetrain(int pin_leftDrive_control1, int pin_leftDrive_control2, int pin_leftDrive_speed_control, int pin_rightDrive_control1, int pin_rightDrive_control2, int pin_rightDrive_speed_control) :
    _leftMotor(pin_leftDrive_control1, pin_leftDrive_control2, pin_leftDrive_speed_control, false), 
    _rightMotor(pin_rightDrive_control1, pin_rightDrive_control2, pin_rightDrive_speed_control, false){
}

/*
 * Drive the drivetrain based on a left and right input, i.e. the power for each input directly corresponds to the power inputted
 * to the left and right motor.
 * @param leftInput the power input placed on the left motor
 * @param rightInput the power input placed on the right motor
 */
void Drivetrain::tankDrive(float leftInput, float rightInput) {
    _leftDrive = leftInput;
    _rightDrive = rightInput;
}

/*
 * Drive the drivetrain based on a forward input and an input for turning. Processes such inputs into a left and right ratio.
 * @param forwardInput the power input placed on both motors corresponding to whether the rover should go forward or back
 * @param turnInput the power input corresponding to the balance of the left and right motor to make the robot turn.
 */
void Drivetrain::drive(float forwardInput, float turnInput) {
    _leftDrive = clamp(forwardInput + turnInput, -1, 1);
    _rightDrive = clamp(forwardInput - turnInput, -1, 1);
}

/*
 * Called every loop cycle, update the power on each motor
 */
void Drivetrain::loop() {
    _leftMotor.setPower(_leftDrive * _leftDriveMultiplier);
    _rightMotor.setPower(_rightDrive * _rightDriveMultiplier);

    Serial.println("drive train power: left: " + String(_leftDrive) + " right: " + String(_rightDrive));
}

/*
 * Returns the input, clamped between two values, when 1 is clamped between 2 and 5, 2 is returned.
 * @param input the value that should be clamped
 * @param min the minimum value 
 * @param max the maximum value
 * @return the clamped value
 */
float Drivetrain::clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    } 
    else if (input < min) {
        return min;
    }
    return input;
}