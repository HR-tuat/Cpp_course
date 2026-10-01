// 第16回：個数の管理を std::vector に任せる
//
// 第13回では要素数を sizeof の割り算で自分で求めていた。
// ここでは size() が答えるので、SENSOR_COUNT のような変数が要らない。
//
// さらに「起動時に見つかったセンサだけ登録する」形にしてある。
// 個数がコンパイル時に決まらないので、std::array では書けない。

#include <Arduino.h>

#include <vector>

#include "GPS.hpp"
#include "IMU.hpp"
#include "Sensor.hpp"
#include "ToF.hpp"

IMU imu;
GPS gps;
ToF tof(34);  // センサはつないでいない。ピン番号は保持するだけ

std::vector<Sensor*> sensors;

/**
 * @brief そのセンサが繋がっているかを調べる
 * @details 実機では I2C の応答やIDレジスタを読んで判定する。
 *          ここでは GPS だけ繋がっていないことにしている。
 * @param sensor 調べるセンサ
 * @return 繋がっていれば true
 */
bool isConnected(Sensor* sensor) {
    return sensor != &gps;
}

/**
 * @brief 繋がっているセンサだけを登録する
 * @param sensor 登録を試すセンサ
 * @param name 表示用の名前
 */
void registerIfConnected(Sensor* sensor, const char* name) {
    if (isConnected(sensor)) {
        sensors.push_back(sensor);
        Serial.print("registered: ");
        Serial.println(name);
    } else {
        Serial.print("not found : ");
        Serial.println(name);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // 確保をここで1回だけ済ませる。loop() では増やさない
    sensors.reserve(8);

    registerIfConnected(&imu, "IMU");
    registerIfConnected(&gps, "GPS");
    registerIfConnected(&tof, "ToF");

    Serial.print("sensors.size() = ");
    Serial.println(sensors.size());
}

void loop() {
    // 添字も境界条件も書かない
    for (Sensor* sensor : sensors) {
        sensor->update();
        sensor->print();
    }

    Serial.println();
    delay(1000);
}
