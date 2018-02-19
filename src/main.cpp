#include "sender.h"
#include "receiver.h"
#include "led.h"
#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

#ifdef RECEIVER
const bool shouldReceive = 1;
#else
const bool shouldReceive = 0;
#endif

const int LED_COUNT = 4;

uint8_t recdValues[4];
uint8_t message[4];
bool newData = false;
char serialData[32];

void setup();
void loop();
void receive();
void updateLed();
void showData();
void transmit();
void getSerialData();
void parseSerialData();
void recvWithEndMarker();
void showNewData();

int radioPin1 = 9;
int radioPin2 = 10;
int ledPin = 4;
uint32_t printInterval = 100000;
int printCounter = 0;

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data


RF24 radio(9, 10);

Receiver *rcvptr;
Sender *sndptr;

Led *ledptr;

void setup()
{
    Serial.begin(115200);
    Serial.println("Nothin");
    ledptr[0].setup(ledPin, 1);
    rcvptr = &Receiver(radio);
    sndptr = &Sender(radio);
}

void loop()
{
   
    delay(500);
    if (shouldReceive)
    {
        receive();
        
        if (printCounter % printInterval == 0)
            {
                printCounter = 0;
                printCounter++;
                showData();
            }
    }
    else
    {
        if (newData) {
            parseSerialData();
            transmit();
            newData = false;
        }
        // getSerialData();
        getSerialData();

    }
}

void receive()
{
    Serial.println("Receiving...");

    rcvptr->getValues(recdValues);
}

void transmit()
{
    Serial.println("Transmitting...");
    
    sndptr->sendValues(message);
}

void showData()
{

    Serial.print("Data received - Address: ");
    Serial.print(recdValues[0], DEC);
    Serial.print(", R: ");
    Serial.print(recdValues[1], DEC);
    Serial.print(", G: ");
    Serial.print(recdValues[2], DEC);
    Serial.print(", B: ");
    Serial.print(recdValues[3], DEC);
    Serial.print("\n");
    
}

void getSerialData()
{
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        } else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void parseSerialData()
{
    char parsingString[32];
    int led_number, r, g, b;
    strcpy(parsingString, receivedChars);
    
    led_number = atoi(strtok(parsingString, ":"));
    r = atoi(strtok(NULL, ":"));
    g = atoi(strtok(NULL, ":"));
    b = atoi(strtok(NULL, ":"));
    Serial.println("Got this data: ");
    Serial.println(receivedChars);

    char buff[100];
    sprintf(buff, "parsed out addr: %d R: %d G:%d B:%d", led_number, r, g, b);
    Serial.println(buff);
    // for(int i = 0; i < LED_COUNT; i++)
    // {
    //     if (leds[i].ledData.address == led_number) {
    //         leds[i].update(r, g, b);
    //     }
    // }
}
