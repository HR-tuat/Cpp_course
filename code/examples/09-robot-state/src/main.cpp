// 第9回：状態を enum class で管理する

#include <Arduino.h>

enum class RobotState
{
    STOP,
    MOVE,
    ERROR
};

const int LED_PIN = 2;

RobotState state = RobotState::STOP;

void setState(RobotState next)
{
    state = next;
}

void updateLed()
{
    switch (state)
    {
    case RobotState::STOP:
        digitalWrite(LED_PIN, LOW);
        break;

    case RobotState::MOVE:
        digitalWrite(LED_PIN, HIGH);
        break;

    case RobotState::ERROR:
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
        break;
    }
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    setState(RobotState::MOVE);
}

void loop()
{
    updateLed();
    delay(50);
}
