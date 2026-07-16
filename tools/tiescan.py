#!/usr/bin/env python3
"""Candidate triage for the decomp loop.

Two filters that together cut most wasted cycles, learned 2026-07-16:

1. ctx-CSE immunity — functions with a data reloc to a global context pointer that is read on
   both sides of a call tie on CSE/rematerialisation (see references/deferred-ties.md). Filtering
   to candidates with NO data relocs raised the hit rate from ~0/2 to ~3/4 per batch.

2. known-tie twins — a candidate whose reloc-masked bytes equal those of a function already in
   src/overlays/*/nonmatching/ will tie for exactly the same reason. Skip it.

usage:
    python tools/tiescan.py [overlay]      # e.g. ov025; omit for all overlays
prints: fresh candidates (worth attempting), and the known-tie twins with their rep.
"""
import json
import os
import re
import sys
import glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = os.path.join(ROOT, "build", "func_index.json")


def masked(f):
    b = bytearray.fromhex(f["hex"])
    for off, _sym in f["relocs"]:
        for i in range(4):
            if off + i < len(b):
                b[off + i] = 0
    return bytes(b).hex()


def carved(ov, name):
    for sub in ("calls", "auto", "nonmatching"):
        if os.path.exists(os.path.join(ROOT, "src", "overlays", ov, sub, name + ".c")):
            return True
    return False


def main():
    only = sys.argv[1] if len(sys.argv) > 1 else None
    idx = json.load(open(IDX))

    # index every already-routed nonmatching function by its masked bytes
    reps = {}
    for p in glob.glob(os.path.join(ROOT, "src", "overlays", "*", "nonmatching", "*.c")):
        n = os.path.basename(p)[:-2]
        if n in idx:
            reps[masked(idx[n])] = n

    fresh, ties = [], []
    for k, f in idx.items():
        m = re.match(r"func_(ov\d+)_", k)
        if not m:
            continue
        ov = m.group(1)
        if only and ov != only:
            continue
        if carved(ov, k):
            continue
        size = f["size"]
        syms = [s for _o, s in f["relocs"]]
        if any(s.startswith("data_") for s in syms):
            continue                       # filter 1: ctx-CSE risk
        if not (64 <= size <= 140) or not (2 <= len(syms) <= 6):
            continue
        h = masked(f)
        if h in reps:
            ties.append((k, reps[h]))      # filter 2: proven tie
        else:
            fresh.append((size, len(syms), ov, k))

    fresh.sort()
    print("known-tie twins (SKIP, they tie for the rep's reason): %d" % len(ties))
    for k, rep in ties:
        print("   %s == tie of %s" % (k, rep))
    print()
    print("fresh candidates: %d" % len(fresh))
    for s, r, ov, k in fresh[:40]:
        print("   %4dB %dr  %s" % (s, r, k))


if __name__ == "__main__":
    main()
