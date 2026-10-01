// 第12回：あとから追加したセンサ
// Sensor を継承した時点で update() と print() の実装を強制される。

#pragma once

#include "Sensor.hpp"

class ToF : public Sensor {
public:
    /**
     * @brief コンストラクタ
     * @param pin 測距センサを繋いだピン番号
     */
    explicit ToF(int pin);

    /**
     * @brief 距離を読み直す
     */
    void update() override;

    /**
     * @brief 距離を表示する
     */
    void print() const override;

private:
    int pin;
    float distance;
};
