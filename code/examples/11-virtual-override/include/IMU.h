#pragma once

#include "Sensor.h"

class IMU : public Sensor
{
public:
    IMU();

    void update() override;
    void print() const override;

private:
    float roll;
    float pitch;
    float yaw;
};
