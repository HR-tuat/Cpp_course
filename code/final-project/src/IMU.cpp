#include "IMU.h"

IMU::IMU()
    : roll(0.0f), pitch(0.0f), yaw(0.0f)
{
}

void IMU::update()
{
    // TODO: 実機のセンサから姿勢を読み取る
}

float IMU::getRoll() const
{
    return roll;
}

float IMU::getPitch() const
{
    return pitch;
}

float IMU::getYaw() const
{
    return yaw;
}
