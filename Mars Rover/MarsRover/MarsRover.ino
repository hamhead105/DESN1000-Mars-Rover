#include "Drivetrain.h"
#include "ControlledMotor.h"
#include "Lighting.h"
#include "UWB.h"
#include <Dabble.h>

char appData;  

String inData = "";

static int PIN_LEFT_DRIVE_CONTROL_1 = A0;
static int PIN_LEFT_DRIVE_CONTROL_2 = A1;

static int PIN_TESTLIGHT = A0;

UWB uwb = UWB();
Lighting light = Lighting(PIN_TESTLIGHT);
Drivetrain drivetrain = Drivetrain(PIN_LEFT_DRIVE_CONTROL_1, PIN_LEFT_DRIVE_CONTROL_2, 10, 11);

void setup() {
    // put your setup code here, to run once:
    Dabble.begin(9600); 
    Serial.begin(115200);
    Serial.println("start Hm10");
    pinMode(9, OUTPUT);

    uwb.setup();
}

void loop() {
  uwb.loop();
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

void serialEvent() {
  if (Serial.available() > 0) {
    uwb.readSerialEvent(Serial.read());
  }
}
