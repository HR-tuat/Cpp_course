# 最終課題：簡易自律ロボット

`include/` と `src/` の雛形を埋めて完成させる。詳しい要件はサイトの
[最終課題](https://hr-tuat.github.io/final-project/) を参照。

## 必須要件

- クラス：`Robot` / `Motor` / `Controller` / `Sensor` / `IMU` / `DistanceSensor`
- 内部データは原則 `private`
- `Sensor` を基底クラスとする継承（`IMU` / `DistanceSensor`）
- `virtual` / `override` によるポリモーフィズム
- 状態は `enum class RobotState` で管理

## 進め方

1. クラス図を紙に書く
2. `.h` を先に書く（何ができるかを決める）
3. `.cpp` を実装する
4. `main.cpp` は短いままに保つ
