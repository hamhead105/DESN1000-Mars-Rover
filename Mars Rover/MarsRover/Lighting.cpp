#include <Arduino.h>
#include "Lighting.h"

Lighting::Lighting(int pin_testLight) {
    _pin_testLight = pin_testLight;
}

void Lighting::loop() {
    analogWrite(_pin_testLight, _brightness);
}

void Lighting::setBrightness(int brightness) {
   _brightness = brightness;
}