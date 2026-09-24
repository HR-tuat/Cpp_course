/**
 * 到達度チェックの保存（localStorage）と進捗表示。
 * 保存先はブラウザごと。端末をまたいでは共有されない。
 */

const STORAGE_KEY = 'cpp-course:checklist:v1';

type CheckState = Record<string, boolean>;

function load(): CheckState {
  try {
    const raw = window.localStorage.getItem(STORAGE_KEY);
    if (!raw) return {};

    const parsed: unknown = JSON.parse(raw);
    return typeof parsed === 'object' && parsed !== null ? (parsed as CheckState) : {};
  } catch {
    // プライベートモードなどで localStorage が使えない場合は保存なしで動かす
    return {};
  }
}

function save(state: CheckState): void {
  try {
    window.localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
  } catch {
    /* 保存できなくてもチェック自体は動作させる */
  }
}

export function setupChecklist(): void {
  const boxes = Array.from(
    document.querySelectorAll<HTMLInputElement>('input[type="checkbox"][data-check]'),
  );
  if (boxes.length === 0) return;

  const state = load();

  const updateProgress = (): void => {
    const done = boxes.filter((box) => box.checked).length;
    const ratio = boxes.length === 0 ? 0 : (done / boxes.length) * 100;

    const text = document.querySelector<HTMLElement>('[data-progress-text]');
    if (text) text.textContent = `${done} / ${boxes.length} 項目`;

    const bar = document.querySelector<HTMLElement>('[data-progress-bar]');
    if (bar) bar.style.width = `${ratio}%`;
  };

  boxes.forEach((box) => {
    const key = box.dataset.check ?? '';
    box.checked = state[key] === true;

    box.addEventListener('change', () => {
      const current = load();
      current[key] = box.checked;
      save(current);
      updateProgress();
    });
  });

  const reset = document.querySelector<HTMLButtonElement>('[data-check-reset]');
  reset?.addEventListener('click', () => {
    if (!window.confirm('チェックをすべて消します。よろしいですか？')) return;

    boxes.forEach((box) => {
      box.checked = false;
    });
    save({});
    updateProgress();
  });

  updateProgress();
}
