// 第10回：共通部分を親にまとめ、固有の機能を子に置く
//
//   Device
//    ├── LED
//    └── Motor
//
// begin() と getPin() は Device に1つだけ書いてある。
// LED も Motor もそれを書き直していない。

#include <Arduino.h>

#include "LED.hpp"
#include "Motor.hpp"

LED led(LED_BUILTIN);  // ボード上のRGB LED
Motor motor(24);       // モータはつないでいない。結果はシリアルの出力で見る

void setup() {
    Serial.begin(115200);
    delay(1000);

    // どちらも Device から継承した begin() を呼んでいる
    led.begin();
    motor.begin();

    // getPin() も Device に1つだけ書いてある。
    // LED 側は LED_BUILTIN（内蔵RGB LEDを指す特別な値）なので表示しない
    Serial.print("motor pin = ");
    Serial.println(motor.getPin());

    // 固有の機能は子クラスにある
    motor.setSpeed(60);
    motor.setSpeed(500);  // 丸められて 100 になる
}

void loop() {
    led.toggle();
    delay(500);
}
