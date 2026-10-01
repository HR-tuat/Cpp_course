#pragma once

#include "Sensor.hpp"

class GPS : public Sensor {
public:
    GPS();

    /**
     * @brief 位置を読み直す
     */
    void update() override;

    /**
     * @brief 位置を表示する
     */
    void print() const override;

private:
    float latitude;
    float longitude;
};
