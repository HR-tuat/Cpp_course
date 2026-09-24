# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

「マイコンのためのC++講座」の教材サイト。GitHub Pages（<https://hr-tuat.github.io/Cpp_course/>）で公開する。
ページ本文・コメント・コミットメッセージはすべて日本語で書く。

## 変更の出し方

**`main` へ直接コミット・push しない。必ず作業ブランチを切ってPRを作成し、マージは作業者に委ねる。**

```bash
git checkout -b <branch>
git add -A && git commit
git push -u origin <branch>
gh pr create --base main --title "..." --body "..."
```

急ぎの修正でも例外にしない（公開サイトが壊れている状況でもPR経由で対応した実績がある）。
`main` への push はデプロイを走らせるため、マージの判断は必ず人が行う。

作業前に `git pull` すること。GitHub上で直接編集されている場合があり、手元が古いまま
ビルドすると、公開済みの内容と食い違って原因の分からない不具合に見える。

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
**ページを増やしてもビルド設定の変更は不要**。出力先は `<repo>/dist/`。

`base` は `/Cpp_course/`。プロジェクトページ（`hr-tuat.github.io/Cpp_course/`）で配信するため、
**リポジトリ名を変えたら `vite.config.ts` の `base` も必ず合わせる**。ここがずれると
`/assets/main-*.css` などが全て404になり、素のHTMLだけが表示される。
ユーザーサイト（`<ユーザー名>.github.io`）に移す場合のみ `/` に戻す。

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

### 解答例の公開

`site/scripts/data/solutions.ts` の `published` が公開スイッチ。
これは**受講者にリンクを見せるか**の切り替えであり、配信するかどうかではない。

| `published` | 受講者 | 講師 | `dist` |
| --- | --- | --- | --- |
| `true` | リンクが出る | リンクが出る | 出力される |
| `false` | 「未公開」表示だけ | 「講師のみ」リンクが出る | **出力される** |

**未公開の回も `dist` に出ているので、URLを知っていれば受講者でも読める。**
2026-09-25に「講師が全回の解答をサイト上で見られること」を優先して、
漏れるリスクを了承で受け入れた選択である（それ以前はビルドから落としていた）。

**本当に出したくないものが出てきたら、`vite.config.ts` の `htmlEntries()` で
rollup の入力から落とすしかない。** 静的ホストでは配信したものは必ず読まれるので、
JSやCSSで隠しても防御にはならない。

解答例へのリンク（一覧表と講義ページの演習ボックス）は、`vite.config.ts` の
`solutionsHtml()` プラグインが**ビルド時にHTMLへ直接書き出す**。`data-solution-index` を
表に、`data-solution` をリンクに置換している。以前はクライアントのJSで描画していたが、
環境によってリンクが表示されない問題が出たため静的生成に変えた。**JS描画に戻さないこと。**
静的な内容であり、表示ソースや `curl` でそのまま検証できる利点もある。

解答例ページは `PAGES`（`lessons.ts`）には載せない。未公開の回が混ざると前へ/次への経路が
壊れるため、`SOLUTIONS` 側だけで管理し、`renderPager()` が `solution-` 接頭辞を見て
講義への戻り導線だけを出している。

### 受講者向け / 講師向けの出し分け

1つのサイトを「表示対象者」で切り替えている。切り替えはヘッダの`.audience-toggle`で、
localStorage（`cpp-course:audience`）に保存する。既定は`student`。

- **ページ単位** … `lessons.ts`の`PageMeta.audience`。**省略したら両方に表示**される（共有ページ）。
  大半のページは共有なので、省略を既定にしてある。サイドバーと前へ/次へはこの値で絞られる。
- **ブロック・文単位** … 本文中の`data-for="teacher"` / `data-for="student"`。
  同じ位置に両方置けば文章の書き分けになる（`exercises/index.html`のLevel 6が例）。

  `components.css`は**隠す側だけ**を書いていて、**一致した要素の`display`には触らない**。
  おかげで`p` / `section`でも`span` / `code`でも`tr` / `li`でもそのまま使える。
  **一致した側に`display: block`を当てる実装に戻さないこと**（インラインが改行し、
  `.card-grid`のgridや`.check`のflexが崩れる）。
  `data-audience`が入る前は全部隠すので、JSが動かないときに講師向けの記述は漏れない。
  `toc.ts`は非表示ブロックの見出しを目次から除く。

**これはアクセス制御ではない。** 静的ホストでは配信済みのページはURLを知れば読める。
本当に見せたくないものは、`vite.config.ts`の`htmlEntries()`でビルド対象から外すしかない
（解答例は2026-09-25にこの仕組みを外し、全回を配信するようになった）。

