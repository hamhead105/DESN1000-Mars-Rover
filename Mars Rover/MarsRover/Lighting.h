#ifndef Lighting_h
#define Lighting_h
#include "Arduino.h" 

class Lighting {
public:
    Lighting(int pin_testLight);
    void setBrightness(int brightness);
    void loop();
private:
    int _pin_testLight;
    int _brightness;
};

#endif