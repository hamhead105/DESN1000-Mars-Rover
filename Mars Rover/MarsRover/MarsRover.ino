/*
 * MarsRover code by Peter Jung in conjuction with Sonny Pybus. Controls a Mars Rover either autonomously through UWB or through a PS4 Controller with Bluetooth.
 * 
 * Control code written using USB Host Libraries in order to allow for control with PS4 controller.
 * Control inputs inspired by PS4BT.ino in examples of USB Host Shield 2.0 https://github.com/felis/USB_Host_Shield_2.0
 * To connect controller, hold down share and PS button at same time once script is running. Ensure controller is reset after each upload / use.
 */

#include "Drivetrain.h"
#include "Intake.h"
#include "ControlledMotor.h"
#include "Lighting.h"
#include "UWB.h"

// USB Host Libraries
#include <PS4BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

bool driverControlMode = false;

// Constants
static int PIN_LEFT_DRIVE_CONTROL_1 = 5;
static int PIN_LEFT_DRIVE_CONTROL_2 = 6;
static int PIN_LEFT_DRIVE_SPEED_CONTROL = 7;
static int PIN_RIGHT_DRIVE_CONTROL_1 = 2;
static int PIN_RIGHT_DRIVE_CONTROL_2 = 4;
static int PIN_RIGHT_DRIVE_SPEED_CONTROL = 3;

static int PIN_INTAKE_SPEED_CONTROL = A3;
static int PIN_INTAKE_CONTROL_1 = 8;
static int PIN_INTAKE_CONTROL_2 = A4;

static int PIN_PLUNGER_SPEED_CONTROL = A0;
static int PIN_PLUNGER_CONTROL_1 = A1;
static int PIN_PLUNGER_CONTROL_2 = A2;

static float PS4_STICK_CONSTANT = 122.5;
static float PS4_TRIGGER_CONSTANT = 255;

// USB Host Variables
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

char appData;  

String inData = "";

// Instantiate Subsystems
UWB uwb = UWB();
Drivetrain drivetrain = Drivetrain(PIN_LEFT_DRIVE_CONTROL_1, PIN_LEFT_DRIVE_CONTROL_2, PIN_LEFT_DRIVE_SPEED_CONTROL, PIN_RIGHT_DRIVE_CONTROL_1, PIN_RIGHT_DRIVE_CONTROL_2, PIN_RIGHT_DRIVE_SPEED_CONTROL);
Intake intake = Intake(PIN_INTAKE_CONTROL_1, PIN_INTAKE_CONTROL_2, PIN_INTAKE_SPEED_CONTROL, PIN_PLUNGER_CONTROL_1, PIN_PLUNGER_CONTROL_2, PIN_PLUNGER_SPEED_CONTROL);

// Positional control variables
float pos_x;
float pos_y;

/*
 * Initialise Rover
 */
void setup() {
  if (driverControlMode) {
    initPS4Controller();
  } else {
    uwb.setup();
  }
}

/*
 * From USB Host 2.0 PS4BT.ino, initialises PS4 Controller
 */
void initPS4Controller() {
   Serial.begin(115200);
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

/*
 *  Loop, run controls if in control mode, otherwise access odometry from UWB.
 */
void loop() {
  Usb.Task();
  if (PS4.connected() && Usb.Init() == 0 && driverControlMode) {
    runInputs();
  }
  else {
    uwb.computeLocation();
    pos_x = uwb.getX();
    pos_y = uwb.getY();
    
  }
  drivetrain.loop();
  intake.loop();
}

/*
 * Called when a message is received from the UWB, i.e. an update on odometry position.
 */
void serialEvent() {
  if (Serial.available() > 0) {
    uwb.readSerialEvent(Serial.read());
  }
}

/*
 * Run inputs on PS4 Controller using the USB 2.0 Host Shield. 
 * Left Stick Y Axis -> Driving forward input
 * Left Stick X Axis -> Driving turn input
 * Right Stick Y Axis -> Digger claw input
 * Trigger R2 -> Plunger Out
 * Trigger L2 -> Draw plunger
 */
void runInputs() {
  if (PS4.connected()) {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117) {
      float forwardDriveValue = (PS4.getAnalogHat(LeftHatY) / PS4_STICK_CONSTANT) - 1;
      float rightDriveValue = (PS4.getAnalogHat(LeftHatX) / PS4_STICK_CONSTANT) - 1;
      drivetrain.drive(forwardDriveValue, rightDriveValue);
    }
    else {
      drivetrain.drive(0, 0);
    }
    if (PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      float intakePower = (PS4.getAnalogHat(RightHatY) / PS4_STICK_CONSTANT) - 1;
      intake.setIntakePower(intakePower);
    }
    else {
      intake.setIntakePower(0);
    }
  }

  float plungerPower = 0;
  if (PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
    plungerPower = (PS4.getAnalogButton(R2) / PS4_TRIGGER_CONSTANT);
  } 
  else if (PS4.getAnalogButton(L2)) { // These are the only analog buttons on the PS4 controller
    plungerPower = -(PS4.getAnalogButton(L2) / PS4_TRIGGER_CONSTANT);
  } 
  intake.setPlungerPower(plungerPower);

  if (PS4.getAnalogButton(R2) != oldR2Value) { // Only write value if it's different 
    PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
    oldR2Value = PS4.getAnalogButton(R2);
  }
}
