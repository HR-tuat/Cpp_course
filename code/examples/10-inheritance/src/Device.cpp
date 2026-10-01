#include <Arduino.h>

#include "Device.hpp"

Device::Device(int pin)
    : pin(pin) {
}

void Device::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    // LED でもモータでも、ここに来るのは Device に1つだけ書いた begin()
    Serial.println("Device::begin()");
}

int Device::getPin() const {
    return pin;
}
