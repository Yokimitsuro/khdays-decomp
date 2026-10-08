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

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PORT = 8089

# `FUN_` is not the only way to have no name. `ov000_helper_4d354` passes a startswith('FUN_')
# test and means exactly as much -- 210 of them were hiding from this audit until 2026-07-17,
# which is the same "invisible until counted" failure the audit was written to fix.
#
# THIS IS THE ONE DEFINITION -- `namefam_propagate.py` imports it. It used to carry its own,
# slightly wider, copy; the two disagreed by 17 functions and the gap only showed up because a
# rename batch of 78 moved the audit by 61. Same lesson as the ARM/THUMB verify split: when two
# tools own one predicate, the bug lives in the difference.
#
# NOT placeholders: `WaitDivResult64_8ab0` and ~1035 like it. A semantic root with an address
# suffix is a disambiguated real name; only a placeholder *root* counts as debt.
#
# The separator is MANDATORY and the suffix must contain a digit, both to stop the regex eating
# real names: `SetFade` and `GetFace` are spelled entirely out of a-f, so `Set_?[0-9a-f]{4,8}$`
# matches them and this tool would have reported -- and namefam_propagate would have OVERWRITTEN
# -- two perfectly good names. An address suffix always carries a digit and always has the `_`.
PLACEHOLDER_ROOTS = 'helper|sub|fn|func|f|thunk|nullsub|set|get|fwd|statestep|st'
PLACEHOLDER = re.compile(r'^((Ov|ov)\d{3}_)?(%s)_(?=[0-9a-fA-F]*\d)[0-9a-fA-F]{4,8}$'
                         % PLACEHOLDER_ROOTS, re.I)


# Function symbols no longer all look like func_<addr>: since 2026-09-28 most carry their real
# name, so the address comes from config/**/symbols.txt instead of the name. Module "arm9",
# "itcm" and "dtcm" functions live in Ghidra's default space; overlay ones in arm9_ovNNN.
_SYMBOLS = None


def symbol_table():
    """function name -> Ghidra key ('020593f4' or 'arm9_ov000::020593f4'), for every module."""
    global _SYMBOLS
    if _SYMBOLS is None:
        _SYMBOLS = {}
        for dirpath, _dirs, files in os.walk(os.path.join(ROOT, 'config', 'arm9')):
            if 'symbols.txt' not in files:
                continue
            mod = os.path.basename(dirpath)
            with open(os.path.join(dirpath, 'symbols.txt'), encoding='utf-8') as fh:
                for line in fh:
                    m = re.match(r'(\S+)\s+kind:function.*addr:0x([0-9a-fA-F]+)', line)
                    if m:
                        addr = m.group(2).lower()
                        _SYMBOLS[m.group(1)] = ('arm9_%s::%s' % (mod, addr)) if mod.startswith('ov') else addr
    return _SYMBOLS


def ghidra_key(name):
    """Ghidra address key for a function symbol, whatever it is called."""
    key = symbol_table().get(name)
    if key is not None:
        return key
    m = re.search(r'([0-9a-fA-F]{8})$', name)
    if not m:
        return None
    ov = re.match(r'func_(ov\d+)_', name)
    return 'arm9_%s::%s' % (ov.group(1), m.group(1).lower()) if ov else m.group(1).lower()


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
    for root, _dirs, files in os.walk(os.path.join(ROOT, 'src')):
        if 'nonmatching' in root or 'asm_stubs' in root:
            continue
        for f in files:
            if f.endswith('.c') and (f.startswith('func_') or f[:-2] in symbol_table()):
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
    placeholders = []
    missing = 0
    for name in sorted(matched_c()):
        # Overlay functions live in a prefixed address space: Ov000_ScrollListToRow is at
        # `arm9_ov000::020593f4`, NOT `020593f4`. Looking up the bare address silently finds
        # nothing and makes the whole overlay tree look clean -- the same prefix trap that made
        # a rename read-back report 27/27 "missing" on 2026-07-17.
        key = ghidra_key(name)
        if key is None:
            continue
        cur = gn.get(key)
        if cur is None:
            missing += 1                   # not a defined function in Ghidra
            continue
        if cur.startswith('FUN_'):
            unnamed.append((name, cur))
        elif PLACEHOLDER.match(cur):
            placeholders.append((name, cur))

    print('byte-exact C functions still named FUN_* in Ghidra: %d' % len(unnamed))
    if placeholders:
        print('...plus %d named like `ov000_helper_4d354` -- a placeholder, not a name: %d total'
              % (len(placeholders), len(unnamed) + len(placeholders)))
    if missing:
        print('(%d had no defined function in Ghidra at all)' % missing)
    if not unnamed and not placeholders:
        print('naming debt is clear.')
        return 0

    by_unit = Counter()
    for name, _cur in unnamed + placeholders:
        # Renamed symbols need not spell out their overlay. Use the same address
        # space that found the function above, including the legacy-name fallback.
        m = re.match(r'arm9_(ov\d+)::', ghidra_key(name))
        by_unit[m.group(1) if m else 'main'] += 1
    print('\nworst units:')
    for unit, n in by_unit.most_common(15):
        print('   %-8s %d' % (unit, n))
    if show:
        print()
        for name, cur in unnamed + placeholders:
            print('   %-28s %s' % (name, cur))
    else:
        print('\nre-run with --list to see them all')
    return 0


if __name__ == '__main__':
    sys.exit(main())
