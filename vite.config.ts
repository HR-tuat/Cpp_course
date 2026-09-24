import { readdirSync } from 'node:fs';
import { resolve, relative, join, sep } from 'node:path';
import { fileURLToPath } from 'node:url';
import { defineConfig } from 'vite';
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

export default defineConfig({
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
