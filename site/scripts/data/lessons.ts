/**
 * サイト全体のページメタデータ。
 * サイドバー・前へ/次へは、このファイルだけを見て生成される。
 * ページを追加したときは、ここに1行足せばナビゲーションに反映される。
 */

export type GroupId = 'guide' | 'lessons' | 'tasks';

export interface PageMeta {
  /** 各HTMLの <body data-page="..."> と一致させる */
  id: string;
  /** site/ からの相対パス */
  path: string;
  /** サイドバー左側の短いラベル（「第3回」など） */
  label: string;
  /** ページタイトル */
  title: string;
  group: GroupId;
}

export const GROUP_TITLES: Record<GroupId, string> = {
  guide: 'はじめに',
  lessons: '各回の教材',
  tasks: '課題と確認',
};

export const PAGES: PageMeta[] = [
  { id: 'home', path: 'index.html', label: '—', title: '講座概要', group: 'guide' },
  { id: 'guide-policy', path: 'guide/policy.html', label: '1章', title: '講座の基本方針', group: 'guide' },
  { id: 'guide-environment', path: 'guide/environment.html', label: '2章', title: '開発環境', group: 'guide' },
  { id: 'guide-schedule', path: 'guide/schedule.html', label: '20章', title: '12週間の授業計画', group: 'guide' },
  { id: 'guide-teaching-notes', path: 'guide/teaching-notes.html', label: '23章', title: '教える際の重要ポイント', group: 'guide' },

  { id: 'lesson-00', path: 'lessons/00-intro.html', label: '第0回', title: 'プログラミングとマイコン', group: 'lessons' },
  { id: 'lesson-01', path: 'lessons/01-variables.html', label: '第1回', title: '変数・型・演算子', group: 'lessons' },
  { id: 'lesson-02', path: 'lessons/02-control.html', label: '第2回', title: '条件分岐・繰り返し', group: 'lessons' },
  { id: 'lesson-03', path: 'lessons/03-functions.html', label: '第3回', title: '関数', group: 'lessons' },
  { id: 'lesson-04', path: 'lessons/04-pointers.html', label: '第4回', title: '配列・メモリ・ポインタ・参照', group: 'lessons' },
  { id: 'lesson-05', path: 'lessons/05-cpp-basics.html', label: '第5回', title: 'C++基礎', group: 'lessons' },
  { id: 'lesson-06', path: 'lessons/06-classes.html', label: '第6回', title: 'クラスとオブジェクト', group: 'lessons' },
  { id: 'lesson-07', path: 'lessons/07-headers.html', label: '第7回', title: 'ヘッダとcpp', group: 'lessons' },
  { id: 'lesson-08', path: 'lessons/08-encapsulation.html', label: '第8回', title: 'カプセル化', group: 'lessons' },
  { id: 'lesson-09', path: 'lessons/09-enum.html', label: '第9回', title: '列挙型と状態管理', group: 'lessons' },
  { id: 'lesson-10', path: 'lessons/10-inheritance.html', label: '第10回', title: '継承', group: 'lessons' },
  { id: 'lesson-11', path: 'lessons/11-virtual.html', label: '第11回', title: 'virtual / override', group: 'lessons' },
  { id: 'lesson-12', path: 'lessons/12-abstract.html', label: '第12回', title: '純粋仮想関数と抽象クラス', group: 'lessons' },
  { id: 'lesson-13', path: 'lessons/13-polymorphism.html', label: '第13回', title: 'ポリモーフィズム', group: 'lessons' },
  { id: 'lesson-14', path: 'lessons/14-design.html', label: '第14回', title: 'クラス設計', group: 'lessons' },
  { id: 'lesson-15', path: 'lessons/15-mcu-design.html', label: '第15回', title: 'マイコン向け設計演習', group: 'lessons' },

  { id: 'exercises', path: 'exercises/index.html', label: '22章', title: '演習問題の段階', group: 'tasks' },
  { id: 'final-project', path: 'final-project/index.html', label: '19章', title: '最終課題', group: 'tasks' },
  { id: 'checklist', path: 'checklist.html', label: '24章', title: '到達度チェック', group: 'tasks' },
  { id: 'advanced', path: 'advanced.html', label: '26章', title: '発展内容', group: 'tasks' },
];

/** 前へ / 次へ はPAGESの並び順をそのまま使う */
export const READING_ORDER: PageMeta[] = PAGES;

export function findPage(id: string): PageMeta | undefined {
  return PAGES.find((page) => page.id === id);
}

export function pagesInGroup(group: GroupId): PageMeta[] {
  return PAGES.filter((page) => page.group === group);
}
