import { readdirSync } from 'node:fs';
import { resolve, relative, join, sep } from 'node:path';
import { fileURLToPath } from 'node:url';
import { defineConfig, type Plugin } from 'vite';
import { SOLUTIONS } from './site/scripts/data/solutions';

const projectRoot = fileURLToPath(new URL('.', import.meta.url));
const siteRoot = resolve(projectRoot, 'site');

/**
 * 未公開の解答例（published: false）はビルド対象から外す。
 * dist に出力されないため、URLを直接叩いても 404 になる。
 * 「JSで隠す」だけでは静的ホストでは見えてしまうので、ここで落とすことが重要。
 */
const unpublished = new Set(
  SOLUTIONS.filter((solution) => !solution.published).map((solution) => solution.path),
);

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
      if (unpublished.has(sitePath)) continue;

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
  const link = (base: string, path: string, title: string): string =>
    `<a class="solution-link" href="${base}${path}">
            <span class="solution-link-label">解答例</span>
            <span class="solution-link-title">${title}</span>
          </a>`;

  const table = (base: string): string => {
    const rows = SOLUTIONS.map((s) => {
      const cell = s.published
        ? `<a href="${base}${s.path}">${s.title}</a>`
        : `<span class="solution-pending">${s.title}</span>`;
      const status = s.published
        ? '<span class="badge badge-open">公開中</span>'
        : '<span class="badge badge-closed">未公開</span>';
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
        <p class="solution-count">公開中: ${count} / ${SOLUTIONS.length} 回</p>`;
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

        const solution = SOLUTIONS.find((s) => s.lessonId === pageId && s.published);
        html = html.replace(
          '<div class="solution-slot" data-solution></div>',
          () => (solution ? `<div class="solution-slot">${link(base, solution.path, solution.title)}</div>` : ''),
        );

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
