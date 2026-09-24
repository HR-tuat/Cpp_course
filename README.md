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
│   ├── guide/                    # 基本方針・開発環境・授業計画・指導上の注意
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

1. `site/` 以下にHTMLを置く（`<body data-page="...">` を付ける）
2. `site/scripts/data/lessons.ts` の `PAGES` に1行追加する

サイドバーと「前へ / 次へ」は `lessons.ts` から自動生成されるため、
それ以外に手を入れる必要はない。ビルド対象のHTMLは `vite.config.ts` が
`site/` を走査して自動で拾う。

## 解答例の公開（段階公開）

各回の演習の解答例は `site/solutions/` にあり、**その回の授業が終わったあとに公開する**運用。

公開するには `site/scripts/data/solutions.ts` の該当する回の `published` を `true` にして
`main` に push する。それだけでよい。

```ts
{ lessonId: 'lesson-03', path: 'solutions/03-functions.html', ..., published: true },
```

`published: false` の回は **`vite.config.ts` がビルド対象から除外する**ため、`dist` に出力されず、
URLを直接叩いても 404 になる。JSで隠しているのではないので、静的ホストでも確実に非公開になる。
非公開に戻したいときは `false` に戻して push すれば、次のデプロイで消える。

## 受講者向けコード

`code/` 以下の各ディレクトリは独立したPlatformIOプロジェクト。
詳細は [`code/README.md`](code/README.md) を参照。
