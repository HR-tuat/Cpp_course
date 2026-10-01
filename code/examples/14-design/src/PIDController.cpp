#include "PIDController.hpp"

PIDController::PIDController(float kp, float ki, float kd, float intervalSec)
    : kp(kp), ki(ki), kd(kd), intervalSec(intervalSec), integral(0.0f), previousError(0.0f) {
}

float PIDController::compute(float error) {
    integral += error * intervalSec;

    float derivative = (error - previousError) / intervalSec;
    previousError = error;

    return kp * error + ki * integral + kd * derivative;
}

void PIDController::reset() {
    integral = 0.0f;
    previousError = 0.0f;
}
