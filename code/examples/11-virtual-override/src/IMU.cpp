#include <Arduino.h>

#include "IMU.h"

IMU::IMU()
    : roll(0.0f), pitch(0.0f), yaw(0.0f)
{
}

void IMU::update()
{
    // 実機では姿勢センサから読み取る
    roll += 0.1f;
    pitch += 0.2f;
    yaw += 0.3f;
}

void IMU::print() const
{
    Serial.print("IMU roll=");
    Serial.println(roll);
}
