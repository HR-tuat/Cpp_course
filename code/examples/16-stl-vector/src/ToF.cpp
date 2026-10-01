#include <Arduino.h>

#include "ToF.hpp"

ToF::ToF(int pin)
    : pin(pin), distance(400.0f) {
}

void ToF::update() {
    // 実機では測距センサから読み取る
    distance -= 25.0f;
    if (distance < 50.0f) {
        distance = 400.0f;
    }
}

void ToF::print() const {
    Serial.print("ToF  distance=");
    Serial.print(distance);
    Serial.println(" mm");
}
