#include <Arduino.h>

#include "MotorManager.hpp"

namespace {
const int BASE_SPEED = 50;
}

MotorManager::MotorManager(int leftPin, int rightPin)
    : leftPin(leftPin), rightPin(rightPin) {
}

void MotorManager::begin() {
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
}

void MotorManager::apply(float correction) {
    int left = clamp(BASE_SPEED - correction);
    int right = clamp(BASE_SPEED + correction);

    // 実機ではここでPWMを出す。ボード単体で確かめられるよう表示だけにしている
    Serial.print("  motor L=");
    Serial.print(left);
    Serial.print(" R=");
    Serial.println(right);
}

int MotorManager::clamp(float value) {
    if (value < 0.0f) {
        return 0;
    }

    if (value > 100.0f) {
        return 100;
    }

    return (int)value;
}
