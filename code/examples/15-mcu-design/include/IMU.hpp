// 第15回：継承とoverride（第10〜11回）

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
     * @brief 現在のロール角を返す
     * @return ロール角(度)
     */
    float getRoll() const;

    /**
     * @brief 現在のピッチ角を返す
     * @return ピッチ角(度)
     */
    float getPitch() const;

private:
    float roll;
    float pitch;
};
