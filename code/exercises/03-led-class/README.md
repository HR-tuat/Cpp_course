# 演習 Level 3：LEDクラス

`include/LED.h` と `src/LED.cpp` の TODO を埋めて、`main.cpp` がそのまま動くようにする。

## 要件

- コンストラクタでピン番号を受け取り、メンバ初期化リストで初期化する
- `begin()` で `pinMode()` を呼ぶ
- `on()` / `off()` / `toggle()` を実装する
- メンバ変数は `private` にする

## 確認

書き込んで、LEDが1秒周期で点滅すれば完成。
