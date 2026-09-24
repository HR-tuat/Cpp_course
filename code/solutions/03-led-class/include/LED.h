#pragma once

class LED {
public:
    LED(int pin);

    void begin();
    void on();
    void off();
    void toggle();

private:
    int pin;
    bool state;
};
