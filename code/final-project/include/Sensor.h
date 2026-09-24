#pragma once

class Sensor {
public:
    virtual ~Sensor() = default;

    virtual void update() = 0;
};
