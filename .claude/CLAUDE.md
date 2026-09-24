# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

「マイコンのためのC++講座」の教材サイト。GitHub Pages（<https://hr-tuat.github.io/>）で公開する。
ページ本文・コメント・コミットメッセージはすべて日本語で書く。

## コマンド

```bash
npm run dev        # 開発サーバ（site/index.html を開く）
npm run typecheck  # tsc --noEmit のみ
npm run build      # typecheck → vite build → リポジトリ直下の dist/
npm run preview    # ビルド結果を配信して確認
```

テストフレームワークは導入していない。変更後の確認は `npm run build`（型チェックを含む）まで通すこと。

`code/` 以下は独立したPlatformIOプロジェクトで、サイトのビルドとは無関係：

```bash
cd code/examples/00-blink
pio run              # ビルド
pio run -t upload    # ESP32へ書き込み
pio device monitor
```

## アーキテクチャ

### Viteのrootは `site/`（リポジトリ直下ではない）

`vite.config.ts` は `site/` を再帰的に走査し、見つけた `.html` をすべてrollupの入力にする。
**ページを増やしてもビルド設定の変更は不要**。出力先は `<repo>/dist/`、`base` は `/`
（ユーザーサイトのためルート配信。プロジェクトページに変える場合のみ `/<リポジトリ名>/` にする）。

### ナビゲーションの単一情報源は `site/scripts/data/lessons.ts`

`PAGES` 配列（25件）からサイドバーと「前へ / 次へ」を実行時に生成する。
ページを追加・改名するときは **HTMLを置く → `PAGES` に1行足す** の2手順のみ。

- 各HTMLの `<body data-page="...">` は `PAGES` の `id` と厳密に一致させる。ずれるとサイドバーの
  現在地ハイライトと前へ/次へが無効になる（エラーにはならず静かに壊れる）。
- `READING_ORDER` は `PAGES` の並び順そのもの。順序を変えると前へ/次への経路が変わる。

### `<body data-base="../">` を消さない

ページは `site/` 直下・`guide/`・`lessons/` と階層の深さがまちまちで、ナビのリンクはこの属性から
サイトルートへの相対パスを得ている（`nav.ts` の `siteBase()`）。
かつてstylesheetの `href` から深さを逆算していたが、**Viteがビルド時にCSSをバンドルして
`link` を `/assets/main-*.css` に差し替えるため、本番だけリンクが壊れた**。
DOMから深さを推測する実装に戻さないこと。

### ページの共通シェル

25ページはすべて同一構造（skip-link → `.site-header` → `.layout`（`[data-nav]` / `.prose` /
`[data-toc]`）→ `[data-pager]` → `.site-footer` → `main.ts`）。新規ページは既存ページを
コピーして作り、`data-page` / `data-base` / `<title>` / `description` を書き換える。
読み込むスクリプトは `scripts/main.ts` の1本だけで、そこから nav / pager / toc / codeBlock /
checklist を初期化する。

### C++ハイライタは自前実装

`scripts/components/codeBlock.ts` に外部ライブラリなしで実装している。`RULES` は
**先に書いたルールが優先**される単一の結合正規表現に畳まれるため、並び順（コメント → 文字列 →
プリプロセッサ → キーワード → 型 → 数値 → 関数名）に意味がある。
対象は `<code class="language-cpp">` のみ。矢印を含む概念図は `figure.diagram` を使い、
ハイライトしない。

### テーマとCSS変数

配色はすべて `styles/base.css` のカスタムプロパティ。ダーク値は
**`@media (prefers-color-scheme: dark)` の `:root:not([data-theme="light"])` と
`:root[data-theme="dark"]` の2箇所に同じ内容を書く**必要がある（片方だけ直すと
OS設定と手動切り替えで食い違う）。同じ二重定義が `styles/code.css` のトークン色にもある。
各HTMLの `<head>` にある小さなインラインスクリプトが保存済みテーマを描画前に適用している
（ちらつき防止）ので消さない。

### 到達度チェックの永続化

`checklist.html` の各 `data-check="..."` が localStorage のキーになる（`cpp-course:checklist:v1`）。
**既存の項目IDを変更すると受講者のチェック状態が失われる**。文言の修正はIDを変えずに行う。

## 教材コンテンツの出どころ

- `Cpp引継ぎ資料草案.md`（全26章）と `フォルダ構成.md` が元資料。どちらも `.gitignore` 済みで、
  リポジトリには含まれない。
- サイトの各ページは章に対応する：トップ=0章、guide=1・2・20・21・23章、lessons/00〜15=3〜18章、
  final-project=19・25章、exercises=22章、checklist=24章、advanced=26章。
  本文を直すときは、対応する章の意図（何を教えるための例か）を崩さない。
- C++のコード例は草案に合わせて**開き波括弧を次の行に置く**スタイル（Allman）で統一する。
  `code/` のサンプルも同じ。

## デプロイ

`main` への push で `.github/workflows/deploy.yml` が `npm ci` → `npm run typecheck` →
`vite build` → Pages公開を行う。`npm ci` を使うため **`package-lock.json` は必ずコミットする**。
