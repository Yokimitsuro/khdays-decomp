"""poolslots.py -- every literal-pool slot that holds the address of a given global.

Typing a global in Ghidra means typing the POOL SLOT as `T *` (see SKILL.md): the
decompiler binds each consumer's local to the pool datum, so the struct fields
propagate through the whole function.  Doing that by hand is one address at a
time; this enumerates them all.

The reloc table already has it: a reloc at offset N of function F pointing at
`data_X` means the word at F+N is a pool slot holding &data_X.  So the slots for
a symbol are just {func_addr + reloc_offset}.

    python tools/poolslots.py data_0204c228
    python tools/poolslots.py data_0204c228 --jython GameSession   # ready to run
"""
import ast, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def slots_for(symbol):
    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    out = []
    for name, e in idx.items():
        m = re.match(r'^func_(?:(ov\d{3})_)?0([0-9a-f]{7})$', name)
        if not m:
            continue
        space, addr = m.group(1) or '', int(m.group(2), 16)
        r = e['relocs']
        if isinstance(r, str):
            r = ast.literal_eval(r)
        for off, s in r:
            if s == symbol:
                out.append((space, addr + off, name))
    return sorted(set(out))


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    sym = sys.argv[1]
    rows = slots_for(sym)
    print('%s: %d pool slot(s) across %d function(s)'
          % (sym, len(rows), len(set(r[2] for r in rows))))
    if '--jython' in sys.argv:
        typ = sys.argv[sys.argv.index('--jython') + 1]
        print()
        print('SLOTS=[')
        for space, a, fn in rows:
            print('  ("%s","%08x"),   # %s' % ('arm9_' + space if space else '', a, fn))
        print(']')
        print('TYPE="%s *"' % typ)
    else:
        for space, a, fn in rows[:40]:
            print('  %-12s %08x   %s' % (space or 'main', a, fn))
        if len(rows) > 40:
            print('  ... and %d more' % (len(rows) - 40))
