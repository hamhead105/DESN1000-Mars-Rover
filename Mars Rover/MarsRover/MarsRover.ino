#include "Drivetrain.h"
#include "Intake.h"
#include "ControlledMotor.h"
#include "Lighting.h"
#include "UWB.h"
#include <Dabble.h>

char appData;  

String inData = "";

static int PIN_LEFT_DRIVE_CONTROL_1 = A2;
static int PIN_LEFT_DRIVE_CONTROL_2 = A3;
static int PIN_RIGHT_DRIVE_CONTROL_1 = A0;
static int PIN_RIGHT_DRIVE_CONTROL_2 = A1;

static int PIN_INTAKE_CONTROL_1 = 8;
static int PIN_INTAKE_CONTROL_2 = 9;
static int PIN_PLUNGER_CONTROL_1 = 10;
static int PIN_PLUNGER_CONTROL_2 = 11;

//HM10 on pins 2,3 for Dabble

UWB uwb = UWB();
Drivetrain drivetrain = Drivetrain(PIN_LEFT_DRIVE_CONTROL_1, PIN_LEFT_DRIVE_CONTROL_2, PIN_RIGHT_DRIVE_CONTROL_1, PIN_RIGHT_DRIVE_CONTROL_2);
Intake intake = Intake(PIN_INTAKE_CONTROL_1, PIN_INTAKE_CONTROL_2, PIN_PLUNGER_CONTROL_1, PIN_PLUNGER_CONTROL_2);

void setup() {
    // put your setup code here, to run once:
    Dabble.begin(9600); 
    Serial.begin(115200);
    Serial.println("start Hm10");
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    uwb.setup();
}

void loop() {
  uwb.loop();
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    Serial.println("forward");
    drivetrain.tankDrive(1, 1);
  }
  else if (GamePad.isRightPressed()) {
    drivetrain.tankDrive(1, -1);
  }
  else if (GamePad.isLeftPressed()) {
    drivetrain.tankDrive(-1, 1);
  }
  else if (GamePad.isDownPressed()) {
    drivetrain.tankDrive(-0.7, -0.7);
  }
  else {
    drivetrain.tankDrive(0, 0);
  }
  drivetrain.loop();

  // Intake controls
  if (GamePad.isTrianglePressed()) {
    intake.setIntakePower(1);
  }
  else if (GamePad.isCrossPressed()) {
    intake.setIntakePower(-1);
  }
  else {
    intake.setIntakePower(0);
  }

  // Plunger controls
  if (GamePad.isSquarePressed()) {
    intake.setPlungerPower(1);
  }
  else if (GamePad.isCirclePressed()) {
    intake.setPlungerPower(-1);
  }
  else {
    intake.setPlungerPower(0);
  }
  intake.loop();
}

void serialEvent() {
  if (Serial.available() > 0) {
    uwb.readSerialEvent(Serial.read());
  }
}
