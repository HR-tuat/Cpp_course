// 第6回：LEDクラス（1ファイル版）
// まずは main.cpp の中だけでクラスを書く。分割は第7回で行う。

#include <Arduino.h>

class LED {
public:
    /**
     * @brief コンストラクタ
     * @param pin LEDを繋いだピン番号
     */
    LED(int pin)
        : pin(pin), state(false) {
    }

    /**
     * @brief ピンを初期化して消灯状態にする
     */
    void begin() {
        pinMode(pin, OUTPUT);
        off();
    }

    /**
     * @brief 点灯する
     */
    void on() {
        state = true;
        digitalWrite(pin, HIGH);
    }

    /**
     * @brief 消灯する
     */
    void off() {
        state = false;
        digitalWrite(pin, LOW);
    }

    /**
     * @brief 点灯と消灯を切り替える
     */
    void toggle() {
        if (state) {
            off();
        } else {
            on();
        }
    }

private:
    int pin;
    bool state;
};

// 同じクラスから複数のオブジェクトを作れる。違うのはピン番号だけ
LED led1(LED_BUILTIN);  // ボード上のRGB LED。配線なしで見える
LED led2(23);           // 何もつないでいないピン。外付けLEDを挿せば光る

void setup() {
    led1.begin();
    led2.begin();
}

void loop() {
    led1.toggle();
    delay(500);

    led2.toggle();
    delay(500);
}
