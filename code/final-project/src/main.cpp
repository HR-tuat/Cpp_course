// 講座終了時の目標コード。
// main.cpp にはロジックを書かず、Robot に任せる。

#include <Arduino.h>

#include "Robot.hpp"

Robot robot;

void setup() {
    robot.initialize();
}

void loop() {
    robot.update();
}
