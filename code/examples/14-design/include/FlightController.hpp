// 第14回：責務は「まとめ役」だけ
// 自分では読まない・計算しない・出力しない。順番に呼ぶだけ。

#pragma once

#include "IMU.hpp"
#include "MotorManager.hpp"
#include "PIDController.hpp"

class FlightController {
public:
    FlightController();

    /**
     * @brief 部品をまとめて初期化する
     */
    void begin();

    /**
     * @brief 1周期分の処理を行う
     * @details 読む → 計算する → 出力する、の3手順を並べているだけ。
     */
    void update();

private:
    IMU imu;
    PIDController pid;
    MotorManager motors;

    float targetRoll;
};
