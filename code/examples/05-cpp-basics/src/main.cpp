// 第5回：C++基礎（const / 名前空間 / オーバーロード / const参照）
// マジックナンバーを const にまとめ、関連する関数を名前空間に入れる。

#include <Arduino.h>

// マジックナンバーを名前付きの定数にする
const int LED_PIN = LED_BUILTIN;
const float TEMP_THRESHOLD = 30.0f;

/**
 * @brief 1回の測定結果
 * @note データをまとめるだけの入れ物。第6回でこれがクラスになる。
 */
struct Reading {
    float temperature;
    float humidity;
};

// センサ関連の関数をひとまとめにする
namespace Sensor {

/**
 * @brief センサを初期化する
 */
void begin() {
    Serial.println("Sensor::begin()");
}

/**
 * @brief 測定値を読む（実機ではセンサから取得する）
 * @return 測定結果
 */
Reading read() {
    static float t = 28.0f;

    t += 1.5f;
    if (t > 34.0f) {
        t = 28.0f;
    }

    Reading reading;
    reading.temperature = t;
    reading.humidity = 55.0f;

    return reading;
}

}  // namespace Sensor

// 同じ名前でも名前空間が違えば衝突しない
namespace Motor {

/**
 * @brief モータを始動する
 */
void begin() {
    Serial.println("Motor::begin()");
}

}  // namespace Motor

/**
 * @brief 整数どうしの加算
 * @param a 左辺
 * @param b 右辺
 * @return 和
 */
int add(int a, int b) {
    return a + b;
}

/**
 * @brief 小数どうしの加算
 * @param a 左辺
 * @param b 右辺
 * @return 和
 */
float add(float a, float b) {
    return a + b;
}

/**
 * @brief 測定結果を表示する
 * @details const参照で受けるのでコピーが起きず、中身を書き換える心配もない。
 * @param reading 測定結果
 */
void print(const Reading& reading) {
    Serial.print("temp=");
    Serial.print(reading.temperature);
    Serial.print(" humi=");
    Serial.println(reading.humidity);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    delay(1000);

    Serial.println("--- 名前空間 ---");
    Sensor::begin();
    Motor::begin();

    Serial.println("--- オーバーロード ---");
    Serial.print("add(1, 2)       = ");
    Serial.println(add(1, 2));          // int 版が呼ばれる → 3
    Serial.print("add(1.5f, 2.5f) = ");
    Serial.println(add(1.5f, 2.5f));    // float 版が呼ばれる → 4.00

    // TEMP_THRESHOLD = 25.0f;  // const なのでコンパイルエラーになる
}

void loop() {
    Reading reading = Sensor::read();
    print(reading);

    if (reading.temperature >= TEMP_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }

    delay(1000);
}
