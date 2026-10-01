// この main.cpp は変更しない

#include <Arduino.h>

#include "LED.hpp"

LED led(LED_BUILTIN);  // ボード上のRGB LED。配線なしで光る

void setup() {
    led.begin();
}

void loop() {
    led.toggle();
    delay(500);
}
