// 第10回：LED is a Device

#pragma once

#include "Device.hpp"

class LED : public Device {
public:
    /**
     * @brief コンストラクタ
     * @param pin LEDを繋いだピン番号
     */
    explicit LED(int pin);

    /**
     * @brief 点灯する
     */
    void on();

    /**
     * @brief 消灯する
     */
    void off();

    /**
     * @brief 点灯と消灯を切り替える
     */
    void toggle();

private:
    bool state;
};
