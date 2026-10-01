#pragma once

#include "Sensor.hpp"

class DistanceSensor : public Sensor {
public:
    DistanceSensor(int pin);

    void update() override;

    int getDistanceMm() const;

private:
    int pin;
    int distanceMm;
};
