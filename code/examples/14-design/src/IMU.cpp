#include <Arduino.h>

#include "IMU.hpp"

IMU::IMU()
    : roll(12.0f) {
}

void IMU::update() {
    // 実機では姿勢センサから読み取る。
    // ここでは「傾きがだんだん戻っていく」様子を作っている
    roll = roll * 0.8f;
}

float IMU::getRoll() const {
    return roll;
}
