// 第3回：関数に切り出す
// 同じ処理を関数にまとめ、loop() を読みやすくする。

#include <Arduino.h>

const int LED_PIN = 2;
const int BLINK_MS = 300;

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
}

void ledOff()
{
    digitalWrite(LED_PIN, LOW);
}

void blink(int times)
{
    for (int i = 0; i < times; i++)
    {
        ledOn();
        delay(BLINK_MS);

        ledOff();
        delay(BLINK_MS);
    }
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    blink(3);
    delay(1000);
}
