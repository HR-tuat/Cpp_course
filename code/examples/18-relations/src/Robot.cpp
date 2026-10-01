#include <Arduino.h>

#include "Robot.hpp"

namespace {
const float STOP_DISTANCE_MM = 150.0f;
const int CRUISE_SPEED = 60;
}

Robot::Robot()
    // モータはつないでいない。Motor は速度をシリアルに表示する
    : motor(5), controller(*this), distance(400.0f) {
    // controller(*this) で自分自身を渡している。
    // Controller は参照を保存するだけなので、この時点では安全。
}

void Robot::begin() {
    motor.begin();
}

void Robot::update() {
    // 実機では距離センサから読み取る。ここでは近づいていく様子を作っている
    distance -= 50.0f;
    if (distance < 50.0f) {
        distance = 400.0f;
    }

    Serial.print("distance=");
    Serial.println(distance);

    controller.update();
}

bool Robot::isObstacleAhead() const {
    return distance < STOP_DISTANCE_MM;
}

void Robot::stop() {
    motor.stop();
}

void Robot::go() {
    motor.setSpeed(CRUISE_SPEED);
}
