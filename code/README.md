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
pio device monitor   # シリアルモニタ
```

ボードを変える場合は各 `platformio.ini` の `board` を書き換える。
