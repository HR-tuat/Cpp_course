// 第18回：Robotが所有する部品

#pragma once

class Motor {
public:
    /**
     * @brief コンストラクタ
     * @param pin モータドライバを繋いだピン番号
     */
    explicit Motor(int pin);

    /**
     * @brief ピンを初期化する
     */
    void begin();

    /**
     * @brief 速度を設定する
     * @param speed 速度(0〜100)
     */
    void setSpeed(int speed);

    /**
     * @brief 停止する
     */
    void stop();

private:
    int pin;
    int speed;
};
