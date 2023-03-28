

#include "Drivetrain.h"
#include "ControlledMotor.h"
#include "Lighting.h"
#include <Dabble.h>

char appData;  

String inData = "";

static int PIN_LEFT_DRIVE_CONTROL_1 = 9;
static int PIN_LEFT_DRIVE_CONTROL_2 = 10;

static int PIN_TESTLIGHT = A0;

Lighting light = Lighting(PIN_TESTLIGHT);
Drivetrain drivetrain = Drivetrain(PIN_LEFT_DRIVE_CONTROL_1, PIN_LEFT_DRIVE_CONTROL_2, 10, 11);

void setup() {
    // put your setup code here, to run once:
     Dabble.begin(9600); 
    Serial.begin(9600);
    Serial.println("start Hm10");
    pinMode(9, OUTPUT);
}

void loop() {
  Dabble.processInput();
  if (GamePad.isUpPressed()) {
    drivetrain.tankDrive(1, 1);
  }
  else if (GamePad.isDownPressed()) {
    drivetrain.tankDrive(-0.7, -0.7);
  }
  else {
    drivetrain.tankDrive(0, 0);
  }
  drivetrain.loop();
 

}
