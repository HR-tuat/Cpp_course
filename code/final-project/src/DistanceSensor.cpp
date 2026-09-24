#include <Arduino.h>

#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin)
    : pin(pin), distanceMm(0) {
}

void DistanceSensor::update() {
    // TODO: 実機の距離センサから読み取る
}

int DistanceSensor::getDistanceMm() const {
    return distanceMm;
}
