"""audit_structs.py -- measure the STRUCT debt, the way audit_unnamed.py measures names.

The project reached 13k matched functions with zero Ghidra data types while the
C tree accumulated thousands of per-file ad-hoc declarations.  A struct debt you
cannot count is a struct debt nobody clears -- that is exactly what happened to
the naming debt until audit_unnamed.py existed.

It splits the debt the way the WORK splits, which is the useful part:

  IDENTICAL   the same declaration text copy-pasted into N files.  One Ghidra
              type each, covering every one of those files.  Cheap, high impact.
  GENERIC     `struct Obj/A/B/S/C/Sub/Inner` -- the SAME object given a different
              shape and name per file.  These need real per-object analysis, and
              they are the ones that actively mislead, because each looks
              authoritative.
  ONE-OFF     declared in a single file.  Usually a genuine local shape; lowest
              priority.

    python tools/audit_structs.py            # the ranking
    python tools/audit_structs.py --name hw60   # every spelling of one name
"""
import os, re, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GENERIC = {'Obj', 'A', 'B', 'C', 'S', 'T', 'Sub', 'Inner', 'E', 'X', 'Elem',
           'Entry', 'Node', 'Foo', 'State', 'Ctx', 'Data', 'Item', 'Info'}

DECL = re.compile(r'\bstruct\s+([A-Za-z_]\w*)\s*\{([^}]*)\}', re.S)


def strip_comments(txt):
    txt = re.sub(r'/\*.*?\*/', ' ', txt, flags=re.S)
    return re.sub(r'//[^\n]*', ' ', txt)


def norm(body):
    """Whitespace-insensitive body, so formatting differences do not split a group."""
    return re.sub(r'\s+', ' ', body).strip()


def scan():
    """(name, normalised body) -> set of files."""
    seen = collections.defaultdict(set)
    for base in ('src', 'libs'):
        root = os.path.join(ROOT, base)
        for dirpath, dirnames, filenames in os.walk(root):
            dirnames[:] = [d for d in dirnames if d != 'asm_stubs']
            for fn in filenames:
                if not fn.endswith('.c'):
                    continue
                p = os.path.join(dirpath, fn)
                try:
                    txt = strip_comments(open(p, errors='replace').read())
                except OSError:
                    continue
                for m in DECL.finditer(txt):
                    seen[(m.group(1), norm(m.group(2)))].add(p)
    return seen


if __name__ == '__main__':
    seen = scan()
    if '--name' in sys.argv:
        want = sys.argv[sys.argv.index('--name') + 1]
        rows = [(len(f), n, b) for (n, b), f in seen.items() if n == want]
        rows.sort(reverse=True)
        print('%s: %d distinct spellings across %d files'
              % (want, len(rows), sum(r[0] for r in rows)))
        for cnt, n, b in rows:
            print('  x%-4d struct %s { %s }' % (cnt, n, b[:110]))
        sys.exit()

    by_name = collections.defaultdict(list)
    for (n, b), files in seen.items():
        by_name[n].append((len(files), b))

    identical, generic, oneoff = [], [], []
    for n, spellings in by_name.items():
        total = sum(c for c, _ in spellings)
        if n in GENERIC:
            generic.append((total, len(spellings), n))
        elif len(spellings) == 1 and total == 1:
            oneoff.append((total, 1, n))
        else:
            identical.append((total, len(spellings), n))

    tot_decls = sum(len(f) for f in seen.values())
    print('ad-hoc struct declarations in the C tree: %d' % tot_decls)
    print('distinct (name, body) pairs:              %d' % len(seen))
    print('distinct names:                           %d' % len(by_name))
    print()

    def dump(title, rows, note):
        rows.sort(reverse=True)
        print('%s -- %d names, %d declarations' % (title, len(rows), sum(r[0] for r in rows)))
        print('   %s' % note)
        for total, spell, n in rows[:15]:
            flag = '  <-- %d DIFFERENT shapes' % spell if spell > 1 else ''
            print('   %-22s %5d files%s' % (n, total, flag))
        print()

    dump('IDENTICAL / near', identical,
         'one Ghidra type each covers every file listed; check spellings > 1 first')
    dump('GENERIC (same object, different shape per file)', generic,
         'these MISLEAD -- each looks authoritative; needs per-object analysis')
    print('ONE-OFF: %d names in a single file each (lowest priority)' % len(oneoff))
