/*
  led.h - Interface for Seeed Grove LED Drive.
*/

#ifndef led_h
#define led_h

#include "Arduino.h"
typedef struct
{
    int pin;
    int address;
    int R;
    int G;
    int B;
} leddata;

class Led
{
  public:
    Led();
    void setPin(int pin);
    void setAddress(int address);
    void setup(int pin, int address);
    void update(int R, int G, int B);
    leddata ledData;
};

#endif

