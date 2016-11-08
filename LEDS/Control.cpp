#include "Control.h"

Control::Control(int redPin, int greenPin, int bluePin)
{  
  this->redPin = redPin;
  this->greenPin = greenPin;
  this->bluePin = bluePin;

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void Control::sendWhite()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

void Control::sendRGB(unsigned char r, unsigned char g, unsigned char b)
{
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void Control::sendHSV(double hue, double saturation, double value)
{
    byte rgb[3];
    converter.hsvToRgb(hue, saturation, value, rgb);
    sendRGB(rgb[0], rgb[1], rgb[2]);
}

void Control::sendHSL(double hue, double saturation, double l)
{
    byte rgb[3];
    converter.hslToRgb(hue, saturation, l, rgb);
    sendRGB(rgb[0], rgb[1], rgb[2]);
}

