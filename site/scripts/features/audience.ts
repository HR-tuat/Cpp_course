/**
 * 表示対象者（受講者 / 講師）の切り替えと、講師モードの解錠。
 *
 * サイドバーと前へ/次へはこの値でページを絞り、本文中の [data-for] ブロックは
 * CSSで出し分ける。既定は受講者側。
 *
 * 講師モードは合言葉つきのURL（ ?teacher=<合言葉> ）を一度開くと解錠され、
 * 以降はヘッダに切り替えボタンが出る。解錠していないブラウザにはボタン自体が出ない。
 *
 * これは本当のロックではない。合言葉はJSバンドルに含まれるし、localStorageは
 * DevToolsから直接書き換えられる。「受講者がうっかり講師モードに入らない」ための
 * 掛け金であって、読ませないための仕組みではない。本当に見せたくないものは、
 * vite.config.ts の htmlEntries() でビルド対象から外すしかない。
 */

import { AUDIENCE_TITLES, PAGES, visibleTo, type Audience } from '../data/lessons';
import { currentPageId, siteBase } from '../components/nav';

const AUDIENCE_KEY = 'cpp-course:audience';
const UNLOCK_KEY = 'cpp-course:teacher-key';
const URL_PARAM = 'teacher';

/**
 * 合言葉。既定値は README にも書いてあるので、受講者にも見える前提。
 * 伸ばしたくなったら VITE_TEACHER_KEY で上書きできるが、
 * そのときは README のURLも直すこと。
 */
const TEACHER_KEY = import.meta.env.VITE_TEACHER_KEY || 'cpp';

function read(key: string): string | null {
  try {
    return window.localStorage.getItem(key);
  } catch {
    return null;
  }
}

function write(key: string, value: string | null): void {
  try {
    if (value === null) window.localStorage.removeItem(key);
    else window.localStorage.setItem(key, value);
  } catch {
    /* 保存できなくても、そのページの表示は成立させる */
  }
}

function storedAudience(): Audience | null {
  const value = read(AUDIENCE_KEY);
  return value === 'student' || value === 'teacher' ? value : null;
}

/**
 * URLに合言葉が付いていたら取り込み、アドレスバーからは消す。
 * 残したままだと、講師が画面を共有したときやURLをコピーしたときに漏れる。
 */
function consumeKeyFromUrl(): void {
  const url = new URL(window.location.href);
  const given = url.searchParams.get(URL_PARAM);
  if (given === null) return;

  url.searchParams.delete(URL_PARAM);
  window.history.replaceState(null, '', url.toString());

  if (given === TEACHER_KEY) write(UNLOCK_KEY, given);
}

/**
 * 解錠済みか。合言葉そのものを保存して突き合わせているので、
 * 合言葉を変えれば古い解錠は自動的に無効になる。
 */
function unlocked(): boolean {
  return read(UNLOCK_KEY) === TEACHER_KEY;
}

/**
 * 各HTMLの<head>のインラインスクリプトが描画前に同じ値を入れている（ちらつき防止）。
 * ここで入れ直すのは、切り替えボタンを押したときと、合言葉が変わっていたときのため。
 */
function apply(audience: Audience): void {
  document.documentElement.dataset.audience = audience;

  const button = document.querySelector<HTMLButtonElement>('.audience-toggle');
  if (!button) return;

  const label = button.querySelector<HTMLElement>('.audience-toggle-label');
  if (label) label.textContent = AUDIENCE_TITLES[audience];
  button.title = `表示を切り替える（現在: ${AUDIENCE_TITLES[audience]}向け）`;
}

/** いま開いているページ。解答例ページはPAGESに無いのでundefinedになる */
function currentPage() {
  const id = currentPageId();
  return PAGES.find((page) => page.id === id);
}

/**
 * 表示対象者を決めて適用する。
 *
 * 解錠済みの場合にかぎり、講師向けページのURLを直接開いたときはそのページに
 * 合わせて切り替える。そうしないとサイドバーに現在地が無く、前へ/次へも出ない
 * 行き止まりになる。未解錠のブラウザは常に受講者表示のままにする。
 */
export function setupAudience(onChange: (audience: Audience) => void): Audience {
  consumeKeyFromUrl();

  const isUnlocked = unlocked();
  if (!isUnlocked) write(UNLOCK_KEY, null);

  // CSSはこの属性を見て切り替えボタンを出す
  document.documentElement.toggleAttribute('data-teacher', isUnlocked);

  let audience: Audience = 'student';
  if (isUnlocked) {
    const page = currentPage();
    audience = storedAudience() ?? 'student';

    if (page?.audience && page.audience !== audience) {
      audience = page.audience;
      write(AUDIENCE_KEY, audience);
    }
  }

  apply(audience);
  if (!isUnlocked) return audience;

  const button = document.querySelector<HTMLButtonElement>('.audience-toggle');
  button?.addEventListener('click', () => {
    const next: Audience = audience === 'student' ? 'teacher' : 'student';
    write(AUDIENCE_KEY, next);

    // 切り替えた先に現在のページが無い場合は、行き止まりになるのでトップへ戻す
    const here = currentPage();
    if (here && !visibleTo(here, next)) {
      window.location.href = `${siteBase()}index.html`;
      return;
    }

    audience = next;
    apply(next);
    onChange(next);
  });

  return audience;
}
