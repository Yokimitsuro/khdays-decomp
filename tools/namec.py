"""namec.py -- derive candidate Ghidra names for byte-exact functions from their own C.

The naming debt (tools/audit_unnamed.py) is ~5.6k functions that already have
byte-exact C in the tree.  That C is evidence: a body that does nothing but
`PushCommand_impl(0xa, a, b, c, 0)` IS a command-0xa wrapper, and saying so is
grounded, not a guess.

Discipline (the whole point of this file): only emit a name that is PROVABLY TRUE
from the body.  Shallow-but-true ("PushCommandCmd0A") beats FUN_.  Speculative
is worse than FUN_, because a name that lies survives and misleads.

    python tools/namec.py --profile          # how the debt classifies
    python tools/namec.py --show CLASS [n]   # sample bodies of one class
    python tools/namec.py --plan CLASS       # emit the rename plan
"""
import json, os, re, sys, subprocess, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ---------------------------------------------------------------- corpus

def unnamed_set():
    """The audit owns the 'this is not a name' predicate; do not re-implement it."""
    out = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'audit_unnamed.py'), '--list'],
                         capture_output=True, text=True, cwd=ROOT).stdout
    names = {}
    for ln in out.splitlines():
        p = ln.split()
        if len(p) == 2 and p[0].startswith(('func_', 'data_')) is False and not p[0][0].isdigit():
            pass
        if len(p) == 2 and re.match(r'^[A-Za-z_]\w*$', p[0]) and re.match(r'^[A-Za-z_]\w*$', p[1]):
            if not ln.startswith(('   ov', '   main', '   itcm', '   libs')) or p[0].startswith('func_'):
                names[p[0]] = p[1]
    return names


def c_file_map():
    """symbol -> path of the real (non-stub, non-parked) .c that defines it."""
    m = {}
    for base in ('src', 'libs'):
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, base)):
            dirnames[:] = [d for d in dirnames if d not in ('asm_stubs', 'nonmatching')]
            for fn in filenames:
                if fn.endswith('.c'):
                    m.setdefault(fn[:-2], os.path.join(dirpath, fn))
    return m


def body_of(path, sym):
    """Extract just the definition of `sym` from its file (files may hold several)."""
    try:
        txt = open(path, 'r', errors='replace').read()
    except OSError:
        return None
    m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(sym) + r'\s*\([^;{]*\)\s*\{', txt, re.M)
    if not m:
        return None
    i = txt.index('{', m.start())
    depth, j = 0, i
    while j < len(txt):
        if txt[j] == '{':
            depth += 1
        elif txt[j] == '}':
            depth -= 1
            if depth == 0:
                break
        j += 1
    return txt[m.start():j + 1]


# ---------------------------------------------------------------- classify

PLACEHOLDER = re.compile(r'^(FUN_|func_|DAT_|data_|sub_|thunk_)', re.I)

def is_named(sym):
    """A callee is grounding only if IT has a real name."""
    return not PLACEHOLDER.match(sym)


def calls_in(body):
    inner = body[body.index('{'):]
    out = []
    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', inner):
        w = m.group(1)
        if w not in ('if', 'while', 'for', 'switch', 'return', 'sizeof', 'do'):
            out.append(w)
    return out


def statements(body):
    inner = body[body.index('{') + 1:body.rindex('}')]
    inner = re.sub(r'/\*.*?\*/', '', inner, flags=re.S)
    inner = re.sub(r'//[^\n]*', '', inner)
    return [s.strip() for s in inner.split(';') if s.strip()]


def classify(sym, body):
    """-> (class, proposed_name or None).  Only confident classes get a name."""
    st = statements(body)
    cl = calls_in(body)

    if not st:
        return 'EMPTY', None

    # one call, nothing else: a forwarder.  Name it after the callee IF the
    # callee is named and a leading constant selects a variant.
    if len(st) == 1 and len(cl) == 1:
        callee = cl[0]
        m = re.search(re.escape(callee) + r'\s*\(([^)]*)\)', body)
        args = [a.strip() for a in m.group(1).split(',')] if m and m.group(1).strip() else []
        consts = [a for a in args if re.match(r'^(0x[0-9a-fA-F]+|\d+)$', a)]
        if is_named(callee):
            if args and re.match(r'^(0x[0-9a-fA-F]+|\d+)$', args[0]):
                v = int(args[0], 0)
                return 'FWD_CONST', '%s_%02X' % (callee.replace('_impl', ''), v)
            if not consts:
                return 'FWD_PLAIN', '%s_Wrapper' % callee.replace('_impl', '')
            return 'FWD_NAMED', None
        return 'FWD_UNNAMED', None

    # critical section around a global access
    if 'OS_DisableInterrupts' in cl and 'OS_RestoreInterrupts' in cl:
        return 'CRITSEC', None

    if all(is_named(c) for c in cl) and cl:
        return 'ALL_CALLEES_NAMED', None
    if cl:
        return 'SOME_UNNAMED', None
    return 'NOCALL', None


def load():
    unnamed = unnamed_set()
    files = c_file_map()
    rows = []
    for sym in unnamed:
        path = files.get(sym)
        if not path:
            rows.append((sym, None, 'NO_C_FILE', None))
            continue
        b = body_of(path, sym)
        if b is None:
            rows.append((sym, path, 'NO_BODY', None))
            continue
        c, n = classify(sym, b)
        rows.append((sym, path, c, n))
    return rows


if __name__ == '__main__':
    rows = load()
    if '--profile' in sys.argv:
        cnt = collections.Counter(r[2] for r in rows)
        print('total unnamed with C:', len(rows))
        for k, v in cnt.most_common():
            named = sum(1 for r in rows if r[2] == k and r[3])
            print('  %-20s %5d   (auto-nameable: %d)' % (k, v, named))
    elif '--show' in sys.argv:
        cls = sys.argv[sys.argv.index('--show') + 1]
        n = int(sys.argv[sys.argv.index('--show') + 2]) if len(sys.argv) > sys.argv.index('--show') + 2 else 8
        for sym, path, c, nm in rows:
            if c == cls and n > 0:
                print('=== %s   -> %s' % (sym, nm))
                print(body_of(path, sym))
                n -= 1
