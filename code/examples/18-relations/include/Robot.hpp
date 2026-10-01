// 第18回：Robotが Controller と Motor を所有する
//
// Controller を実体のメンバとして持つので、大きさを知る必要があり
// ここでは #include を外せない。向きが一方向なので循環しない。

#pragma once

#include "Controller.hpp"
#include "Motor.hpp"

class Robot {
public:
    Robot();

    /**
     * @brief 部品をまとめて初期化する
     */
    void begin();

    /**
     * @brief 1周期分の処理を行う
     */
    void update();

    /**
     * @brief 前方に障害物があるか
     * @return あれば true
     */
    bool isObstacleAhead() const;

    /**
     * @brief 走行を止める
     */
    void stop();

    /**
     * @brief 走行を始める
     */
    void go();

private:
    Motor motor;
    Controller controller;  // Robotが所有する

    float distance;
};
