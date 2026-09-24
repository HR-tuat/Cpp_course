/**
 * 解答例へのリンクの差し込みと、解答例一覧の描画。
 *
 * 未公開の回はそもそもビルドされていない（vite.config.ts で除外）。
 * ここでリンクを出さないのは、404へのリンクを見せないための表示上の配慮であって、
 * 非公開そのものを保証しているわけではない。
 */

import { SOLUTIONS, solutionForLesson } from '../data/solutions';
import { currentPageId, siteBase } from './nav';

/** 講義ページの演習ボックスに、公開済みなら解答例へのリンクを差し込む */
export function renderSolutionLink(): void {
  const slot = document.querySelector<HTMLElement>('[data-solution]');
  if (!slot) return;

  const solution = solutionForLesson(currentPageId());
  if (!solution) return;

  slot.innerHTML = `<a class="solution-link" href="${siteBase()}${solution.path}">
  <span class="solution-link-label">解答例</span>
  <span class="solution-link-title">${solution.title}</span>
</a>`;
}

/** 解答例一覧ページの表を描画する */
export function renderSolutionIndex(): void {
  const host = document.querySelector<HTMLElement>('[data-solution-index]');
  if (!host) return;

  const base = siteBase();
  const rows = SOLUTIONS.map((solution) => {
    const cell = solution.published
      ? `<a href="${base}${solution.path}">${solution.title}</a>`
      : `<span class="solution-pending">${solution.title}</span>`;

    const status = solution.published
      ? '<span class="badge badge-open">公開中</span>'
      : '<span class="badge badge-closed">未公開</span>';

    return `<tr><td>${solution.label}</td><td>${cell}</td><td>${status}</td></tr>`;
  }).join('');

  const count = SOLUTIONS.filter((solution) => solution.published).length;

  host.innerHTML = `<div class="table-wrap">
  <table>
    <thead><tr><th>回</th><th>演習</th><th>状態</th></tr></thead>
    <tbody>${rows}</tbody>
  </table>
</div>
<p class="solution-count">公開中: ${count} / ${SOLUTIONS.length} 回</p>`;
}
