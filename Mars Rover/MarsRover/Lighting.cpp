/*
 * Lighting class written by Peter Jung 2023, for DESN1000 project.
 * Used for testing pin outputs with an LED light.
 */

#include <Arduino.h>
#include "Lighting.h"

/*
 * Base constructor
 */
Lighting::Lighting(int pin_testLight) {
    _pin_testLight = pin_testLight;
}

/*
 * Called every loop cycle, update LED brightness
 */
void Lighting::loop() {
    analogWrite(_pin_testLight, _brightness);
}

/*
 * Set the brightness of the LED light
 * @param brightness how bright the light should be from 0-255
 */
void Lighting::setBrightness(int brightness) {
   _brightness = brightness;
}