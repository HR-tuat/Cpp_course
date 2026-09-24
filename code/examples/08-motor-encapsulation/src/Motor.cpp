#include <Arduino.h>

#include "Motor.h"

namespace
{
const int MIN_SPEED = 0;
const int MAX_SPEED = 100;
const int PWM_MAX = 255;
}

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
    if (speed < MIN_SPEED)
    {
        speed = MIN_SPEED;
    }

    if (speed > MAX_SPEED)
    {
        speed = MAX_SPEED;
    }

    this->speed = speed;
    apply();
}

int Motor::getSpeed() const
{
    return speed;
}

void Motor::stop()
{
    setSpeed(MIN_SPEED);
}

void Motor::apply()
{
    analogWrite(pin, speed * PWM_MAX / MAX_SPEED);
}
