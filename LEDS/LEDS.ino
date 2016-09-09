#include "Control.h"

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define FADESPEED 5     // make this higher to slow down

Control *leds;
 
void setup() {
  leds = new Control(REDPIN, GREENPIN, BLUEPIN);
}
 
 
void loop() {
  swirl();
  delay(FADESPEED);
}

int swirlHue = 0;
void swirl()
{
  swirlHue = swirlHue % 360;
  leds->sendHSV(swirlHue, 100, 100);
  swirlHue++;
}

