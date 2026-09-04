#!/usr/bin/env python3
"""Rank already-carved functions by how closely their instruction SHAPE matches
a pending one, so the nearest decompiled neighbour can be read before any source
is invented.

    python tools/find_shape.py func_ov030_020b35dc
    python tools/find_shape.py func_ov030_020b35dc --min 0.80 --top 12

The shape is the mnemonic sequence, so relocated operands, pool values and
register choices do not matter. Only sources under a calls/ or auto/ directory
count; asm_stubs are excluded, because a stub reproduces the ROM without saying
anything about the C that produced it.

A neighbour above roughly 0.85 is usually worth reading in full: it tends to
carry the return type, the argument spelling and the field vocabulary that the
target needs.
"""
import argparse
import difflib
import glob
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = os.path.join(ROOT, 'build', 'func_index.json')

_MD = {'arm': Cs(CS_ARCH_ARM, CS_MODE_ARM), 'thumb': Cs(CS_ARCH_ARM, CS_MODE_THUMB)}


def shape(entry):
    md = _MD.get(entry.get('mode'), _MD['arm'])
    return [i.mnemonic for i in md.disasm(bytes.fromhex(entry['hex']), 0)]


def carved():
    """name -> path, for real C only"""
    out = {}
    for pat in ('src/**/*.c', 'libs/**/*.c'):
        for p in glob.glob(os.path.join(ROOT, pat), recursive=True):
            q = p.replace(os.sep, '/')
            if '/asm_stubs/' in q:
                continue
            if '/calls/' not in q and '/auto/' not in q:
                continue
            out[os.path.basename(q)[:-2]] = q
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('--min', type=float, default=0.75,
                    help='lowest similarity to report (default 0.75)')
    ap.add_argument('--top', type=int, default=10)
    ap.add_argument('--span', type=float, default=2.0,
                    help='only consider sizes within this factor (default 2.0)')
    args = ap.parse_args()

    idx = json.load(open(IDX))
    if args.function not in idx:
        raise SystemExit('%s is not in func_index' % args.function)
    target = idx[args.function]
    tshape = shape(target)
    have = carved()

    lo, hi = target['size'] / args.span, target['size'] * args.span
    scored = []
    for name, e in idx.items():
        if name not in have or name == args.function:
            continue
        if not (lo <= e['size'] <= hi):
            continue
        r = difflib.SequenceMatcher(None, tshape, shape(e)).ratio()
        if r >= args.min:
            scored.append((r, name, e['size'], e.get('mode'), have[name]))

    scored.sort(reverse=True)
    print('%s: %d bytes, %s, %d instructions'
          % (args.function, target['size'], target.get('mode'), len(tshape)))
    if not scored:
        print('no carved function scores at least %.2f' % args.min)
        return
    print('%d carved neighbours at or above %.2f:' % (len(scored), args.min))
    for r, name, size, mode, path in scored[:args.top]:
        print('  %.3f  %-30s %4dB %-5s %s'
              % (r, name, size, mode, os.path.relpath(path, ROOT)))


if __name__ == '__main__':
    main()
