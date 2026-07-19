"""fieldid.py -- identify context-struct FIELDS by what their accessors feed into.

The ov008/ov025 naming debt is dominated by accessors on one shared context
struct: `return *(int *)(ctx + 0x959c);`, `*(int *)(ctx + 0x9678) = v;` ...
Naming those one by one is hopeless -- `SetField9678` says nothing.

But a field's TYPE is revealed by its consumers.  If an accessor's result is
handed to `Anim_SetFrameWrapped` or `Srt_SetTranslation` or `List_First`, the
field IS an animation state / a transform / a list.  So: find the accessors,
then look at what the call sites do with the value.

This only works because the hubs were named first -- it is the payoff of the
"clear the debt from the named frontier outward" plan in naming-hubs.md.

    python tools/fieldid.py ov008
    python tools/fieldid.py ov008 --offset 0x959c
"""
import os, re, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PLACEHOLDER = re.compile(r'^(FUN_|func_|DAT_|data_|sub_|thunk_)', re.I)
JUNK_SDK = re.compile(r'_0x[0-9a-fA-F]{6,8}$')

def real_name(sym):
    return not PLACEHOLDER.match(sym) and not JUNK_SDK.search(sym)


def strip_comments(txt):
    """★ Do this BEFORE any regex over source.  The first version of this tool
    skipped it and reported four 'consumers' called `sprite`, `page`, `rebuild`
    and `scrolls` -- all of them ordinary English words inside /* */ comments,
    followed by a paren.  Four plausible-looking hits and not one was a call."""
    txt = re.sub(r'/\*.*?\*/', ' ', txt, flags=re.S)
    return re.sub(r'//[^\n]*', ' ', txt)


def unit_files(unit):
    out = []
    root = os.path.join(ROOT, 'src', 'overlays', unit) if unit.startswith('ov') else os.path.join(ROOT, 'src')
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [d for d in dirnames if d not in ('asm_stubs', 'nonmatching')]
        for fn in filenames:
            if fn.endswith('.c'):
                out.append(os.path.join(dirpath, fn))
    return out


ACC = re.compile(
    r'\b(func_\w+)\s*\([^)]*\)\s*\{\s*(?:return\s+)?'
    r'[^;{}]*?\+\s*(0x[0-9a-fA-F]+)\s*\)?\s*(?:=\s*[^;]+)?;', re.S)


def find_accessors(files):
    """symbol -> (offset, kind) for the trivial ctx+N accessors."""
    acc = {}
    for p in files:
        try:
            txt = open(p, errors='replace').read()
        except OSError:
            continue
        for m in re.finditer(r'^[A-Za-z_][\w \*]*\b(func_\w+)\s*\([^;{]*\)\s*\{(.*?)^\}',
                             txt, re.S | re.M):
            sym, body = m.group(1), m.group(2)
            if len(body) > 220:
                continue
            off = re.search(r'\+\s*(0x[0-9a-fA-F]{2,5})\b', body)
            if not off:
                continue
            kind = 'set' if re.search(r'\)\s*=\s*\w', body) else 'get'
            acc[sym] = (int(off.group(1), 16), kind)
    return acc


KEYWORD = ('if', 'while', 'return', 'for', 'switch', 'sizeof', 'do', 'else')

def consumers(files, syms):
    """symbol -> Counter of the named functions its result is passed to.

    ★ Handles BOTH forms, and the second one is the common one:
        direct   Srt_SetTranslation(accessor(), v);
        via-var  int obj = accessor();  ...  Srt_SetTranslation(obj, v);
    Matching only the direct form found ZERO consumers across 161 accessors --
    a clean example of a negative that was purely an artifact of the search.
    The real code almost always parks the result in a local first.
    """
    out = collections.defaultdict(collections.Counter)
    direct = {s: re.compile(r'([A-Za-z_]\w*)\s*\([^()]*\b' + re.escape(s) + r'\s*\(') for s in syms}
    assign = re.compile(r'\b(\w+)\s*=\s*([A-Za-z_]\w*)\s*\(\s*\)')
    for p in files:
        try:
            txt = strip_comments(open(p, errors='replace').read())
        except OSError:
            continue
        for s, rx in direct.items():
            for m in rx.finditer(txt):
                if m.group(1) not in KEYWORD:
                    out[s][m.group(1)] += 1
        # via-variable: map local -> accessor, then find calls taking that local
        var2acc = {}
        for m in assign.finditer(txt):
            if m.group(2) in syms:
                var2acc[m.group(1)] = m.group(2)
        for var, s in var2acc.items():
            rx = re.compile(r'([A-Za-z_]\w*)\s*\([^()]*\b' + re.escape(var) + r'\b')
            for m in rx.finditer(txt):
                callee = m.group(1)
                if callee in KEYWORD or callee == s:
                    continue
                out[s][callee] += 1
    return out


if __name__ == '__main__':
    unit = sys.argv[1] if len(sys.argv) > 1 else 'ov008'
    files = unit_files(unit)
    # consumers may live anywhere, not just in the owning unit
    allfiles = files + unit_files('') if unit.startswith('ov') else files
    acc = find_accessors(files)
    print('%s: %d trivial offset accessors' % (unit, len(acc)))
    byoff = collections.defaultdict(list)
    for s, (off, kind) in acc.items():
        byoff[off].append((kind, s))
    cons = consumers(allfiles, set(acc))
    named_hits = 0
    for off in sorted(byoff):
        entries = byoff[off]
        lines = []
        for kind, s in sorted(entries):
            c = cons.get(s, collections.Counter())
            named = [(k, v) for k, v in c.most_common() if real_name(k)]
            if named:
                named_hits += 1
                lines.append('    %-28s %s -> %s' % (s, kind,
                             ', '.join('%s(x%d)' % (k, v) for k, v in named[:3])))
        if lines:
            print('  +0x%04x  (%d accessors)' % (off, len(entries)))
            for l in lines:
                print(l)
    print('\naccessors whose result reaches a NAMED function: %d' % named_hits)
