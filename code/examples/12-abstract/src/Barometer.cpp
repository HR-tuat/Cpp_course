#include <Arduino.h>

#include "Barometer.hpp"

Barometer::Barometer()
    : pressure(1013.0f) {
}

void Barometer::update() {
    // 実機では気圧センサから読み取る
    pressure -= 0.5f;
    if (pressure < 1000.0f) {
        pressure = 1013.0f;
    }
}

void Barometer::print() const {
    Serial.print("Baro pressure=");
    Serial.print(pressure);
    Serial.println(" hPa");
}
