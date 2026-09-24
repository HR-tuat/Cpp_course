#pragma once

#include "Controller.h"
#include "DistanceSensor.h"
#include "IMU.h"
#include "Motor.h"

class Robot
{
public:
    Robot();

    void initialize();
    void update();

private:
    Motor motor;
    DistanceSensor distance;
    IMU imu;
    Controller controller;

    // Sensor* でまとめて更新する
    Sensor* sensors[2];
};
