#include <Arduino.h>

#include "FlightController.hpp"

FlightController::FlightController()
    // モータはつないでいない。MotorManager は出力値をシリアルに表示する
    : pid(1.5f, 0.1f, 0.05f, 0.5f), motors(24, 10), targetRoll(0.0f) {
}

void FlightController::begin() {
    motors.begin();
    pid.reset();
}

void FlightController::update() {
    // 1. 読む（IMUの責務）
    imu.update();
    float roll = imu.getRoll();

    // 2. 計算する（PIDControllerの責務）
    float correction = pid.compute(targetRoll - roll);

    Serial.print("roll=");
    Serial.print(roll);
    Serial.print(" correction=");
    Serial.println(correction);

    // 3. 出力する（MotorManagerの責務）
    motors.apply(correction);
}
