#pragma once

class Motor
{
public:
    Motor(int pin);

    void begin();
    void setSpeed(int speed);
    void stop();

private:
    int pin;
    int speed;
};
