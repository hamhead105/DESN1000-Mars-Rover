#include "Chassis.h"

static int PIN_LEFT_DRIVE = 3;
static int PIN_RIGHT_DRIVE = 4;

Chassis chassis = Chassis(PIN_LEFT_DRIVE, PIN_RIGHT_DRIVE);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  chassis.drive(1, 1);
}
