import { readdirSync } from 'node:fs';
import { resolve, relative, join, sep } from 'node:path';
import { fileURLToPath } from 'node:url';
import { defineConfig, type Plugin } from 'vite';
import { SOLUTIONS } from './site/scripts/data/solutions';

const projectRoot = fileURLToPath(new URL('.', import.meta.url));
const siteRoot = resolve(projectRoot, 'site');

/**
 * 解答例は**公開・未公開を問わずすべてビルドする**。
 * 未公開の回は講師表示のときだけリンクが出るが、ファイル自体は配信されるので
 * **URLを知っていれば受講者でも読める**。それを了承した上での選択である
 * （2026-09-25）。本当に出したくない回が出てきたら、ここで rollup の入力から落とすこと。
 */

/** site/ 以下のHTMLをすべて探し、rollupの入力にする（複数ページビルド） */
function htmlEntries(dir: string, found: Record<string, string> = {}): Record<string, string> {
  for (const entry of readdirSync(dir, { withFileTypes: true })) {
    const full = join(dir, entry.name);

    if (entry.isDirectory()) {
      if (entry.name === 'public' || entry.name === 'node_modules') continue;
      htmlEntries(full, found);
      continue;
    }

    if (entry.isFile() && entry.name.endsWith('.html')) {
      const sitePath = relative(siteRoot, full).split(sep).join('/');

      // "index", "guide/policy", "lessons/00-intro" のようなキーにする
      found[sitePath.replace(/\.html$/, '')] = full;
    }
  }

  return found;
}

/**
 * 解答例のリンクをビルド時にHTMLへ埋め込むプラグイン。
 *
 * 以前はブラウザ側のJSで描画していたが、JSが動かない環境や
 * 古いキャッシュを掴んだ状態ではリンクが出ないという問題があった。
 * 静的な内容なので、HTMLに直接書き出すほうが確実で、
 * curl や表示ソースでそのまま検証できる。
 */
function solutionsHtml(): Plugin {
  const link = (base: string, path: string, title: string, teacherOnly: boolean): string => {
    const cls = teacherOnly ? 'solution-link solution-link-teacher' : 'solution-link';
    const label = teacherOnly ? '解答例（講師のみ）' : '解答例';

    return `<a class="${cls}" href="${base}${path}">
            <span class="solution-link-label">${label}</span>
            <span class="solution-link-title">${title}</span>
          </a>`;
  };

  const table = (base: string): string => {
    const rows = SOLUTIONS.map((s) => {
      // 未公開の回は両方の表記を書き出し、data-for でCSSが選ぶ。
      // ビルド時に静的に出すので、JS描画に戻してはいけないのは従来どおり。
      const cell = s.published
        ? `<a href="${base}${s.path}">${s.title}</a>`
        : `<a href="${base}${s.path}" data-for="teacher">${s.title}</a>`
          + `<span class="solution-pending" data-for="student">${s.title}</span>`;
      const status = s.published
        ? '<span class="badge badge-open">公開中</span>'
        : '<span class="badge badge-teacher" data-for="teacher">講師のみ</span>'
          + '<span class="badge badge-closed" data-for="student">未公開</span>';
      return `<tr><td>${s.label}</td><td>${cell}</td><td>${status}</td></tr>`;
    }).join('\n            ');

    const count = SOLUTIONS.filter((s) => s.published).length;

    return `<div class="table-wrap">
          <table>
            <thead><tr><th>回</th><th>演習</th><th>状態</th></tr></thead>
            <tbody>
            ${rows}
            </tbody>
          </table>
        </div>
        <p class="solution-count" data-for="student">公開中: ${count} / ${SOLUTIONS.length} 回</p>
        <p class="solution-count" data-for="teacher">受講者に公開中: ${count} / ${SOLUTIONS.length} 回（講師表示では全${SOLUTIONS.length}回を開ける）</p>`;
  };

  return {
    name: 'solutions-html',
    transformIndexHtml: {
      order: 'pre',
      handler(html) {
        const base = html.match(/data-base="([^"]*)"/)?.[1] ?? './';
        const pageId = html.match(/data-page="([^"]*)"/)?.[1] ?? '';

        if (html.includes('data-solution-index')) {
          html = html.replace('<div data-solution-index></div>', () => table(base));
        }

        // 未公開の回は、枠ごと data-for="teacher" にして受講者側には余白も残さない
        const solution = SOLUTIONS.find((s) => s.lessonId === pageId);
        html = html.replace('<div class="solution-slot" data-solution></div>', () => {
          if (!solution) return '';

          const anchor = link(base, solution.path, solution.title, !solution.published);
          return solution.published
            ? `<div class="solution-slot">${anchor}</div>`
            : `<div class="solution-slot" data-for="teacher">${anchor}</div>`;
        });

        return html;
      },
    },
  };
}

export default defineConfig({
  plugins: [solutionsHtml()],
  root: siteRoot,
  // プロジェクトページ（HR-tuat/Cpp_course）のため "/<リポジトリ名>/"。
  // リポジトリ名を変えたらここも合わせる。ユーザーサイト（<ユーザー名>.github.io）
  // に戻す場合のみ "/" にする。
  base: '/Cpp_course/',
  publicDir: resolve(siteRoot, 'public'),
  build: {
    outDir: resolve(projectRoot, 'dist'),
    emptyOutDir: true,
    rollupOptions: {
      input: htmlEntries(siteRoot),
    },
  },
  server: {
    open: '/index.html',
  },
});
