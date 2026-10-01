/**
 * 解答例の公開管理（段階公開）。
 *
 * published は「受講者にリンクを見せるか」の切り替えである。
 * **配信するかどうかではない**：未公開の回も dist に出力されるため、
 * URLを知っていれば受講者でも読める。講師が全回を見られることを優先して
 * 了承した選択である（2026-09-25。詳細は CLAUDE.md「解答例の公開」）。
 *
 *   published: true   受講者にも講師にもリンクが出る
 *   published: false  受講者には「未公開」表示だけ。講師には「講師のみ」リンクが出る
 *
 * ## 授業後に公開する手順
 *
 *   1. 該当する回の published を true にする
 *   2. コミットして main に push する
 *   3. GitHub Actions がビルドし、数分で公開される
 *
 * 本当に配信したくない回が出てきたら、vite.config.ts の htmlEntries() で
 * rollup の入力から落とすしかない。
 */

export interface SolutionMeta {
  /** 対応する講義ページのid（lessons.ts の PAGES と一致させる） */
  lessonId: string;
  /** site/ からの相対パス */
  path: string;
  label: string;
  title: string;
  /** false の回はビルドされず公開もされない */
  published: boolean;
}

export const SOLUTIONS: SolutionMeta[] = [
  { lessonId: 'lesson-00', path: 'solutions/00-intro.html', label: '第0回', title: 'LEDを点滅させる', published: false },
  { lessonId: 'lesson-01', path: 'solutions/01-variables.html', label: '第1回', title: '温度が30度以上ならLEDを点灯する', published: false },
  { lessonId: 'lesson-02', path: 'solutions/02-control.html', label: '第2回', title: '繰り返しと条件分岐', published: false },
  { lessonId: 'lesson-03', path: 'solutions/03-functions.html', label: '第3回', title: 'モータとセンサの関数', published: false },
  { lessonId: 'lesson-04', path: 'solutions/04-pointers.html', label: '第4回', title: '配列・ポインタ・参照', published: false },
  { lessonId: 'lesson-05', path: 'solutions/05-cpp-basics.html', label: '第5回', title: 'const・名前空間・オーバーロード', published: false },
  { lessonId: 'lesson-06', path: 'solutions/06-classes.html', label: '第6回', title: 'LEDクラスを作る', published: false },
  { lessonId: 'lesson-07', path: 'solutions/07-headers.html', label: '第7回', title: 'LED・Motor・Buttonを分割する', published: false },
  { lessonId: 'lesson-08', path: 'solutions/08-encapsulation.html', label: '第8回', title: 'カプセル化する', published: false },
  { lessonId: 'lesson-09', path: 'solutions/09-enum.html', label: '第9回', title: 'RobotStateで状態管理する', published: false },
  { lessonId: 'lesson-10', path: 'solutions/10-inheritance.html', label: '第10回', title: 'Deviceクラス構造を考える', published: false },
  { lessonId: 'lesson-11', path: 'solutions/11-virtual.html', label: '第11回', title: 'IMUとGPSをvirtualで扱う', published: false },
  { lessonId: 'lesson-12', path: 'solutions/12-abstract.html', label: '第12回', title: '純粋仮想関数とToFの追加', published: false },
  { lessonId: 'lesson-13', path: 'solutions/13-polymorphism.html', label: '第13回', title: 'センサを配列でまとめて更新する', published: false },
  { lessonId: 'lesson-14', path: 'solutions/14-design.html', label: '第14回', title: '責務を割り当てる', published: false },
  { lessonId: 'lesson-15', path: 'solutions/15-mcu-design.html', label: '第15回', title: 'マイコン向け設計をまとめる', published: false },
  { lessonId: 'lesson-16', path: 'solutions/16-stl-vector.html', label: '第16回', title: 'センサをstd::vectorでまとめる', published: false },
  { lessonId: 'lesson-17', path: 'solutions/17-smart-pointer.html', label: '第17回', title: 'センサの所有をunique_ptrに任せる', published: false },
  { lessonId: 'lesson-18', path: 'solutions/18-relations.html', label: '第18回', title: 'RobotとControllerの相互参照を解く', published: false },
];

export function publishedSolutions(): SolutionMeta[] {
  return SOLUTIONS.filter((solution) => solution.published);
}

export function solutionForLesson(lessonId: string): SolutionMeta | undefined {
  return SOLUTIONS.find((solution) => solution.lessonId === lessonId && solution.published);
}
