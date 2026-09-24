#include "Controller.h"

Controller::Controller(Motor& motor, DistanceSensor& distance)
    : motor(motor), distance(distance), state(RobotState::STOP)
{
}

void Controller::update()
{
    // TODO: 距離センサの値から状態を決め、モータに指示を出す
}

RobotState Controller::getState() const
{
    return state;
}
