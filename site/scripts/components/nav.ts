/**
 * サイドバーと「前へ / 次へ」を lessons.ts から生成する。
 */

import {
  GROUP_TITLES,
  PAGES,
  READING_ORDER,
  visibleTo,
  type Audience,
  type GroupId,
  type PageMeta,
} from '../data/lessons';

/**
 * ページごとに階層の深さが違うため、サイトルートまでの相対パスを
 * <body data-base="../"> から受け取る（各HTMLが生成時に持っている）。
 */
export function siteBase(): string {
  return document.body.dataset.base ?? './';
}

export function href(page: PageMeta): string {
  return siteBase() + page.path;
}

export function currentPageId(): string {
  return document.body.dataset.page ?? '';
}

function groupMarkup(group: GroupId, currentId: string, audience: Audience): string {
  const pages = PAGES.filter((page) => page.group === group && visibleTo(page, audience));
  if (pages.length === 0) return '';

  const items = pages
    .map((page) => {
      const active = page.id === currentId ? ' aria-current="page"' : '';
      return `<li><a href="${href(page)}"${active}><span class="nav-num">${page.label}</span><span>${page.title}</span></a></li>`;
    })
    .join('');

  return `<div class="nav-group">
  <p class="nav-group-title">${GROUP_TITLES[group]}</p>
  <ul class="nav-list">${items}</ul>
</div>`;
}

export function renderNav(audience: Audience): void {
  const host = document.querySelector<HTMLElement>('[data-nav]');
  if (!host) return;

  const currentId = currentPageId();
  const groups: GroupId[] = ['guide', 'lessons', 'tasks'];
  host.innerHTML = groups.map((group) => groupMarkup(group, currentId, audience)).join('\n');

  setupToggle(host);
}

function setupToggle(sidebar: HTMLElement): void {
  const button = document.querySelector<HTMLButtonElement>('.nav-toggle');
  if (!button) return;

  const setOpen = (open: boolean): void => {
    sidebar.classList.toggle('is-open', open);
    button.setAttribute('aria-expanded', String(open));
  };

  button.addEventListener('click', () => {
    setOpen(!sidebar.classList.contains('is-open'));
  });

  // モバイルでリンクを踏んだら閉じる
  sidebar.addEventListener('click', (event) => {
    if ((event.target as HTMLElement).closest('a')) setOpen(false);
  });

  document.addEventListener('keydown', (event) => {
    if (event.key === 'Escape') setOpen(false);
  });
}

export function renderPager(audience: Audience): void {
  const host = document.querySelector<HTMLElement>('[data-pager]');
  if (!host) return;

  const current = currentPageId();

  // 解答例ページは READING_ORDER に含めない。対応する講義への戻り導線だけを出す
  if (current.startsWith('solution-')) {
    const lesson = PAGES.find((page) => page.id === current.replace('solution-', 'lesson-'));
    if (lesson) {
      host.innerHTML = `<a class="pager-prev" href="${href(lesson)}">
  <span class="pager-label">← 講義に戻る / ${lesson.label}</span>
  <span class="pager-title">${lesson.title}</span>
</a>`;
    }
    return;
  }

  // 対象者の違うページを挟まないよう、経路そのものを絞ってから前後を取る
  const order = READING_ORDER.filter((page) => visibleTo(page, audience));

  const index = order.findIndex((page) => page.id === current);
  if (index < 0) return;

  const prev = order[index - 1];
  const next = order[index + 1];
  const parts: string[] = [];

  if (prev) {
    parts.push(`<a class="pager-prev" href="${href(prev)}" rel="prev">
  <span class="pager-label">← 前へ / ${prev.label}</span>
  <span class="pager-title">${prev.title}</span>
</a>`);
  }

  if (next) {
    parts.push(`<a class="pager-next" href="${href(next)}" rel="next">
  <span class="pager-label">次へ / ${next.label} →</span>
  <span class="pager-title">${next.title}</span>
</a>`);
  }

  host.innerHTML = parts.join('\n');
}
