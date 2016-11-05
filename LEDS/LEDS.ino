#include <RCSwitch.h>
#include "Control.h"
#include "receiver.h"

#define INTERRUPT_NUM 2
#define DEVICE_ID 2
#define WHITE_CMD 0
#define SWIRL_CMD 1
#define PARTY_CMD 2

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define SPEED 5     // loop delay in ms

//We want to switch colors every second. SPEED is in ms
static int partyModeMaxCycles = 60000 / SPEED;

typedef enum Mode {
    WHITE,
    PARTY,
    SWIRL
} Mode;

Control *leds;
RFMessage *message;
Receiver *receiver;
Mode mode;
 
void setup() {
  leds = new Control(REDPIN, GREENPIN, BLUEPIN);
  receiver = new Receiver(INTERRUPT_NUM, DEVICE_ID);
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
    default:
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
        default:
          mode = WHITE;
          break;
      }
  }
}

int swirlHue = 0;
void swirl()
{
  swirlHue = swirlHue % 360;
  leds->sendHSV(swirlHue, 100, 100);
  swirlHue++;
}


void party()
{
  static int cycles = 0; //used to slow down the switching of colors 
  if(cycles == 0) {
    leds->sendHSV(random(0,360), 100, 100);
  }
  cycles = (cycles + 1) % partyModeMaxCycles; //increment with wraparound
}

void white()
{
  leds->sendRGB(255,255,255);
}



