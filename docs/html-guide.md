# ページの書き方

サイトのHTMLを書くときの手引き。受講者向けと講師向けの出し分けが中心。

- 設計の背景や「なぜそうなっているか」は [`.claude/CLAUDE.md`](../.claude/CLAUDE.md) にある
- 講師モードの入り方は [`README.md`](../README.md) にある

## 目次

- [新しいページを作る](#新しいページを作る)
- [共通シェル](#共通シェル)
- [受講者 / 講師の出し分け](#受講者--講師の出し分け)
- [本文で使う部品](#本文で使う部品)
- [C++のコード](#cのコード)
- [やってはいけないこと](#やってはいけないこと)
- [確認](#確認)

---

## 新しいページを作る

手順は2つだけ。

1. 既存のページをコピーして `site/` 以下に置く
2. `site/scripts/data/lessons.ts` の `PAGES` に1行足す

ビルド設定は触らなくてよい。`vite.config.ts` が `site/` を走査して `.html` を自動で拾う。
サイドバーと「前へ / 次へ」も `PAGES` から生成される。

```ts
{ id: 'lesson-16', path: 'lessons/16-xxx.html', label: '第16回', title: 'タイトル', group: 'lessons' },
```

| フィールド | 内容 |
| --- | --- |
| `id` | HTMLの `<body data-page="...">` と**厳密に一致**させる |
| `path` | `site/` からの相対パス |
| `label` | サイドバー左側の短いラベル（`第3回`、`22章`、該当なしは `—`） |
| `title` | ページタイトル |
| `group` | `guide` / `lessons` / `tasks` |
| `audience` | 省略で両方に表示。[出し分け](#ページ単位)を参照 |

`PAGES` の**並び順がそのまま「前へ / 次へ」の経路**になる。

## 共通シェル

新規ページは既存ページをコピーして作る。書き換えるのは次の4箇所だけ。

```html
<body data-page="lesson-16" data-base="../">
```

| 場所 | 書き換える内容 |
| --- | --- |
| `<title>` | `ページ名 \| マイコンのためのC++講座` |
| `<meta name="description">` | 1〜2文の説明 |
| `data-page` | `PAGES` の `id` と一致させる |
| `data-base` | サイトルートまでの相対パス |

`data-base` は階層の深さで決まる。

| ページの場所 | `data-base` | stylesheet の `href` |
| --- | --- | --- |
| `site/index.html` | `./` | `./styles/base.css` |
| `site/guide/*.html` | `../` | `../styles/base.css` |
| `site/lessons/*.html` | `../` | `../styles/base.css` |

`data-page` がずれると、サイドバーの現在地ハイライトと前へ/次へが**エラーを出さずに静かに壊れる**。

本文を書く場所は `<article class="prose">` の中。ページ見出しはこの形。

```html
<header class="page-head">
  <p class="eyebrow">第16回</p>
  <h1>タイトル</h1>
  <p class="lead">1文の要約。</p>
</header>
```

## 受講者 / 講師の出し分け

既定は**受講者向けの表示**。講師向けの記述は隠れている。

粒度は3段階ある。**迷ったら何も書かない**（＝両方に見せる）。大半のページは共有でよい。

| 粒度 | 書く場所 | 使う場面 |
| --- | --- | --- |
| ページまるごと | `lessons.ts` の `audience` | ページ全体が片方専用 |
| ブロック | `data-for` を節や囲みに | 節がまるごと片方向け |
| 文・語句 | `data-for` を `<p>` や `<span>` に | 語り方だけが違う |

### ページ単位

`PAGES` の行に `audience` を足す。**省略したら両方に表示**される。

```ts
{ id: 'guide-teaching-notes', path: 'guide/teaching-notes.html', label: '23章',
  title: '教える際の重要ポイント', group: 'guide', audience: 'teacher' },
```

| 値 | 意味 |
| --- | --- |
| 省略 | 両方に表示（共有ページ） |
| `'student'` | 受講者にだけサイドバーに出る |
| `'teacher'` | 講師にだけサイドバーに出る |

サイドバー・前へ/次へ・ページ内目次がこの値で絞られる。

### ブロック単位

節がまるごと片方向けなら `<section data-for="teacher">` で囲む。
本文中で「ここは受講者には見えていない」ことが分かるよう、先頭に目印を置く。

```html
<section data-for="teacher">
<p class="audience-mark">講師向け</p>

<h2 id="教材作成">教材作成</h2>

<p>……</p>
</section>
```

囲みひとつだけなら、そのまま属性を足せばよい。

```html
<aside class="callout callout-tip" data-for="teacher">
  <p class="callout-title">講師向け</p>
  <p>……</p>
</aside>
```

**講師向けブロックの中の見出しは、受講者のページ内目次からも自動で消える**（`toc.ts` が除外する）。

### 文・語句単位

同じ位置に両方を並べると書き分けになる。片方だけ書けば、一方にしか出ない文になる。

```html
<p data-for="student">「この機能はどのクラスに置くべきか」を自分で考える段階。</p>
<p data-for="teacher">「この機能はどのクラスに置くべきか」を受講者自身に考えさせる。</p>
```

文の途中だけ差し替えることもできる。

```html
<p>この機能はどのクラスに置くべきかを<span data-for="student">自分で考える</span><span data-for="teacher">受講者に考えさせる</span>段階。</p>
```

### どの要素にも付けられる

CSSは**一致しなかった側を隠しているだけ**で、一致した要素の `display` には触らない。
そのため要素の種類を選ばない。

| 要素 | 出たときの表示 |
| --- | --- |
| `<p>` `<section>` `<div>` | ブロック |
| `<span>` `<code>` `<strong>` | インライン（改行しない） |
| `<tr>` `<td>` | 表の行・セル |
| `<li>` | 箇条書き |
| `class="card-grid"` / `class="check"` | grid / flex のまま |

> **`display` を当て直す実装に変えないこと。** 一致した側に `display: block` を書くと、
> インラインが改行し、grid や flex が崩れる。

### 書き分けは最小限に

段落を2本書くと**そこだけ二重管理**になる。内容が変わらない部分まで複製しない。

- 語り方だけが違う → 1文だけ `data-for` で分ける
- どちらでも通る言い方にできる → 共有の文に書き直す
- 節がまるごと違う → `<section data-for>` で分ける（段落を交互に並べない）

### これはアクセス制御ではない

静的ホストなので、**配信したものはURLを知れば誰でも読める**。
講師向けページも `dist` に出力されている。切り替えボタンの合言葉もJSバンドルに平文で入っている。

**読まれて困るものは、解答例と同じく `vite.config.ts` でビルド対象から外すこと。**
JSやCSSで隠す実装に変えても意味がない。

## 本文で使う部品

### コード

```html
<figure class="code"><pre><code class="language-cpp">void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}</code></pre></figure>
```

`<` `>` `&` はHTMLエスケープする（`&lt;` `&gt;` `&amp;`）。

### 概念図

矢印や罫線を含む図は**コードではない**ので `figure.diagram` を使う。ハイライトされない。

```html
<figure class="diagram"><pre>Sensor
├── IMU
└── GPS</pre></figure>
```

### 囲み

```html
<aside class="callout callout-tip"><p class="callout-title">ポイント</p><p>……</p></aside>
```

| クラス | 使い分け |
| --- | --- |
| `callout-tip` | ポイント。教え方・考え方のこつ |
| `callout-note` | 補足。知っておくと良い程度のこと |
| `callout-warn` | 注意。ハマりどころ、壊れる操作 |

### 表

`table-wrap` で包む。包まないと狭い画面で本文ごと横スクロールする。
数字の列には `align-right` を付ける。

```html
<div class="table-wrap">
  <table>
    <thead><tr><th>週</th><th>内容</th></tr></thead>
    <tbody>
    <tr><td class="align-right">1</td><td>……</td></tr>
    </tbody>
  </table>
</div>
```

### 演習ボックス

講義ページの演習はこの形。`solution-slot` は**空のまま置く**。
解答例が公開されている回だけ、ビルド時にリンクが埋め込まれる。

```html
<section class="exercise">
  <h3 class="exercise-title">演習：LEDクラスを作る</h3>
  <p>……</p>
  <div class="solution-slot" data-solution></div>
</section>
```

### カード

```html
<div class="card-grid">
  <a class="card" href="guide/policy.html">
    <span class="card-eyebrow">1章</span>
    <span class="card-title">講座の基本方針</span>
    <span class="card-desc">1文の説明。</span>
  </a>
</div>
```

### 到達度チェックの項目

`checklist.html` 専用。`data-check` の値が localStorage のキーになる。

```html
<li><label class="check"><input type="checkbox" data-check="basic-variable"><span>変数を説明できる</span></label></li>
```

**既存の項目IDを変更すると受講者のチェック状態が消える。** 文言だけ直すときはIDを変えない。

## C++のコード

- **開き波括弧は行末**（K&R）。`else` は `} else {` と前の `}` に続ける
- インデントは**スペース4つ**
- 関数にはDoxygen形式のコメントを付ける

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
| `@param` | 引数ひとつにつき1行 |
| `@return` | 返す値。`void` の関数には書かない |

講義ページの短い断片（`if (x) {` だけの例など）にまで付ける必要はない。
書き方そのものは第3回「関数」の「コメントの書き方」で説明している。

> 元資料の草案はAllman（波括弧を次の行に置く）のままなので、引き写すときは波括弧を直す。

## やってはいけないこと

| やること | 何が起きるか |
| --- | --- |
| `data-base` を消す / DOMから深さを推測する実装に戻す | 本番だけナビのリンクが壊れる。Viteがstylesheetのhrefを差し替えるため |
| `<head>` のインラインスクリプトを消す | テーマと表示対象者の適用が描画後になり、ちらつく |
| 解答例のリンクをJSで描画する実装に戻す | 環境によってリンクが表示されない |
| 見せたくないものをJSやCSSで隠す | 静的ホストでは配信された時点で読める。ビルドから外すしかない |
| `data-for` の一致側に `display` を当てる | インラインが改行し、grid / flex が崩れる |
| `data-check` のIDを変える | 受講者のチェック状態が消える |
| 解答例ページを `PAGES` に足す | 未公開の回が混ざって前へ/次への経路が壊れる |

## 確認

```bash
npm run build     # 型チェック込み。ここまで通す
npm run preview   # ビルド結果を配信して表示を確認
```

表示の確認は、**受講者表示と講師表示の両方**で行う。
講師表示に入るには `?teacher=cpp` を付けたURLを一度開く（[README](../README.md) 参照）。

変更は `main` に直接 push せず、作業ブランチを切ってPRを出す。
