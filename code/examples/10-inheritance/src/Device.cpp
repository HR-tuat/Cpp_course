#include <Arduino.h>

#include "Device.hpp"

Device::Device(int pin)
    : pin(pin) {
}

void Device::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    Serial.print("Device::begin() pin=");
    Serial.println(pin);
}

int Device::getPin() const {
    return pin;
}
