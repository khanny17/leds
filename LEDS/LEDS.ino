#include <RCSwitch.h>
#include "Control.h"
#include "receiver.h"

#define RECEIVER_PIN 2
#define DEVICE_ID 2
#define WHITE_CMD 0
#define SWIRL_CMD 1
#define PARTY_CMD 2

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define SPEED 50     // loop delay in ms

//We want to switch colors every second. SPEED is in ms
static int partyModeMaxCycles = 10;

typedef enum Mode {
    WHITE,
    PARTY,
    SWIRL
} Mode;

Control *leds;
RFMessage *message;
Receiver *receiver;
Mode mode;

void swirl();
 
void setup() {
  Serial.begin(9600);
  leds = new Control(REDPIN, GREENPIN, BLUEPIN);
  receiver = new Receiver(RECEIVER_PIN, DEVICE_ID);
  message = NULL;
  mode = SWIRL;
}
 
void loop() {
  checkCommands();

  switch(mode) {
    case SWIRL:
      swirl();
      break;
    case PARTY:
      party();
      break;
    case WHITE:
      white();
      break;
  }
  
  delay(SPEED);
}

void checkCommands() {
  if(receiver->check(&message)) {
      //We have a new message!
      switch(message->data) {
        case PARTY_CMD:
          mode = PARTY;
          break;
        case SWIRL_CMD:
          mode = SWIRL;
          break;
        case WHITE_CMD:
          mode = WHITE;
          break;
      }
  }
}

int swirlHue = 0;
void swirl()
{
  swirlHue = swirlHue % 360;
  leds->sendHSV((double)swirlHue/360, 1, 1);
  swirlHue++;
}


void party()
{
  static int cycles = 0; //used to slow down the switching of colors 
  if(cycles == 0) {
    leds->sendHSV(((double)random(0,360))/360, 1, 1);
  }
  cycles = (cycles + 1) % partyModeMaxCycles; //increment with wraparound
}

void white()
{
  leds->sendRGB(255,255,255);
}



