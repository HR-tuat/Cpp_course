// 第7回：定義（どうやって実現しているか）

#include <Arduino.h>

#include "LED.h"

LED::LED(int pin)
    : pin(pin), state(false)
{
}

void LED::begin()
{
    pinMode(pin, OUTPUT);
    off();
}

void LED::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void LED::off()
{
    state = false;
    digitalWrite(pin, LOW);
}

void LED::toggle()
{
    if (state)
    {
        off();
    }
    else
    {
        on();
    }
}
