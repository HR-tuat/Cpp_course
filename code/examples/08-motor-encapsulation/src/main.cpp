#include <Arduino.h>

#include "Motor.h"

Motor motor(5);

void setup()
{
    Serial.begin(115200);
    motor.begin();

    // 範囲外の値を渡しても内部で丸められる
    motor.setSpeed(-100000);
    Serial.println(motor.getSpeed()); // 0

    motor.setSpeed(500);
    Serial.println(motor.getSpeed()); // 100
}

void loop()
{
}
