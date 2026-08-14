"""Build the reachable ov002 frontier: pending functions that already-matched
ov002 sources call, ranked by how many matched callers reference them."""
import os
import re
import json
import glob
import collections

idx = json.load(open("build/func_index.json"))

have = set()
srcs = []
for pat in ("src/**/calls/*.c", "src/**/auto/*.c", "libs/**/calls/*.c",
            "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        if "asm_stubs" in p.replace("\\", "/"):
            continue
        have.add(os.path.splitext(os.path.basename(p))[0])
        srcs.append(p)

pending = set(n for n in idx if n.startswith("func_ov002_") and n not in have)

callers = collections.defaultdict(set)
for p in srcs:
    base = os.path.splitext(os.path.basename(p))[0]
    try:
        txt = open(p, errors="replace").read()
    except Exception:
        continue
    for m in re.findall(r"func_ov002_[0-9a-f]{8}", txt):
        if m in pending and m != base:
            callers[m].add(base)

rows = []
for fn, cs in callers.items():
    e = idx[fn]
    rows.append((len(cs), -e["size"], fn, e["size"], e["mode"],
                 len(e["relocs"]), sorted(cs)))
rows.sort(reverse=True)

print("%d pending ov002 functions are referenced by matched sources" % len(rows))
print()
for nc, negsz, fn, sz, mode, nr, cs in rows[:18]:
    print("%2d callers  %-28s %5d B  %-5s relocs=%-3d" % (nc, fn, sz, mode, nr))
    print("            called by: %s" % ", ".join(cs[:6]))
