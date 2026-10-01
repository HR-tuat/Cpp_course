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

LED led(LED_BUILTIN);  // ボード上の内蔵LED
Motor motor(5);        // モータはつないでいない。結果はシリアルの出力で見る

void setup() {
    Serial.begin(115200);
    delay(1000);

    // どちらも Device から継承した begin() を呼んでいる
    led.begin();
    motor.begin();

    Serial.print("led   pin = ");
    Serial.println(led.getPin());
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
