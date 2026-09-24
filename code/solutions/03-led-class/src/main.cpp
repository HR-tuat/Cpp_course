#include <Arduino.h>

#include "LED.h"

LED led(2);

void setup() {
    led.begin();
}

void loop() {
    led.toggle();
    delay(500);
}
