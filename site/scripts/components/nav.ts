/**
 * サイドバーと「前へ / 次へ」を lessons.ts から生成する。
 */

import { GROUP_TITLES, PAGES, READING_ORDER, type GroupId, type PageMeta } from '../data/lessons';

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

function groupMarkup(group: GroupId, currentId: string): string {
  const items = PAGES.filter((page) => page.group === group)
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

export function renderNav(): void {
  const host = document.querySelector<HTMLElement>('[data-nav]');
  if (!host) return;

  const currentId = currentPageId();
  const groups: GroupId[] = ['guide', 'lessons', 'tasks'];
  host.innerHTML = groups.map((group) => groupMarkup(group, currentId)).join('\n');

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

export function renderPager(): void {
  const host = document.querySelector<HTMLElement>('[data-pager]');
  if (!host) return;

  const index = READING_ORDER.findIndex((page) => page.id === currentPageId());
  if (index < 0) return;

  const prev = READING_ORDER[index - 1];
  const next = READING_ORDER[index + 1];
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
