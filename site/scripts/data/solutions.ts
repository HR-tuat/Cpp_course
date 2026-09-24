/**
 * 解答例の公開管理（段階公開）。
 *
 * published を false にしている回は、ビルド対象から除外されるため
 * dist に出力されず、URLを直接叩いても 404 になる。
 * 「JSで隠す」のではなく「そもそも配信しない」ことで非公開を保証している。
 *
 * ## 授業後に公開する手順
 *
 *   1. 該当する回の published を true にする
 *   2. コミットして main に push する
 *   3. GitHub Actions がビルドし、数分で公開される
 *
 * 非公開に戻したいときは false に戻して push すれば、次のデプロイで消える。
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
];

export function publishedSolutions(): SolutionMeta[] {
  return SOLUTIONS.filter((solution) => solution.published);
}

export function solutionForLesson(lessonId: string): SolutionMeta | undefined {
  return SOLUTIONS.find((solution) => solution.lessonId === lessonId && solution.published);
}
