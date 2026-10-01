// 第14回：責務は「計算すること」だけ
// センサもモータも知らないので、この計算だけを切り離して確かめられる。

#pragma once

class PIDController {
public:
    /**
     * @brief コンストラクタ
     * @param kp 比例ゲイン
     * @param ki 積分ゲイン
     * @param kd 微分ゲイン
     * @param intervalSec 呼び出し間隔(秒)
     */
    PIDController(float kp, float ki, float kd, float intervalSec);

    /**
     * @brief 偏差から操作量を求める
     * @param error 目標値と現在値の差
     * @return 操作量
     */
    float compute(float error);

    /**
     * @brief 内部に溜めた状態を消す
     */
    void reset();

private:
    float kp;
    float ki;
    float kd;
    float intervalSec;

    float integral;
    float previousError;
};
