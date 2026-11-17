#ifndef PIDController_h
#define PIDController_h
#include "PIDController.h"
#include "Arduino.h" 

class PIDController {
public:
  PIDController(float kP, float kI, float kD);
  float getOutput(float error);
private:
  float _kP;
  float _kI;
  float _kD;
  
  float lastError;
  long lastTime;

  float errorAccumulation;
  float errorDerivative;
};

#endif