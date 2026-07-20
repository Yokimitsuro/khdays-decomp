#!/usr/bin/env python3
"""Rank the naming debt by call-graph in-degree.

The debt is not flat: a handful of unnamed functions absorb thousands of call
sites, so naming a few percent of them removes a large share of the opacity a
reader (or the PC port) actually meets.  In-degree comes from the reloc table in
build/func_index.json -- a reloc to symbol S at offset N of function F is a call
site of S -- so this needs no Ghidra round-trip.

    python tools/namehubs.py [n]            # top n hubs still unnamed
    python tools/namehubs.py --unit main    # restrict to one unit
"""
import json
import os
import subprocess
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load_index():
    with open(os.path.join(ROOT, "build", "func_index.json"), encoding="utf-8") as fh:
        return json.load(fh)


def unnamed_set():
    """Names audit_unnamed.py considers debt, as {func_name: current_ghidra_name}."""
    out = subprocess.run(
        [sys.executable, os.path.join(ROOT, "tools", "audit_unnamed.py"), "--list"],
        capture_output=True, text=True, cwd=ROOT,
    ).stdout
    debt = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[0].startswith("func_"):
            debt[parts[0]] = parts[1]
        elif len(parts) == 1 and parts[0].startswith("func_"):
            debt[parts[0]] = "FUN_*"
    return debt


def main():
    args = [a for a in sys.argv[1:]]
    unit = None
    if "--unit" in args:
        i = args.index("--unit")
        unit = args[i + 1]
        del args[i:i + 2]
    topn = int(args[0]) if args else 40

    index = load_index()
    indeg = Counter()
    for fn, info in index.items():
        for _off, sym in info.get("relocs", []):
            indeg[sym] += 1

    debt = unnamed_set()
    rows = []
    for fn, cur in debt.items():
        info = index.get(fn)
        if info is None:
            continue
        if unit and info.get("unit") != unit:
            continue
        rows.append((indeg.get(fn, 0), fn, cur, info.get("size", 0), info.get("unit", "?")))
    rows.sort(reverse=True)

    total = sum(r[0] for r in rows)
    print("unnamed matched functions: %d   total call sites they absorb: %d" % (len(rows), total))
    head = sum(r[0] for r in rows[:topn])
    print("top %d absorb %d (%.1f%% of the opacity)\n" % (topn, head, 100.0 * head / total if total else 0))
    print("%-6s %-28s %-26s %6s  %s" % ("callers", "function", "current name", "size", "unit"))
    for deg, fn, cur, size, u in rows[:topn]:
        print("%-6d  %-28s %-26s %6d  %s" % (deg, fn, cur, size, u))


if __name__ == "__main__":
    main()
