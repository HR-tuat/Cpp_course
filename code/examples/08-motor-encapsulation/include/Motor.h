// 第8回：速度の範囲をクラス内部で守る

#pragma once

class Motor
{
public:
    Motor(int pin);

    void begin();

    // 0〜100 に制限して保持する
    void setSpeed(int speed);
    int getSpeed() const;

    void stop();

private:
    void apply();

    int pin;
    int speed;
};
