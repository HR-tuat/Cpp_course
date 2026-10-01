#include <Arduino.h>

#include "Motor.hpp"

namespace {
const int MIN_SPEED = 0;
const int MAX_SPEED = 100;
}

Motor::Motor(int pin)
    : Device(pin), speed(0) {
}

void Motor::setSpeed(int speed) {
    if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }

    if (speed > MAX_SPEED) {
        speed = MAX_SPEED;
    }

    this->speed = speed;

    // 実機ではここでPWMを出す。ボード単体で確かめられるよう表示だけにしている
    Serial.print("Motor pin=");
    Serial.print(pin);
    Serial.print(" speed=");
    Serial.println(this->speed);
}

int Motor::getSpeed() const {
    return speed;
}
