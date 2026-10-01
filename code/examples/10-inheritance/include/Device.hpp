// 第10回：共通部分を親クラスにまとめる

#pragma once

class Device {
public:
    /**
     * @brief コンストラクタ
     * @param pin 使用するピン番号
     * @note explicit は「引数1つのコンストラクタを勝手な型変換に使わせない」指定。
     *       付けておくと Device device = 5; のような書き方を防げる。
     */
    explicit Device(int pin);

    /**
     * @brief ピンを初期化する
     * @details LED でもモータでも手順は同じなので、親に置ける。
     */
    void begin();

    /**
     * @brief ピン番号を返す
     * @return ピン番号
     */
    int getPin() const;

protected:
    // 子クラスからは使わせるが、外部には見せない
    int pin;
};
