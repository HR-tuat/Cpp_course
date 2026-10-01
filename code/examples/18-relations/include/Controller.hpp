// 第18回：相手を「指すだけ」なので、ヘッダでは前方宣言で足りる

#pragma once

class Robot;  // 前方宣言：Robotというクラスがある、とだけ伝える

class Controller {
public:
    /**
     * @brief コンストラクタ
     * @param robot 判断のときに状態を聞く相手
     * @note 受け取った参照は保存するだけ。ここでは使わない
     *       （Robotのメンバがまだ初期化されていない）。
     */
    explicit Controller(Robot& robot);

    /**
     * @brief 状態を見て、止めるかどうかを決める
     */
    void update();

private:
    Robot& robot;  // 参照するだけ。所有はしない
};
