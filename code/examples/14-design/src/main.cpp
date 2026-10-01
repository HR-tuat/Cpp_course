// 第14回：1クラス1責務
//
//   FlightController   まとめ役（順番に呼ぶだけ）
//    ├── IMU            姿勢を読む
//    ├── PIDController  操作量を計算する
//    └── MotorManager   モータに出す
//
// main.cpp にも FlightController にも、計算式は1つも書かれていない。
// 「センサを変える」「ゲインを変える」「出力先を変える」のどれをやっても
// 直すファイルが1つで済むことを確かめる。

#include <Arduino.h>

#include "FlightController.hpp"

FlightController controller;

void setup() {
    Serial.begin(115200);
    delay(1000);

    controller.begin();
}

void loop() {
    controller.update();
    delay(500);
}
