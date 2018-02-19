#include "receiver.h"

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

uint8_t dataReceived[4];
int ackData[2] = {109, -4000}; // the two values to be sent to the master

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

Receiver::Receiver(RF24& radio) : radio(radio)
{
    this->radio.begin();
    this->radio.setPALevel(RF24_PA_MIN);
    this->radio.setChannel(108);

    this->radio.setDataRate(RF24_250KBPS);
    this->radio.openReadingPipe(1, thisSlaveAddress);

    this->radio.enableAckPayload();
    this->radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data

    this->radio.startListening();
}

void Receiver::getValues(uint8_t *buffer)
{
    buffer = dataReceived;
}

void Receiver::getRadioData()
{
    if (this->radio.available() > 0)
    {
        while (this->radio.available())
        {
            this->radio.read(&dataReceived, sizeof(dataReceived));
            updateReplyData();
        }
    }
}

void Receiver::updateReplyData()
{
    Serial.println("Updating reply data");
    ackData[0] -= 1;
    ackData[1] -= 1;
    if (ackData[0] < 100)
    {
        ackData[0] = 109;
    }
    if (ackData[1] < -4009)
    {
        ackData[1] = -4000;
    }
    this->radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}