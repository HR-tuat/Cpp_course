/**
 * コードブロックのシンタックスハイライトとコピーボタン。
 * 外部ライブラリを使わず、C++の教材に必要な範囲だけを色分けする。
 */

const KEYWORDS = [
  'alignas', 'alignof', 'break', 'case', 'catch', 'class', 'const', 'constexpr',
  'continue', 'default', 'delete', 'do', 'else', 'enum', 'explicit', 'export',
  'extern', 'false', 'for', 'friend', 'goto', 'if', 'inline', 'namespace', 'new',
  'noexcept', 'nullptr', 'operator', 'override', 'private', 'protected', 'public',
  'return', 'sizeof', 'static', 'struct', 'switch', 'template', 'this', 'throw',
  'true', 'try', 'typedef', 'typename', 'union', 'using', 'virtual', 'volatile',
  'while',
];

const TYPES = [
  'auto', 'bool', 'char', 'double', 'float', 'int', 'long', 'short', 'signed',
  'unsigned', 'void', 'size_t', 'int8_t', 'uint8_t', 'int16_t', 'uint16_t',
  'int32_t', 'uint32_t', 'int64_t', 'uint64_t',
];

interface Rule {
  cls: string;
  re: RegExp;
}

const RULES: Rule[] = [
  { cls: 'tok-comment', re: /\/\/[^\n]*|\/\*[\s\S]*?\*\// },
  { cls: 'tok-string', re: /"(?:[^"\\\n]|\\.)*"|'(?:[^'\\\n]|\\.)*'/ },
  { cls: 'tok-preproc', re: /^[ \t]*#[a-z]+/m },
  { cls: 'tok-keyword', re: new RegExp(`\\b(?:${KEYWORDS.join('|')})\\b`) },
  { cls: 'tok-type', re: new RegExp(`\\b(?:${TYPES.join('|')})\\b`) },
  { cls: 'tok-number', re: /\b\d+(?:\.\d+)?[fFuUlL]*\b/ },
  { cls: 'tok-func', re: /\b[A-Za-z_]\w*(?=\s*\()/ },
];

/** 全ルールをまとめた1本の正規表現（先に書いたルールが優先される） */
const SCANNER = new RegExp(RULES.map((rule) => `(${rule.re.source})`).join('|'), 'gm');

function escapeHtml(text: string): string {
  return text
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;');
}

export function highlightCpp(source: string): string {
  let out = '';
  let last = 0;

  SCANNER.lastIndex = 0;
  for (let match = SCANNER.exec(source); match !== null; match = SCANNER.exec(source)) {
    // どのキャプチャグループに当たったかでトークン種別が決まる
    const groupIndex = match.findIndex((value, index) => index > 0 && value !== undefined);
    if (groupIndex <= 0) continue;

    out += escapeHtml(source.slice(last, match.index));
    out += `<span class="${RULES[groupIndex - 1].cls}">${escapeHtml(match[0])}</span>`;
    last = match.index + match[0].length;
  }

  return out + escapeHtml(source.slice(last));
}

function addCopyButton(figure: HTMLElement, code: HTMLElement): void {
  const button = document.createElement('button');
  button.type = 'button';
  button.className = 'copy-btn';
  button.textContent = 'コピー';

  button.addEventListener('click', () => {
    void navigator.clipboard.writeText(code.textContent ?? '').then(
      () => {
        button.textContent = 'コピーしました';
        button.classList.add('is-done');
        window.setTimeout(() => {
          button.textContent = 'コピー';
          button.classList.remove('is-done');
        }, 1600);
      },
      () => {
        button.textContent = 'コピーできません';
      },
    );
  });

  figure.appendChild(button);
}

export function enhanceCodeBlocks(): void {
  const blocks = document.querySelectorAll<HTMLElement>('figure.code pre > code');

  blocks.forEach((code) => {
    const source = code.textContent ?? '';

    if (code.classList.contains('language-cpp')) {
      code.innerHTML = highlightCpp(source);
    }

    const figure = code.closest('figure.code');
    if (figure instanceof HTMLElement && navigator.clipboard) {
      addCopyButton(figure, code);
    }
  });
}
