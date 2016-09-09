#ifndef CONTROL_H
#define CONTROL_H

#include "RGBConverter.h"
#include "Arduino.h"

class Control
{
  public:
    Control(int redPin, int greenPin, int bluePin);
    
    void sendWhite();
    void sendRGB(unsigned char r, unsigned char g, unsigned char b);
    void sendRGB(RGB *val);
    void sendHSV(int hue, int saturation, int value);

  private:
    int redPin, greenPin, bluePin;
    RGBConverter converter;
};

#endif
