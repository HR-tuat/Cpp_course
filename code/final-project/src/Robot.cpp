#include <Arduino.h>

#include "Robot.hpp"

namespace {
// ESP32-C5-DevKitC-1 のヘッダに出ていて、他の機能と衝突しないピンを選ぶ。
// GPIO6 は ADC1_CH5。GPIO24 は特別な機能の割り当てがない。
const int MOTOR_PIN = 24;
const int DISTANCE_PIN = 6;
}

Robot::Robot()
    : motor(MOTOR_PIN),
      distance(DISTANCE_PIN),
      imu(),
      controller(motor, distance),
      sensors{&distance, &imu} {
}

void Robot::initialize() {
    Serial.begin(115200);
    motor.begin();
}

void Robot::update() {
    // TODO: すべてのセンサを更新してから controller.update() を呼ぶ
}
