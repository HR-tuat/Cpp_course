# 図の元ファイル

draw.io（diagrams.net）の `.drawio` ファイルを置く。

## 書き出し手順

1. draw.io で `.drawio` を編集する
2. 「ファイル」→「形式を指定してエクスポート」→ SVG
3. `site/public/images/diagrams/` に保存する
4. HTMLからは `/images/diagrams/<名前>.svg` で参照する

元ファイルを消すと後から修正できなくなるため、SVGだけを更新しないこと。
