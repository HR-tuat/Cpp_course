#pragma once

#include "Sensor.h"

class IMU : public Sensor
{
public:
    IMU();

    void update() override;

    float getRoll() const;
    float getPitch() const;
    float getYaw() const;

private:
    float roll;
    float pitch;
    float yaw;
};
