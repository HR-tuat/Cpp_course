// 第14回：責務は「モータに出すこと」だけ
// 何度傾いているかも、PIDのゲインも知らない。

#pragma once

class MotorManager {
public:
    /**
     * @brief コンストラクタ
     * @param leftPin 左モータのピン番号
     * @param rightPin 右モータのピン番号
     */
    MotorManager(int leftPin, int rightPin);

    /**
     * @brief ピンを初期化する
     */
    void begin();

    /**
     * @brief 左右のモータに差をつけて出力する
     * @param correction 操作量。正なら右が速くなる
     */
    void apply(float correction);

private:
    /**
     * @brief 0〜100 に丸める
     * @param value 丸める値
     * @return 丸めた値
     */
    static int clamp(float value);

    int leftPin;
    int rightPin;
};
