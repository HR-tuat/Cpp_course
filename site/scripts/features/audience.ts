/**
 * 表示対象者（受講者 / 講師）の切り替え。
 *
 * サイドバーと前へ/次へはこの値でページを絞り、本文中の [data-for] ブロックは
 * CSSで出し分ける。既定は受講者側。
 *
 * これはアクセス制御ではない。静的ホストでは配信したものはURLを知れば読めるため、
 * 「誰に向けた導線を出すか」を切り替えているだけである。本当に見せたくないものは
 * 解答例と同じく vite.config.ts でビルド対象から外すこと。
 */

import { AUDIENCE_TITLES, PAGES, visibleTo, type Audience } from '../data/lessons';
import { currentPageId, siteBase } from '../components/nav';

const AUDIENCE_KEY = 'cpp-course:audience';

function stored(): Audience | null {
  try {
    const value = window.localStorage.getItem(AUDIENCE_KEY);
    return value === 'student' || value === 'teacher' ? value : null;
  } catch {
    return null;
  }
}

function save(audience: Audience): void {
  try {
    window.localStorage.setItem(AUDIENCE_KEY, audience);
  } catch {
    /* 保存できなくても表示は切り替える */
  }
}

/**
 * 各HTMLの<head>のインラインスクリプトが描画前に同じ値を入れている（ちらつき防止）。
 * ここで入れ直すのは、切り替えボタンを押したときと、保存に失敗する環境のため。
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
 * 講師向けページのURLを直接開いたときは、そのページに合わせて切り替える。
 * そうしないとサイドバーに現在地が無く、前へ/次へも出ない状態になる。
 */
export function setupAudience(onChange: (audience: Audience) => void): Audience {
  const page = currentPage();
  let audience: Audience = stored() ?? 'student';

  if (page?.audience && page.audience !== audience) {
    audience = page.audience;
    save(audience);
  }

  apply(audience);

  const button = document.querySelector<HTMLButtonElement>('.audience-toggle');
  button?.addEventListener('click', () => {
    const next: Audience = audience === 'student' ? 'teacher' : 'student';
    save(next);

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
