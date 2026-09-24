/**
 * ページ内目次。本文のh2 / h3から生成し、スクロール位置に追従させる。
 */

interface Heading {
  id: string;
  text: string;
  level: 2 | 3;
}

function collectHeadings(): Heading[] {
  const nodes = document.querySelectorAll<HTMLHeadingElement>('.prose h2[id], .prose h3[id]');

  return Array.from(nodes).map((node) => ({
    id: node.id,
    text: node.textContent ?? '',
    level: node.tagName === 'H3' ? 3 : 2,
  }));
}

export function renderToc(): void {
  const host = document.querySelector<HTMLElement>('[data-toc]');
  if (!host) return;

  const headings = collectHeadings();
  if (headings.length < 2) return;

  const items = headings
    .map((heading) => {
      const cls = heading.level === 3 ? ' class="toc-h3"' : '';
      return `<li${cls}><a href="#${heading.id}">${heading.text}</a></li>`;
    })
    .join('');

  host.innerHTML = `<p class="toc-title">このページの内容</p><ul>${items}</ul>`;

  observe(host, headings);
}

function observe(host: HTMLElement, headings: Heading[]): void {
  const links = new Map<string, HTMLAnchorElement>();
  host.querySelectorAll('a').forEach((link) => {
    links.set(decodeURIComponent(link.getAttribute('href')?.slice(1) ?? ''), link);
  });

  const visible = new Set<string>();

  const setActive = (id: string): void => {
    links.forEach((link, key) => link.classList.toggle('is-active', key === id));
  };

  const observer = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) visible.add(entry.target.id);
        else visible.delete(entry.target.id);
      });

      const first = headings.find((heading) => visible.has(heading.id));
      if (first) setActive(first.id);
    },
    { rootMargin: '-5rem 0px -70% 0px', threshold: 0 },
  );

  headings.forEach((heading) => {
    const element = document.getElementById(heading.id);
    if (element) observer.observe(element);
  });
}
