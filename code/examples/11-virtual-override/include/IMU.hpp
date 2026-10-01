#pragma once

#include "Sensor.hpp"

class IMU : public Sensor {
public:
    IMU();

    /**
     * @brief 姿勢を読み直す
     */
    void update() override;

    /**
     * @brief 姿勢を表示する
     */
    void print() const override;

private:
    float roll;
    float pitch;
    float yaw;
};
