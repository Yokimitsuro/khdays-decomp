#!/usr/bin/env python3
"""Find nonmatching/ files whose extern declares an arity the matched tree NEVER uses.

A dropped trailing argument does NOT change the function's size -- it just moves a constant into
the wrong register, so the diff reads as an unbreakable allocator permutation. Three parked
functions were rescued this way on 2026-07-17 (ov115_020ce20c, ov256_020cd8f0, ov212_020ce0d4),
one of which had a ten-variant write-up confidently blaming register allocation.

Usage:  python tools/audit_arity.py            # strict: my arity appears NOWHERE in the tree
        python tools/audit_arity.py --loose    # also show where the tree uses OTHER arities too

Strict hits are strong candidates. Loose hits are mostly noise: the tree legitimately calls many
of these through K&R decls with varying counts.

Then, for each hit: disassemble the call site and look at what the ROM sets in r0-r3 (and [sp]).
The giveaway is a `mov rN, #0` hoisted ABOVE a branch -- that means the same 0 feeds a field store
AND a call's trailing argument.
"""
import collections
import io
import os
import re
import sys

CALL_RE = re.compile(r'\b(func_[0-9a-fA-F]{8}|func_ov\d+_[0-9a-fA-F]{8})\s*\(([^;{]*?)\)\s*;')
EXTERN_RE = re.compile(
    r'extern\s+[\w \*]+?\b(func_[0-9a-fA-F]{8}|func_ov\d+_[0-9a-fA-F]{8})\s*\(([^)]*)\)\s*;')


def argcount(s):
    """Count top-level commas in an argument list."""
    depth = 0
    n = 1 if s.strip() else 0
    for ch in s:
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        elif ch == ',' and depth == 0:
            n += 1
    return n


def read(path):
    try:
        return io.open(path, encoding='utf-8', errors='replace').read()
    except OSError:
        return ''


def main():
    loose = '--loose' in sys.argv

    # arity actually used at call sites in MATCHED code only
    used = collections.defaultdict(collections.Counter)
    parked = []
    for root, _dirs, files in os.walk('src'):
        is_parked = 'nonmatching' in root
        is_stub = 'asm_stubs' in root
        for f in files:
            if not f.endswith('.c'):
                continue
            path = os.path.join(root, f)
            if is_parked:
                parked.append(path)
                continue
            if is_stub:
                continue
            s = read(path)
            for m in CALL_RE.finditer(s):
                if 'extern' in s[max(0, m.start() - 80):m.start()]:
                    continue
                used[m.group(1)][argcount(m.group(2))] += 1

    hits = []
    for p in sorted(parked):
        s = read(p)
        bad = []
        for m in EXTERN_RE.finditer(s):
            name, args = m.group(1), m.group(2)
            if args.strip() in ('', 'void'):
                continue          # K&R / void decls carry no arity claim
            mine = argcount(args)
            seen = used.get(name)
            if not seen:
                continue
            if mine not in seen:
                bad.append('%s: declared %d, tree ONLY uses %s' % (name, mine, dict(seen)))
            elif loose and set(seen) - {mine}:
                bad.append('(loose) %s: declared %d, tree uses %s' % (name, mine, dict(seen)))
        if bad:
            hits.append((p.replace(os.sep, '/'), bad))

    for p, bad in hits:
        print('!! ' + p)
        for b in bad:
            print('      ' + b)
    print()
    print('%d parked files scanned, %d with an arity disagreement%s'
          % (len(parked), len(hits), '' if loose else ' (strict)'))


if __name__ == '__main__':
    main()
