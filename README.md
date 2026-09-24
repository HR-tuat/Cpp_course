# マイコンのためのC++講座

プログラミング未経験者が、12週間でESP32などのマイコン上のプログラムを
C++のクラスと複数ファイルで設計・実装できるようになることを目指す講座の教材。

公開サイト: <https://hr-tuat.github.io/Cpp_course/>

## 構成

```text
.
├── .github/workflows/deploy.yml  # push → npm ci → vite build → Pages公開
├── site/                         # Webサイト（Viteのroot）
│   ├── index.html                # 講座概要・対象・到達目標
│   ├── guide/                    # 基本方針・開発環境・授業計画・指導上の注意・受講者の進め方
│   ├── lessons/                  # 第0回〜第15回
│   ├── exercises/                # 演習問題の段階（Level 1〜6）
│   ├── final-project/            # 最終課題
│   ├── checklist.html            # 到達度チェック（localStorageに保存）
│   ├── advanced.html             # 発展内容
│   ├── styles/                   # base / layout / components / code
│   ├── scripts/                  # TypeScript（ナビ・目次・ハイライト・チェック）
│   └── public/                   # そのまま配信（図のSVGなど）
├── diagrams/                     # draw.io の元ファイル（.drawio）
├── code/                         # 受講者向けC++コード（PlatformIOプロジェクト）
│   ├── examples/                 # 各回のサンプル
│   ├── exercises/                # 演習の雛形（穴あき）
│   ├── solutions/                # 解答例（講師用）
│   └── final-project/            # 最終課題の雛形
├── package.json
├── tsconfig.json
└── vite.config.ts
```

## サイトの開発

```bash
npm ci
npm run dev        # 開発サーバ
npm run typecheck  # 型チェックのみ
npm run build      # dist/ に出力
npm run preview    # ビルド結果を確認
```

`main` への push で GitHub Actions がビルドし、GitHub Pages に公開する。

## ページを追加するとき

HTMLの書き方、受講者 / 講師の出し分け、本文で使う部品は
**[`docs/html-guide.md`](docs/html-guide.md)** にまとめてある。

1. `site/` 以下にHTMLを置く（`<body data-page="...">` を付ける）
2. `site/scripts/data/lessons.ts` の `PAGES` に1行追加する

サイドバーと「前へ / 次へ」は `lessons.ts` から自動生成されるため、
それ以外に手を入れる必要はない。ビルド対象のHTMLは `vite.config.ts` が
`site/` を走査して自動で拾う。

## 講師モード

このサイトは受講者向けの表示が既定で、指導ノートや授業計画などの講師向けの記述は隠れている。
講師表示に入るには、次のURLを一度開く。

```text
https://hr-tuat.github.io/Cpp_course/?teacher=cpp
```

開いたブラウザにだけ、ヘッダに「受講者 / 講師」の切り替えボタンが出る
（`?teacher=cpp` はアドレスバーから消える）。**ボタンを1回押すと講師表示**になり、
以降は普通のURLでも保たれる。受講者表示に戻すにはもう一度押す。
解錠ごと戻すときは、そのブラウザのサイトデータを消す。

手元で確かめるときは `npm run dev` で開いたURLに `?teacher=cpp` を付ける。

**これは鍵ではない。** 合言葉はJSバンドルに平文で入っているし、このREADMEにも書いてある。
講師向けページ自体も配信されていて、URLを知っていれば読める。
受講者がうっかり切り替えないための掛け金でしかない。
**読まれて困るものは、`vite.config.ts` の `htmlEntries()` でビルドから外すしかない。**

合言葉を変えたいときは `VITE_TEACHER_KEY` で上書きできる（GitHub Actions は
リポジトリの Secrets の `TEACHER_KEY` を渡す）。登録すると `?teacher=cpp` では入れなくなるので、
**変えたらこの章のURLも直すこと**。

## 解答例の公開（段階公開）

各回の演習の解答例は `site/solutions/` にあり、**その回の授業が終わったあとに公開する**運用。

公開するには `site/scripts/data/solutions.ts` の該当する回の `published` を `true` にして
`main` に push する。それだけでよい。

```ts
{ lessonId: 'lesson-03', path: 'solutions/03-functions.html', ..., published: true },
```

`published` は、**受講者にリンクを見せるか**の切り替えである。

| `published` | 受講者 | 講師 |
| --- | --- | --- |
| `true` | リンクが出る | リンクが出る |
| `false` | 「未公開」表示だけ | 「講師のみ」リンクが出る |

講師が授業前に全回の解答を確かめられるよう、[講師モード](#講師モード)では
未公開の回にもリンクが出る。

> **注意。** 未公開の回も含めて、**解答例は全回が `dist` に出力されている**。
> リンクを出していないだけなので、`solutions/05-cpp-basics.html` のようなURLを
> 直接叩けば受講者でも読める。確実に伏せたい回がある場合は、
> `vite.config.ts` の `htmlEntries()` でビルド対象から落とす必要がある。

## 受講者向けコード

`code/` 以下の各ディレクトリは独立したPlatformIOプロジェクト。
詳細は [`code/README.md`](code/README.md) を参照。
