// 第17回：誰が解放するのかを型で表す
//
// USE_SMART_POINTER を false にして書き込むと、
// シリアルモニタの free heap が1秒ごとに減り続ける（リーク）。
// true に戻すと値が一定のまま変わらない。delete は1行も書いていない。

#include <Arduino.h>

#include <memory>

#include "IMU.hpp"
#include "Sensor.hpp"

const bool USE_SMART_POINTER = true;

/**
 * @brief 生ポインタで確保し、解放を忘れた場合
 * @note delete を書く場所が「ここ」だと決まっていないのが問題の根っこ。
 */
void readWithRawPointer() {
    Sensor* sensor = new IMU();

    sensor->update();
    sensor->print();

    // delete sensor;  ← わざと書いていない。これがリークになる
}

/**
 * @brief unique_ptr で確保した場合
 * @note スコープを抜けるときに必ず解放される。途中で return しても同じ。
 */
void readWithUniquePtr() {
    std::unique_ptr<Sensor> sensor = std::make_unique<IMU>();

    sensor->update();
    sensor->print();
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.print("USE_SMART_POINTER = ");
    Serial.println(USE_SMART_POINTER);
    Serial.print("free heap at start: ");
    Serial.println(ESP.getFreeHeap());
}

void loop() {
    if (USE_SMART_POINTER) {
        readWithUniquePtr();
    } else {
        readWithRawPointer();
    }

    Serial.print("free heap: ");
    Serial.println(ESP.getFreeHeap());

    delay(1000);
}
