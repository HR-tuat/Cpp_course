// 第6回：LEDクラス（1ファイル版）
// まずは main.cpp の中だけでクラスを書く。分割は第7回で行う。

#include <Arduino.h>

class LED
{
public:
    LED(int pin)
        : pin(pin), state(false)
    {
    }

    void begin()
    {
        pinMode(pin, OUTPUT);
        off();
    }

    void on()
    {
        state = true;
        digitalWrite(pin, HIGH);
    }

    void off()
    {
        state = false;
        digitalWrite(pin, LOW);
    }

    void toggle()
    {
        if (state)
        {
            off();
        }
        else
        {
            on();
        }
    }

private:
    int pin;
    bool state;
};

// 同じクラスから複数のオブジェクトを作れる
LED led1(2);
LED led2(4);

void setup()
{
    led1.begin();
    led2.begin();
}

void loop()
{
    led1.toggle();
    delay(500);

    led2.toggle();
    delay(500);
}
