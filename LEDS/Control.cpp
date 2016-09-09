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

void Control::sendRGB(RGB *values)
{
  analogWrite(redPin, values->r);
  analogWrite(greenPin, values->g);
  analogWrite(bluePin, values->b);
}

void Control::sendHSV(int hue, int saturation, int value)
{
    sendRGB(converter.hsvToRgb((double)hue, (double)saturation, (double)value));
}

