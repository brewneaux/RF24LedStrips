#include "led.h"
#include "Arduino.h"

leddata ledData;

Led::Led() {
    ledData.R = 0;
    ledData.G = 0;
    ledData.B = 0;
}

void Led::setup(int pin, int address)
{
    Serial.println("Start of loop");
    
    ledData.pin = pin;
    ledData.address = address;
}

void Led::setAddress(int address)
{
    ledData.address = address;
}

void Led::setPin(int pin)
{
    ledData.pin = pin;
}


void Led::update(int r, int g, int b) {
    ledData.R = constrain(r, 0, 255);
    ledData.G = constrain(g, 0, 255);
    ledData.B = constrain(b, 0, 255);
}
