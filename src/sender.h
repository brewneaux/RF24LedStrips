/*
  sender.h - Send messages via Radio.
*/

#ifndef sender_h
#define sender_h

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

class Sender
{
  public:
    Sender(RF24& radio);
    bool sendValues(uint8_t message[4]);
  private:
    RF24 radio;
    void print_message(uint8_t message[4]);
};

#endif
