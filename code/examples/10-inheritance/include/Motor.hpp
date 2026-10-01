// 第10回：Motor is a Device

#pragma once

#include "Device.hpp"

class Motor : public Device {
public:
    /**
     * @brief コンストラクタ
     * @param pin モータドライバを繋いだピン番号
     */
    explicit Motor(int pin);

    /**
     * @brief 速度を設定する
     * @param speed 速度(0〜100)。範囲外は丸める
     */
    void setSpeed(int speed);

    /**
     * @brief 現在の速度を返す
     * @return 速度(0〜100)
     */
    int getSpeed() const;

private:
    int speed;
};
