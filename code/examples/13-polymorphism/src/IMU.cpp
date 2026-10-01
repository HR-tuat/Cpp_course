#include <Arduino.h>

#include "IMU.hpp"

IMU::IMU()
    : roll(0.0f), pitch(0.0f) {
}

void IMU::update() {
    // 実機では姿勢センサから読み取る。ここでは値が動く様子だけを作っている
    roll += 0.5f;
    pitch += 0.2f;
}

void IMU::print() const {
    Serial.print("IMU  roll=");
    Serial.print(roll);
    Serial.print(" pitch=");
    Serial.println(pitch);
}
