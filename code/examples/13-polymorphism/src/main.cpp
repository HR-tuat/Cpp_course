// 第13回：種類の違うセンサを、同じ手続きで扱う
//
// loop() は中身が IMU なのか GPS なのか ToF なのかを知らない。
// センサを1種類増やすとき、loop() を1文字も変えずに済むことを確かめる。

#include <Arduino.h>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Sensor.hpp"
#include "ToF.hpp"

IMU imu;
GPS gps;
ToF tof(34);  // センサはつないでいない。ピン番号は保持するだけ

// 上位のコードは「Sensorであること」しか知らない
Sensor* sensors[] = {&imu, &gps, &tof};
const int SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.print("センサの数: ");
    Serial.println(SENSOR_COUNT);
}

void loop() {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        sensors[i]->update();
        sensors[i]->print();
    }

    Serial.println();
    delay(1000);
}
