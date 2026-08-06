#!/usr/bin/env python3
"""Find functions whose bytes are identical to a target once relocations are masked out.

    python tools/findtwin.py <func_name> [--all]

Why: copies of the same function in different overlays are NOT byte-identical. Every branch and
pool word that carries a relocation encodes an address, so a copy at a different address differs
in exactly those words and a raw hex comparison finds nothing. Masking each function's own
relocation offsets before comparing recovers the twin.

If a twin already has real C under src/ or libs/, adapting it is usually a first-compile match:
rename the function and the struct names and verify. Run this BEFORE deriving any source.

Reported for each twin: whether it has REALC (integrated), NONMATCH, STUB, or no source at all.
"""
import glob
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def masked(entry):
    """Function bytes with every relocated word blanked out."""
    b = bytearray.fromhex(entry['hex'])
    for off, _sym in entry.get('relocs', []):
        for k in range(off, min(off + 4, len(b))):
            b[k] = 0
    return bytes(b)


def source_state():
    out = {}
    for root in ('src', 'libs'):
        for p in glob.iglob(os.path.join(ROOT, root, '**', '*.c'), recursive=True):
            rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
            parts = rel.split('/')
            name = os.path.basename(p)[:-2]
            if 'asm_stubs' in parts:
                out.setdefault(name, ('STUB', rel))
            elif 'calls' in parts or 'auto' in parts:
                out[name] = ('REALC', rel)
            elif 'nonmatching' in parts:
                out.setdefault(name, ('NONMATCH', rel))
    return out


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    target = sys.argv[1]
    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    if target not in idx:
        raise SystemExit("unknown function: %s" % target)

    me = idx[target]
    key = masked(me)
    syms = sorted(s for _o, s in me.get('relocs', []))
    srcs = source_state()

    hits = []
    for name, e in idx.items():
        if name == target or e.get('size') != me.get('size') or e.get('mode') != me.get('mode'):
            continue
        if masked(e) != key:
            continue
        same_syms = sorted(s for _o, s in e.get('relocs', [])) == syms
        kind, path = srcs.get(name, ('MISSING', '-'))
        hits.append((0 if kind == 'REALC' else 1, name, kind, path, same_syms))

    print("%s: %d bytes, %d relocs" % (target, me['size'], len(me.get('relocs', []))))
    if not hits:
        print("no reloc-masked twin")
        return
    print("%d twin(s):" % len(hits))
    for _rank, name, kind, path, same_syms in sorted(hits):
        print("  %-9s %-32s same_reloc_symbols=%-5s %s" % (kind, name, same_syms, path))


if __name__ == '__main__':
    main()
