#!/usr/bin/env python3
"""Real per-overlay completion, counted the way the delinker counts it.

Two traps this avoids, both of which produced wrong targets before:

  1. Counting only `asm_stubs/` + `nonmatching/` as pending IGNORES functions that have
     no source file at all (the delinker's "gap"), which are usually the majority.
  2. A function's source does NOT have to live under `src/overlays/ovNNN/`. Shared
     directories satisfy an overlay's delink too, and they are NOT all under src/:
     `src/calls`, `src/auto` AND `libs/**/calls` all appear in overlay delinks.txt
     files. Walk src/ and libs/ both.

The source of truth is the same one `gen_delinks.py` uses: an overlay function counts as
done when SOME `.c` named after it exists under any `calls/` or `auto/` directory.

    python tools/overlay_progress.py            # ranking of incomplete overlays
    python tools/overlay_progress.py ov000      # detail for one overlay
"""
import os
import re
import sys
import json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, "config", "arm9", "overlays")
ROOTS = [os.path.join(ROOT, "src"), os.path.join(ROOT, "libs")]


def all_sources():
    """Every function name that has a .c under ANY calls/ or auto/ directory."""
    have = set()
    for base in ROOTS:
      for dirpath, _dirs, files in os.walk(base):
        parts = dirpath.replace("\\", "/").split("/")
        if parts[-1] not in ("calls", "auto") or "asm_stubs" in parts:
            continue
        for f in files:
            if f.endswith(".c"):
                have.add(f[:-2])
    return have


def overlay_functions(ov):
    sym = os.path.join(CFG, ov, "symbols.txt")
    if not os.path.isfile(sym):
        return []
    out = []
    with open(sym, encoding="utf-8", errors="ignore") as fh:
        for line in fh:
            m = re.match(r"(\S+)\s+kind:function\(", line)
            if m:
                out.append(m.group(1))
    return out


def main():
    have = all_sources()
    idx_path = os.path.join(ROOT, "build", "func_index.json")
    idx = json.load(open(idx_path)) if os.path.isfile(idx_path) else {}

    if len(sys.argv) > 1:
        ov = sys.argv[1]
        funcs = overlay_functions(ov)
        missing = [f for f in funcs if f not in have]
        print("%s: %d/%d done, %d pending" % (ov, len(funcs) - len(missing), len(funcs), len(missing)))
        for f in missing:
            e = idx.get(f)
            print("   %-40s %s bytes" % (f, len(e["hex"]) // 2 if e else "?"))
        return

    rows = []
    for ov in sorted(os.listdir(CFG)):
        funcs = overlay_functions(ov)
        if not funcs:
            continue
        missing = [f for f in funcs if f not in have]
        if not missing:
            continue
        nbytes = sum(len(idx[f]["hex"]) // 2 for f in missing if f in idx)
        pct = 100.0 * (len(funcs) - len(missing)) / len(funcs)
        rows.append((len(missing), nbytes, -pct, ov, len(funcs)))

    rows.sort()
    print("%-8s %6s %9s %11s %s" % ("overlay", "pend", "bytes", "done/tot", "pct"))
    for pend, nb, negpct, ov, tot in rows[:25]:
        print("%-8s %6d %9d %6d/%-5d %.1f%%" % (ov, pend, nb, tot - pend, tot, -negpct))
    print("incomplete overlays: %d" % len(rows))


if __name__ == "__main__":
    main()
