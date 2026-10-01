#include <Arduino.h>

#include "LED.hpp"

LED::LED(int pin)
    : Device(pin), state(false) {  // 親のコンストラクタを先に呼ぶ
}

void LED::on() {
    state = true;
    digitalWrite(pin, HIGH);  // protected なので子からは使える
}

void LED::off() {
    state = false;
    digitalWrite(pin, LOW);
}

void LED::toggle() {
    if (state) {
        off();
    } else {
        on();
    }
}
