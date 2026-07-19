"""find_cast_parks.py -- parked functions whose C shows the POINTER-CAST symptom.

From the ov029 crack (codegen-cracks.md, "Si estas casteando punteros, la C esta mal"):
a `(char *)table + n`, a `(T *)(base + i*K)`, or a hand-computed `i << 4` byte
offset is a sign the C is transcribing the ROM's addressing instead of
reconstructing the source.  That closed func_ov029_020b2ee0 at the first attempt
after months parked behind ~19 spellings, 12 compiler builds and 10 flag sets.

It is a re-test vein, not one case.  This ranks the parked files by how strongly
they show the symptom.

    python tools/find_cast_parks.py [n]
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CAST  = re.compile(r'\(\s*(?:char|unsigned char|u8|s8)\s*\*\s*\)')
TCAST = re.compile(r'\(\s*(?:struct\s+)?\w+\s*\*\s*\)\s*\(\s*\(\s*char')
SHIFT = re.compile(r'\w+\s*(?:<<=\s*[2-6]\b|=\s*\w+\s*<<\s*[2-6]\b)')


def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', ' ', t, flags=re.S)
    return re.sub(r'//[^\n]*', ' ', t)


def main():
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 20
    rows, total = [], 0
    for dp, dn, fn in os.walk(ROOT):
        if 'nonmatching' not in dp.replace('\\', '/').split('/'):
            continue
        for f in fn:
            if not f.endswith('.c'):
                continue
            total += 1
            p = os.path.join(dp, f)
            try:
                body = strip_comments(open(p, errors='replace').read())
            except OSError:
                continue
            c, t, s = len(CAST.findall(body)), len(TCAST.findall(body)), len(SHIFT.findall(body))
            score = c + 3 * t + 2 * s
            if score:
                rows.append((score, c, t, s, os.path.relpath(p, ROOT)))
    rows.sort(reverse=True)
    print('parked .c scanned: %d' % total)
    print('showing the cast / manual-offset symptom: %d (%.0f%%)'
          % (len(rows), 100.0 * len(rows) / max(total, 1)))
    print()
    print('%-6s %-6s %-6s %-6s %s' % ('score', 'char*', '(T*)(', 'shift', 'file'))
    for sc, c, t, s, p in rows[:limit]:
        print('%-6d %-6d %-6d %-6d %s' % (sc, c, t, s, p.replace(os.sep, '/')))


if __name__ == '__main__':
    main()
