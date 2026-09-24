/**
 * 各ページ共通の初期化。すべてのHTMLがこのファイルだけを読み込む。
 */

import { renderNav, renderPager } from './components/nav';
import { enhanceCodeBlocks } from './components/codeBlock';
import { renderToc } from './components/toc';
import { setupChecklist } from './features/checklist';
import { setupAudience } from './features/audience';
import { type Audience } from './data/lessons';

const THEME_KEY = 'cpp-course:theme';

type Theme = 'light' | 'dark';

function storedTheme(): Theme | null {
  try {
    const value = window.localStorage.getItem(THEME_KEY);
    return value === 'light' || value === 'dark' ? value : null;
  } catch {
    return null;
  }
}

function applyTheme(theme: Theme | null): void {
  if (theme) document.documentElement.dataset.theme = theme;
  else delete document.documentElement.dataset.theme;
}

function setupTheme(): void {
  applyTheme(storedTheme());

  const button = document.querySelector<HTMLButtonElement>('.theme-toggle');
  button?.addEventListener('click', () => {
    const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
    const current = storedTheme() ?? (prefersDark ? 'dark' : 'light');
    const next: Theme = current === 'dark' ? 'light' : 'dark';

    applyTheme(next);
    try {
      window.localStorage.setItem(THEME_KEY, next);
    } catch {
      /* 保存できなくても表示は切り替える */
    }
  });
}

/** 表示対象者で中身が変わるもの。切り替えボタンからも同じ関数を呼ぶ */
function renderForAudience(audience: Audience): void {
  renderNav(audience);
  renderPager(audience);
  renderToc(audience);
}

function init(): void {
  setupTheme();
  renderForAudience(setupAudience(renderForAudience));
  enhanceCodeBlocks();
  setupChecklist();
}

if (document.readyState === 'loading') {
  document.addEventListener('DOMContentLoaded', init);
} else {
  init();
}
