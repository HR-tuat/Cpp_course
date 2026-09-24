#pragma once

#include "DistanceSensor.h"
#include "Motor.h"

enum class RobotState {
    STOP,
    MOVE,
    ERROR
};

class Controller {
public:
    Controller(Motor& motor, DistanceSensor& distance);

    void update();

    RobotState getState() const;

private:
    Motor& motor;
    DistanceSensor& distance;
    RobotState state;
};