#### 講師モードの解錠

切り替えボタンは**解錠するまで表示されない**。合言葉つきURL（`?teacher=<合言葉>`）を
一度開くと解錠され、localStorage（`cpp-course:teacher-key`）に合言葉そのものが保存される。
クエリは`history.replaceState()`で**アドレスバーから消す**（画面共有やURLコピーで漏れないため）。

合言葉は`VITE_TEACHER_KEY`からビルド時に埋め込む。GitHub ActionsはリポジトリのSecretsの
`TEACHER_KEY`を`deploy.yml`経由で渡す。**未設定なら`audience.ts`の既定値（`cpp`）のまま**になる（READMEにそのURLを載せてあるので、
変えるならREADMEも直す）。
保存しているのが合言葉そのものなので、**合言葉を変えれば古い解錠は自動的に無効になる**。

**これは鍵ではなく掛け金である。** 合言葉はJSバンドルに平文で入っているし、localStorageは
DevToolsから直接書ける。「受講者がうっかり講師モードに入らない」ためのもので、
読ませないためのものではない。**パスワード入力に変えても強度は上がらない。**

解錠済みの場合にかぎり、講師向けページのURLを直接開いたときはそのページに合わせて
自動で切り替わる（`audience.ts`）。そうしないと、サイドバーに現在地がなく
前へ/次へも出ない行き止まりになる。未解錠のブラウザは常に受講者表示のままにする。

各HTMLの`<head>`のインラインスクリプトが、テーマと同じく描画前に
`documentElement.dataset.audience`と`dataset.teacher`を入れている（ちらつき防止）ので消さない。

### 到達度チェックの永続化

`checklist.html` の各 `data-check="..."` が localStorage のキーになる（`cpp-course:checklist:v1`）。
**既存の項目IDを変更すると受講者のチェック状態が失われる**。文言の修正はIDを変えずに行う。

## 教材コンテンツの出どころ

- `Cpp引継ぎ資料草案.md`（全26章）と `フォルダ構成.md` が元資料。どちらも `.gitignore` 済みで、
  リポジトリには含まれない。
- サイトの各ページは章に対応する：トップ=0章、guide=1・2・20・21・23章、lessons/00〜15=3〜18章、
  final-project=19・25章、exercises=22章、checklist=24章、advanced=26章。
  本文を直すときは、対応する章の意図（何を教えるための例か）を崩さない。
- C++のコード例は**開き波括弧を行末に置く**スタイル（K&R）で統一する。`code/` のサンプルも同じ。
  `else` は `} else {` と前の `}` に続ける。
  **元資料の草案はAllmanだが、サイトと`code/`は2026-09-24にK&Rに寄せた**ので、
  草案から引き写すときは波括弧を直すこと。
- 関数にはDoxygen形式のコメントを付ける。

  ```cpp
  /**
   * @brief 倍化関数
   * @param value 値
   * @param flag 有効化フラグ
   * @return 倍化した値(有効時)
   */
  int doubleValue(int value, bool flag) {
      if (flag) {
          return value * 2;
      } else {
          return value;
      }
  }
  ```

  | タグ | 書く内容 |
  | --- | --- |
  | `@brief` | その関数が何をするか。1行 |
  | `@details` | 詳細な説明。複数行にわたってもよい |
  | `@param` | 引数ひとつにつき1行。`@param[in]` / `@param[out]` / `@param[in,out]` で入出力を示せる |
  | `@return` | 返す値。`void` の関数には書かない |
  | `@note` | 使い方の注意点 |
  | `@todo` | 今後実装する予定の機能や改善点 |
  | `@file` | **ファイル自体の説明**。関数に付けるものではなく、**ファイル先頭**に書く |

  講義ページの短い断片（`if (x) {` だけの例など）にまで付ける必要はない。
  `code/` の関数と、クラスのメンバ関数を見せる例が対象。

  第3回「コメントの書き方」の表と `docs/html-guide.md` は受講者向けに絞ってあるので、
  **ここと一致していなくてよい**。揃えにいかないこと。
- インクルードガードは `LED_H` の形にする。`#endif` に `// LED_H` とコメントを付ける。
  **先頭のアンダースコアと二重アンダースコアは使わない**（`__LED_H__` や `_LED_H` は
  規格上、処理系に予約された名前）。
  `code/` のヘッダは `#pragma once` で統一してある。`#ifndef` 形式は第7回の説明にだけ出てくる。

## デプロイ

`main` への push で `.github/workflows/deploy.yml` が `npm ci` → `npm run typecheck` →
`vite build` → Pages公開を行う。`npm ci` を使うため **`package-lock.json` は必ずコミットする**。
