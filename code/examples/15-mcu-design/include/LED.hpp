// 第15回：クラスとカプセル化（第6〜8回）

#pragma once

class LED {
public:
    /**
     * @brief コンストラクタ
     * @param pin LEDを繋いだピン番号
     */
    explicit LED(int pin);

    /**
     * @brief ピンを初期化する
     */
    void begin();

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
    int pin;
    bool state;
};
