// 第12回：あとから追加したセンサ
// Sensor を継承した時点で update() と print() の実装を強制される。
// どちらかを書き忘れると、実体を作る行でコンパイルエラーになる。

#pragma once

#include "Sensor.hpp"

class Barometer : public Sensor {
public:
    Barometer();

    /**
     * @brief 気圧を読み直す
     */
    void update() override;

    /**
     * @brief 気圧を表示する
     */
    void print() const override;

private:
    float pressure;
};
