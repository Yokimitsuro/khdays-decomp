#!/usr/bin/env python3
"""Find the UNMATCHED remainder of an identified subsystem, by reloc intersection.

    python tools/subsyscensus.py <sym> [<sym> ...] [--min 2] [--max-size N]

Lists functions that have no real C yet and whose relocs hit at least `--min` of
the given symbols, ranked by how many they hit.

This is a different axis from the other two candidate finders and it catches
things they structurally cannot:

  tools/dense.py    ranks by reloc DENSITY -- good for "what is cheap to match",
                    blind to "what belongs together".
  tools/dedupprop   needs a matched representative to already exist, so it is
                    useless while an entire family is still unmatched.
  this              needs only that you have NAMED the subsystem, and finds its
                    members even when none of them is matched yet.

Found func_ov008_0208bd9c (the third CommitSaveToSlot) in one run, from a single
census over the save-system symbols, when neither of the others could have.

Use it right after naming a subsystem: that is the moment you know its symbol set
and the moment the census is worth the most.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def matched_names():
    """Function names that already have real C (not asm_stubs, not nonmatching)."""
    have = set()
    for root, _dirs, files in os.walk(os.path.join(ROOT, "src")):
        if "asm_stubs" in root or "nonmatching" in root:
            continue
        for f in files:
            if f.endswith(".c"):
                have.add(f[:-2])
    return have


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    mn = 2
    mx = 10 ** 9
    if "--min" in sys.argv:
        mn = int(sys.argv[sys.argv.index("--min") + 1])
    if "--max-size" in sys.argv:
        mx = int(sys.argv[sys.argv.index("--max-size") + 1])
    want = set(args)
    if not want:
        raise SystemExit(__doc__)

    idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
    have = matched_names()
    rows = []
    for name, e in idx.items():
        if name in have or e["size"] > mx:
            continue
        syms = {s for _o, s in e["relocs"]}
        hit = syms & want
        if len(hit) >= mn:
            rows.append((len(hit), e["size"], name, sorted(hit)))
    rows.sort(key=lambda r: (-r[0], r[1]))
    print("%d unmatched functions hit >=%d of %d symbols" % (len(rows), mn, len(want)))
    for n, size, name, hit in rows[:40]:
        print("  hits=%d %5dB  %-26s  %s" % (n, size, name, " ".join(hit[:4])))


if __name__ == "__main__":
    main()
