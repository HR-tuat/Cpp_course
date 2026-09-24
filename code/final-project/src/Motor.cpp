#include <Arduino.h>

#include "Motor.h"

Motor::Motor(int pin)
    : pin(pin), speed(0)
{
}

void Motor::begin()
{
    pinMode(pin, OUTPUT);
    stop();
}

void Motor::setSpeed(int speed)
{
    // TODO: 0〜100 に制限してから保持し、出力する
}

void Motor::stop()
{
    setSpeed(0);
}
