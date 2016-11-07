#include "receiver.h"

Receiver::Receiver(int interruptNumber, uint8_t deviceID) {
    rf.enableReceive(digitalPinToInterrupt(interruptNumber));

    this->deviceID = deviceID;
    this->prevMessage = NULL;
}

bool Receiver::check(RFMessage** output) {
    //If nothing available, return false
    if(!rf.available()){
        return false;
    }

    uint32_t raw = rf.getReceivedValue();
    rf.resetAvailable();

    //Message available, convert and save in our currentMessage
    RFMessage *newMessage = intToRFMessage(raw);

    //If its not for us, ignore
    if(newMessage->destinationID != deviceID) {
        return false;
    }

    //If we just got this message or if this is the first one, ignore
    if(prevMessage != NULL && prevMessage->messageID == newMessage->messageID) {
      Serial.println("ignoring");
        //return false;
    }

    //tell the output about the currentMessage
    *output = newMessage;
    delete prevMessage; //delete the old previous message
    prevMessage = newMessage; //Save the new previous message
    
    return true;
}

RFMessage *Receiver::intToRFMessage(uint32_t input) {
    return new RFMessage {
        input & 0xFF000000 >> 24,
        input & 0x00FF0000 >> 16,
        input & 0x0000FF00 >> 8,
        input & 0x000000FF
    };
}

