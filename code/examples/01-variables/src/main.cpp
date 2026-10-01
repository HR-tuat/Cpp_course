// 第1回：変数・型・演算子
// 値をシリアルモニタに出して、型と演算子のふるまいを目で確かめる。

#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(1000);  // シリアルモニタが繋がるのを待つ

    int count = 7;
    int divisor = 2;
    float temperature = 23.5f;
    char grade = 'A';
    bool isHot = false;

    Serial.println("--- 変数と型 ---");
    Serial.print("count       = ");
    Serial.println(count);
    Serial.print("temperature = ");
    Serial.println(temperature);
    Serial.print("grade       = ");
    Serial.println(grade);

    Serial.println("--- 割り算 ---");
    Serial.print("7 / 2    = ");
    Serial.println(count / divisor);  // 3（小数は切り捨てられる）
    Serial.print("7 % 2    = ");
    Serial.println(count % divisor);  // 1
    Serial.print("7 / 2.0f = ");
    Serial.println(count / 2.0f);     // 3.50

    Serial.println("--- 比較と論理 ---");
    isHot = temperature >= 30.0f;
    Serial.print("temperature >= 30.0f = ");
    Serial.println(isHot);  // 0（false は 0 と表示される）

    Serial.print("20 < t && t < 30     = ");
    Serial.println(20.0f < temperature && temperature < 30.0f);  // 1

    Serial.println("--- 型の大きさ（バイト）---");
    Serial.print("int     : ");
    Serial.println(sizeof(int));
    Serial.print("float   : ");
    Serial.println(sizeof(float));
    Serial.print("double  : ");
    Serial.println(sizeof(double));
    Serial.print("char    : ");
    Serial.println(sizeof(char));
    Serial.print("bool    : ");
    Serial.println(sizeof(bool));
    Serial.print("uint8_t : ");
    Serial.println(sizeof(uint8_t));
}

void loop() {
}
