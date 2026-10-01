// 第15回：約束ごと（第12回）

#pragma once

class Sensor {
public:
    virtual ~Sensor() = default;

    /**
     * @brief センサの値を読み直す
     */
    virtual void update() = 0;
};
