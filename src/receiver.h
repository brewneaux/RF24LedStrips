/*
  receiver.h - Receiver messages via Radio.
*/

#ifndef receiver_h
#define receiver_h

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

class Receiver
{
  public:
    Receiver(RF24& radio);
    void getValues(uint8_t buffer[4]);
  private:
    void updateReplyData();
    void getRadioData(); 
    RF24 radio;   
};

#endif
