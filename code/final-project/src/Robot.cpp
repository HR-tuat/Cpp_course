#include <Arduino.h>

#include "Robot.h"

namespace
{
const int MOTOR_PIN = 5;
const int DISTANCE_PIN = 34;
}

Robot::Robot()
    : motor(MOTOR_PIN),
      distance(DISTANCE_PIN),
      imu(),
      controller(motor, distance),
      sensors{&distance, &imu}
{
}

void Robot::initialize()
{
    Serial.begin(115200);
    motor.begin();
}

void Robot::update()
{
    // TODO: すべてのセンサを更新してから controller.update() を呼ぶ
}
