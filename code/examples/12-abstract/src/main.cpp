// 第12回：抽象クラスは「約束ごと」。オブジェクトとしては作れない。
//
// 下の Sensor sensor; のコメントを外すとビルドが失敗する。
// エラーメッセージを一度自分の目で見てから、また戻すとよい。

#include <Arduino.h>

#include "Barometer.hpp"
#include "IMU.hpp"
#include "Sensor.hpp"

IMU imu;
Barometer baro;

// Sensor sensor;
//   → error: cannot declare variable 'sensor' to be of abstract type 'Sensor'
//     純粋仮想関数が残っているので、実体は作れない

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Sensorを継承した2つは、どちらも update() と print() を持っている");
}

void loop() {
    // どちらも「Sensorの約束ごと」を満たしているので、同じ順番で呼べる
    imu.update();
    imu.print();

    baro.update();
    baro.print();

    Serial.println();
    delay(1000);
}
