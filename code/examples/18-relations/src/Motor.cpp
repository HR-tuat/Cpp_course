#include <Arduino.h>

#include "Motor.hpp"

Motor::Motor(int pin)
    : pin(pin), speed(0) {
}

void Motor::begin() {
    pinMode(pin, OUTPUT);
    stop();
}

void Motor::setSpeed(int speed) {
    this->speed = speed;

    // 実機ではここでPWMを出す。ボード単体で確かめられるよう表示だけにしている
    Serial.print("  motor speed=");
    Serial.println(this->speed);
}

void Motor::stop() {
    setSpeed(0);
}
