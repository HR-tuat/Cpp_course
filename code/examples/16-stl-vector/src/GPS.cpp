#include <Arduino.h>

#include "GPS.hpp"

GPS::GPS()
    : latitude(35.6586f), longitude(139.7454f) {
}

void GPS::update() {
    // 実機ではGPSモジュールから読み取る
    latitude += 0.0001f;
    longitude += 0.0001f;
}

void GPS::print() const {
    Serial.print("GPS  lat=");
    Serial.print(latitude, 4);
    Serial.print(" lon=");
    Serial.println(longitude, 4);
}
