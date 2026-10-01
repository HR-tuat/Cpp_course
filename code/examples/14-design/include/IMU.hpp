// 第14回：責務は「姿勢を読むこと」だけ

#pragma once

class IMU {
public:
    IMU();

    /**
     * @brief 姿勢を読み直す
     */
    void update();

    /**
     * @brief 現在のロール角を返す
     * @return ロール角(度)
     */
    float getRoll() const;

private:
    float roll;
};
