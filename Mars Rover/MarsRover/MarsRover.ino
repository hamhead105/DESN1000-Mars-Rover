#include "Drivetrain.h"
#include "ControlledMotor.h"
#include "Lighting.h"

static int PIN_LEFT_DRIVE_CONTROL_1 = 9;
static int PIN_LEFT_DRIVE_CONTROL_2 = 10;

static int PIN_TESTLIGHT = A0;

Lighting light = Lighting(PIN_TESTLIGHT);
Drivetrain drivetrain = Drivetrain(PIN_LEFT_DRIVE_CONTROL_1, PIN_LEFT_DRIVE_CONTROL_2, 1, 2);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    drivetrain.tankDrive(0, 0);
}

void loop() {
    drivetrain.loop();
}
