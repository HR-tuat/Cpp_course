// 第11回〜第12回：共通インターフェース

#pragma once

class Sensor {
public:
    virtual ~Sensor() = default;

    /**
     * @brief センサの値を読み直す
     * @note = 0 なので実装がない。派生クラスが必ず実装する（純粋仮想関数）。
     */
    virtual void update() = 0;

    /**
     * @brief 現在の値をシリアルに表示する
     */
    virtual void print() const = 0;
};
