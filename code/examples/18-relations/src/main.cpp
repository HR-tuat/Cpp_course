// 第18回：互いを知っているクラスを、壊れない形で書く
//
//   Robot ──所有──→ Controller
//     ↑                  │
//     └──参照（Robot&）───┘
//
// Controller.hpp は Robot を #include していない（前方宣言だけ）。
// Robot.hpp を Controller.hpp から include すると循環して通らなくなる。
// 試しに Controller.hpp の前方宣言を #include "Robot.hpp" に変えてみると、
// どんなエラーが出るかを確かめられる。

#include <Arduino.h>

#include "Robot.hpp"

Robot robot;

void setup() {
    Serial.begin(115200);
    delay(1000);

    robot.begin();
}

void loop() {
    robot.update();

    Serial.println();
    delay(1000);
}
