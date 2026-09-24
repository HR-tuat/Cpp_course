import { readdirSync } from 'node:fs';
import { resolve, relative, join, sep } from 'node:path';
import { fileURLToPath } from 'node:url';
import { defineConfig } from 'vite';

const projectRoot = fileURLToPath(new URL('.', import.meta.url));
const siteRoot = resolve(projectRoot, 'site');

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
      // "index", "guide/policy", "lessons/00-intro" のようなキーにする
      const name = relative(siteRoot, full).replace(/\.html$/, '').split(sep).join('/');
      found[name] = full;
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
