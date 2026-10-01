#include <Arduino.h>

#include "Controller.hpp"

#include "Robot.hpp"  // 中身を使うのはここから。.cppは誰からもincludeされないので循環しない

Controller::Controller(Robot& robot)
    : robot(robot) {
    // ここで robot.isObstacleAhead() を呼んではいけない。
    // Robot のメンバはまだ初期化されていない。
}

void Controller::update() {
    if (robot.isObstacleAhead()) {
        Serial.println("Controller: obstacle -> stop");
        robot.stop();
    } else {
        Serial.println("Controller: clear -> go");
        robot.go();
    }
}
