// 第11回〜第12回：共通インターフェース

#pragma once

class Sensor
{
public:
    virtual ~Sensor() = default;

    // 派生クラスに実装を強制する（純粋仮想関数）
    virtual void update() = 0;
    virtual void print() const = 0;
};
