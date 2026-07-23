"""Compare the ARG COUNT AT EVERY CALL SITE in nonmatching/ against what the matched tree uses.

Why this exists (2026-07-24): `audit_arity.py` compares the local `extern` DECLARATION against the
tree, and it deliberately skips `extern int f();` because an empty parameter list "is not a
declaration". It also only looks at `func_XXXXXXXX` style names. Both gaps hid the real cause of
`func_ov030_020b4410`: the park declared `extern int VEC_Mag();` (unprototyped, so no declared
arity to compare) and CALLED it with four arguments, while every matched call site passes one.
The three phantom arguments were enough extra live values to push mwcc over its
keep-vs-rematerialise threshold, and the residue surfaced ~0x99 bytes later looking exactly like a
register-allocation tie. It cost ~75 experiments across several sessions.

So: key on the CALL SITE, not the declaration, and cover every callee name -- including named
symbols like VEC_Mag / VEC_Add / MI_CpuCopy8, which the old regex ignored entirely.

    python tools/audit_callsite_arity.py            # parks whose call arity the tree contradicts
    python tools/audit_callsite_arity.py --all      # also print the consensus for each callee
"""
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")

IDENT = re.compile(r'\b([A-Za-z_]\w*)\s*\(')
# things that take parens but are not calls
KEYWORDS = {
    'if', 'for', 'while', 'switch', 'return', 'sizeof', 'do', 'else',
    'int', 'char', 'short', 'long', 'unsigned', 'signed', 'void', 'struct',
    'union', 'enum', 'const', 'volatile', 'static', 'extern', 'typedef',
    'float', 'double', 'register', 'inline', 'defined',
}


def split_args(s):
    """Split a balanced argument string on top-level commas."""
    if not s.strip():
        return []
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    out.append(cur)
    return [a.strip() for a in out]


def call_sites(text):
    """Yield (callee, argcount) for every call in the file, skipping declarations."""
    # strip comments and strings so their contents never parse as calls
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', ' ', text)
    text = re.sub(r'"(\\.|[^"\\])*"', '""', text)
    for m in IDENT.finditer(text):
        name = m.group(1)
        if name in KEYWORDS:
            continue
        # balanced scan for the closing paren
        i = m.end() - 1
        depth, j = 0, i
        while j < len(text):
            if text[j] == '(':
                depth += 1
            elif text[j] == ')':
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= len(text):
            continue
        inner = text[i + 1:j]
        # a declaration/definition, not a call
        before = text[max(0, m.start() - 90):m.start()]
        if 'extern' in before or 'typedef' in before:
            continue
        after = text[j + 1:j + 3]
        if after.strip()[:1] == '{':   # function definition
            continue
        # a prototype-ish arg list (types, no values) is a declaration
        args = split_args(inner)
        yield name, len(args)


def main():
    show_all = '--all' in sys.argv
    matched, parked = [], []
    for dirpath, _dirs, files in os.walk(SRC):
        norm = dirpath.replace('\\', '/')
        for fn in files:
            if not fn.endswith('.c'):
                continue
            p = os.path.join(dirpath, fn)
            if '/nonmatching' in norm:
                parked.append(p)
            elif '/asm_stubs' in norm:
                continue
            else:
                matched.append(p)

    consensus = defaultdict(lambda: defaultdict(int))
    for p in matched:
        try:
            t = open(p, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        for name, n in call_sites(t):
            consensus[name][n] += 1

    if show_all:
        for name in sorted(consensus):
            print("%-34s %s" % (name, dict(consensus[name])))
        return

    hits = 0
    for p in sorted(parked):
        try:
            t = open(p, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        bad = []
        for name, n in call_sites(t):
            seen = consensus.get(name)
            if not seen:
                continue
            total = sum(seen.values())
            # only flag when the tree is confident AND never uses our count
            if total >= 3 and n not in seen:
                bad.append("%s: called with %d, tree uses %s (%d sites)"
                           % (name, n, sorted(seen), total))
        if bad:
            hits += 1
            print("!! " + os.path.relpath(p, ROOT).replace('\\', '/'))
            for b in sorted(set(bad)):
                print("      " + b)
    print("\n%d parked files scanned, %d with a CALL-SITE arity contradiction"
          % (len(parked), hits))


if __name__ == "__main__":
    main()
