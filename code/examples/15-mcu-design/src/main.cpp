// 第15回：道具を組み合わせた出発点
//
//   Sensor（抽象クラス・第12回）  ← IMU が継承（第10〜11回）
//   FlightMode（enum class・第9回）
//   LED（クラス・カプセル化・第6〜8回）
//
// まずこのまま動かし、モードが切り替わるとLEDの出方が変わることを確かめる。
// Motor を足すところ、モードごとの判断を Controller に移すところは演習で行う。

#include <Arduino.h>

#include "FlightMode.hpp"
#include "IMU.hpp"
#include "LED.hpp"
#include "Sensor.hpp"

LED led(LED_BUILTIN);
IMU imu;

// センサが増えてもこの配列に足すだけで済む（第13回）
Sensor* sensors[] = {&imu};
const int SENSOR_COUNT = sizeof(sensors) / sizeof(sensors[0]);

FlightMode mode = FlightMode::MANUAL;

/**
 * @brief モード名を返す
 * @param mode 飛行モード
 * @return 表示用の文字列
 */
const char* modeName(FlightMode mode) {
    switch (mode) {
    case FlightMode::MANUAL:
        return "MANUAL";

    case FlightMode::AUTO:
        return "AUTO";

    case FlightMode::LANDING:
        return "LANDING";
    }

    return "UNKNOWN";
}

/**
 * @brief 10周ごとにモードを進める（実機ではスイッチや通信で切り替える）
 */
void advanceMode() {
    static int ticks = 0;

    ticks++;
    if (ticks < 10) {
        return;
    }

    ticks = 0;

    switch (mode) {
    case FlightMode::MANUAL:
        mode = FlightMode::AUTO;
        break;

    case FlightMode::AUTO:
        mode = FlightMode::LANDING;
        break;

    case FlightMode::LANDING:
        mode = FlightMode::MANUAL;
        break;
    }

    Serial.print("mode -> ");
    Serial.println(modeName(mode));
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    led.begin();

    Serial.print("mode -> ");
    Serial.println(modeName(mode));
}

void loop() {
    // センサは種類を問わずまとめて更新する
    for (int i = 0; i < SENSOR_COUNT; i++) {
        sensors[i]->update();
    }

    // 状態によってふるまいを変える
    switch (mode) {
    case FlightMode::MANUAL:
        led.off();
        break;

    case FlightMode::AUTO:
        led.on();
        break;

    case FlightMode::LANDING:
        led.toggle();
        break;
    }

    // IMUの値はまとめ役（この例では main.cpp）が取り出して使う
    Serial.print(modeName(mode));
    Serial.print("  roll=");
    Serial.println(imu.getRoll());

    advanceMode();
    delay(200);
}
