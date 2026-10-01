# 受講者向けC++コード

サイト（`site/`）とは別管理。各ディレクトリは `platformio.ini` を含む独立した
PlatformIOプロジェクトで、VS Code + PlatformIO でフォルダを開けばそのままビルドできる。

| ディレクトリ | 内容 |
|---|---|
| `examples/` | 各回のサンプル。授業中に一緒に動かす |
| `exercises/` | 演習の雛形（TODOを埋める） |
| `solutions/` | 解答例（講師用・公開方針は要相談） |
| `final-project/` | 最終課題の雛形（`src/` `include/` 構成） |

## ビルド

```bash
cd code/examples/00-blink
pio run              # ビルド
pio run -t upload    # 書き込み
pio device monitor   # シリアルモニタ（115200 bps）
```

ボードを変える場合は各 `platformio.ini` の `board` を書き換える。

## examples/ と講義ページの対応

各回の講義ページの「動かして確かめる」で紹介しているサンプル。
**全19回ぶんあり、1回につき1つ**。

| 回 | ディレクトリ | 何を見せるか |
|---|---|---|
| 第0回 | `00-blink` | `setup()` と `loop()` |
| 第1回 | `01-variables` | 型と演算子。`7 / 2` が `3` になる |
| 第2回 | `02-control` | `if` / `else if` / `switch` / `for` / `while` |
| 第3回 | `03-functions` | 同じ処理を関数にまとめる |
| 第4回 | `04-pointers` | アドレスと値、ポインタと参照の違い |
| 第5回 | `05-cpp-basics` | `const` / 名前空間 / オーバーロード / `const`参照 |
| 第6回 | `06-led-class` | 1ファイルの中でクラスを書く |
| 第7回 | `07-led-header` | `.hpp` と `.cpp` に分ける |
| 第8回 | `08-motor-encapsulation` | 範囲の制限をクラス内部に閉じる |
| 第9回 | `09-robot-state` | `enum class` と `switch` |
| 第10回 | `10-inheritance` | `Device` → `LED` / `Motor`、`protected` |
| 第11回 | `11-virtual-override` | 親のポインタから子の実装を呼ぶ |
| 第12回 | `12-abstract` | 純粋仮想関数。抽象クラスは実体を作れない |
| 第13回 | `13-polymorphism` | `Sensor*` だけで3種類を回す |
| 第14回 | `14-design` | 1クラス1責務。まとめ役に計算式を置かない |
| 第15回 | `15-mcu-design` | ここまでの道具を1つのプログラムに組む |
| 第16回 | `16-stl-vector` | `std::vector`。個数が実行時に決まる場合 |
| 第17回 | `17-smart-pointer` | `unique_ptr`。`free heap` の増減を見る |
| 第18回 | `18-relations` | 前方宣言で循環includeを切る |

### サンプルを書くときの決まり

- **配線なしで動くこと。** 結果は内蔵LED（`LED_BUILTIN`）と `Serial` の出力だけで
  確かめられるようにする。センサやモータの値はプログラムの中で作り、その行に
  「実機では〜から読み取る」とコメントを入れる。
- **内蔵LEDは `LED_BUILTIN` と書く。`2` と直書きしない。**
  数字だと「自分でピン2にLEDを挿すのか」と読めてしまう。
  何もつないでいないピンを使う場合は、その行に「つないでいない」と書く。
- 唯一の例外は `06-led-class`。「同じクラスから2つ」を見せるので2個目のLEDが要るが、
  内蔵LEDは1つしかない。ピン4に外付けを挿すと2個目が光る（つながなくても
  コードの形は読める）。部品と配線はサイトの「開発環境 → 実物をつなぐ場合」にある。
- `Serial` を使うサンプルは `setup()` の先頭で `Serial.begin(115200)` のあとに
  `delay(1000)` を入れる。書き込み直後はモニタの接続が間に合わず、最初の数行が消える。
- 1回につき1つ。その回の主題だけを見せ、まだ教えていない機能を持ち込まない。
- 講義ページの「動かして確かめる」に貼る出力は**実際に動かした結果**にする。

### 規格

既定は Arduino のまま（多くの環境で `gnu++11`）。`17-smart-pointer` だけは
`std::make_unique` のために `platformio.ini` で引き上げている。

```ini
build_unflags = -std=gnu++11
build_flags = -Wall -std=gnu++17
```

### 手元での構文確認

ボードがなくても、`Arduino.h` のスタブを用意すれば PC 上で構文だけ確かめられる
（`pinMode` などを空実装にしたヘッダを1枚書き、`g++ -fsyntax-only` に食わせる）。
`exercises/` と `final-project/` は TODO を残した雛形なので、
そのままでは通らないのが正しい。
