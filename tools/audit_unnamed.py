#!/usr/bin/env python3
"""Find byte-exact C functions that are still called FUN_* in Ghidra.

The project's hard rule is that a match with no semantic layer is "half done" and does not count.
That rule relied on discipline and duly failed: on 2026-07-17 six rescued functions were committed
unnamed simply because rescuing does not feel like new decomp work. This makes the debt countable
instead of remembered.

Ghidra must be open with days.nds and the GhidraMCP plugin serving (TCP 127.0.0.1:8089 -- NOT 8080).
This is a read-only audit; it never mutates the program.

Usage:  python tools/audit_unnamed.py           # summary + per-overlay counts
        python tools/audit_unnamed.py --list    # every unnamed function
"""
import http.client
import os
import re
import sys
import urllib.parse
from collections import Counter

PORT = 8089


def get(endpoint, params=None, timeout=120):
    q = '?' + urllib.parse.urlencode(params) if params else ''
    c = http.client.HTTPConnection('127.0.0.1', PORT, timeout=timeout)
    c.request('GET', '/' + endpoint + q)
    r = c.getresponse()
    out = r.read().decode('utf-8', 'replace')
    c.close()
    return out


def ghidra_names():
    """addr(lowercase hex, no space prefix) -> current Ghidra name."""
    out = get('list_functions', {'limit': 30000})
    names = {}
    for line in out.splitlines():
        if ' at ' not in line:
            continue
        name, _, addr = line.rpartition(' at ')
        names[addr.strip().lower()] = name.strip()
    return names


def matched_c():
    """func name -> path, for real byte-exact C only."""
    out = {}
    for root, _dirs, files in os.walk('src'):
        if 'nonmatching' in root or 'asm_stubs' in root:
            continue
        for f in files:
            if f.endswith('.c') and f.startswith('func_'):
                out[f[:-2]] = os.path.join(root, f).replace(os.sep, '/')
    return out


def main():
    show = '--list' in sys.argv
    try:
        gn = ghidra_names()
    except OSError as e:
        print('cannot reach the GhidraMCP bridge on 127.0.0.1:%d (%s)' % (PORT, e))
        print('is Ghidra open with days.nds? note the port is 8089, not 8080.')
        return 1

    unnamed = []
    missing = 0
    for name in sorted(matched_c()):
        m = re.search(r'([0-9a-fA-F]{8})$', name)
        if not m:
            continue
        addr = m.group(1).lower()
        # Overlay functions live in a prefixed address space: func_ov000_020593f4 is at
        # `arm9_ov000::020593f4`, NOT `020593f4`. Looking up the bare address silently finds
        # nothing and makes the whole overlay tree look clean -- the same prefix trap that made
        # a rename read-back report 27/27 "missing" on 2026-07-17.
        ov = re.match(r'func_(ov\d+)_', name)
        key = 'arm9_%s::%s' % (ov.group(1), addr) if ov else addr
        cur = gn.get(key)
        if cur is None:
            missing += 1                   # not a defined function in Ghidra
            continue
        if cur.startswith('FUN_'):
            unnamed.append((name, cur))

    print('byte-exact C functions still named FUN_* in Ghidra: %d' % len(unnamed))
    if missing:
        print('(%d had no defined function in Ghidra at all)' % missing)
    if not unnamed:
        print('naming debt is clear.')
        return 0

    by_unit = Counter()
    for name, _cur in unnamed:
        m = re.match(r'func_(ov\d+)_', name)
        by_unit[m.group(1) if m else 'main'] += 1
    print('\nworst units:')
    for unit, n in by_unit.most_common(15):
        print('   %-8s %d' % (unit, n))
    if show:
        print()
        for name, cur in unnamed:
            print('   %-28s %s' % (name, cur))
    else:
        print('\nre-run with --list to see them all')
    return 0


if __name__ == '__main__':
    sys.exit(main())
