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
    void sendHSV(double hue, double saturation, double value);
    void sendHSL(double hue, double saturation, double l);

  private:
    int redPin, greenPin, bluePin;
    RGBConverter converter;
};

#endif
