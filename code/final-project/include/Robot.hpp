#pragma once

#include "Controller.hpp"
#include "DistanceSensor.hpp"
#include "IMU.hpp"
#include "Motor.hpp"

class Robot {
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
