#include "sender.h"

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"



int rec[2] = {0, 0};

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

Sender::Sender(RF24& radio): radio(radio)
{
    Serial.println("Sender Setup");
    
    this->radio.begin();
    this->radio.enableAckPayload();
    this->radio.setRetries(15, 15);
    this->radio.openWritingPipe(thisSlaveAddress);
}


bool Sender::sendValues(uint8_t message[4])
{
    this->radio.stopListening();
    if (this->radio.write(&message, sizeof(message)))
    {
        if (this->radio.isAckPayloadAvailable())
        {
            this->radio.read(rec, sizeof(rec));
            rec[0] = 0;
            Serial.println("Got an ack");
            Serial.println(rec[0]);
        }
        else
        {
            Serial.println("Something went bad - no ack");
            return false;
        }
    }
    else
    {
        Serial.println("COuldnt transmit?");
        return false;
    }
    return true;
}

void Sender::print_message(uint8_t message[4])
{
    Serial.print("Sending message: ");
    Serial.print(message[0], DEC);
    Serial.print(" ");
    Serial.print(message[1], DEC);
    Serial.print(" ");
    Serial.print(message[2], DEC);
    Serial.print(" ");
    Serial.print(message[3], DEC);
    Serial.print(" ");
    Serial.print(message[4], DEC);
    Serial.print(" ");
    
}
