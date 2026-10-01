// 第8回：速度の範囲をクラス内部で守る

#pragma once

class Motor {
public:
    /**
     * @brief コンストラクタ
     * @param pin モータドライバを繋いだピン番号
     */
    Motor(int pin);

    /**
     * @brief ピンを初期化して停止させる
     */
    void begin();

    /**
     * @brief 速度を設定する
     * @details 範囲外の値を渡しても 0〜100 に丸めてから保持する。
     *          範囲を守る責任は、使う側ではなくこのクラスにある。
     * @param speed 速度(0〜100)
     */
    void setSpeed(int speed);

    /**
     * @brief 現在の速度を返す
     * @return 速度(0〜100)
     */
    int getSpeed() const;

    /**
     * @brief 停止する
     */
    void stop();

private:
    /**
     * @brief 保持している速度をPWMに変換して出力する
     * @note 使う側が呼ぶ必要はないので private にしてある。
     */
    void apply();

    int pin;
    int speed;
};
