// 第12回：共通の「約束ごと」だけを決めるクラス

#pragma once

class Sensor {
public:
    virtual ~Sensor() = default;

    /**
     * @brief センサの値を読み直す
     * @note = 0 なので、ここに実装はない。継承した側が必ず実装する。
     */
    virtual void update() = 0;

    /**
     * @brief 現在の値をシリアルに表示する
     */
    virtual void print() const = 0;
};
