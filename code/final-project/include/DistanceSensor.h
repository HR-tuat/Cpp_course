#pragma once

#include "Sensor.h"

class DistanceSensor : public Sensor {
public:
    DistanceSensor(int pin);

    void update() override;

    int getDistanceMm() const;

private:
    int pin;
    int distanceMm;
};
