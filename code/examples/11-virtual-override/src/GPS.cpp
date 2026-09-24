#include <Arduino.h>

#include "GPS.h"

GPS::GPS()
    : latitude(0.0f), longitude(0.0f) {
}

void GPS::update() {
    // 実機ではGPSモジュールから読み取る
    latitude += 0.0001f;
    longitude += 0.0001f;
}

void GPS::print() const {
    Serial.print("GPS lat=");
    Serial.println(latitude, 4);
}
