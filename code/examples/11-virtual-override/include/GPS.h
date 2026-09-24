#pragma once

#include "Sensor.h"

class GPS : public Sensor {
public:
    GPS();

    void update() override;
    void print() const override;

private:
    float latitude;
    float longitude;
};
