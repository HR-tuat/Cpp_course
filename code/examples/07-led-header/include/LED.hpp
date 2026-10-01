// 第7回：宣言（何ができるか）

#pragma once

class LED {
public:
    /**
     * @brief コンストラクタ
     * @param pin LEDを繋いだピン番号
     */
    LED(int pin);

    /**
     * @brief ピンを初期化して消灯状態にする
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
