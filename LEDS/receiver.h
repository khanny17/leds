#ifndef RECEIVER_H
#define RECEIVER_H

#include "RCSwitch.h"

//TODO define command ids somewhere??

typedef struct RFMessage {
    uint8_t messageID;
    uint8_t senderID;
    uint8_t destinationID;
    uint8_t data;
} RFMessage;

class Receiver
{
  public:
    Receiver(int interruptNumber, uint8_t deviceID);
    //Checks if a message is available. if so, it returns true and
    //populates "output" with the data
    bool check(RFMessage** output);

  private:
    uint8_t deviceID;
    RCSwitch rf;
    RFMessage *prevMessage;

    //convert 32 bit int to RFMessage struct
    RFMessage *intToRFMessage(uint32_t input);
};

#endif
