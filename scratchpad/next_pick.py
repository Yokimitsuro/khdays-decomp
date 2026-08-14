"""Selection pass with no active lock: sweep staging recursively for real C,
then rank ov002's pending functions. Priority is the frontier, so the direct
callees of the function just matched come first: they are the dependencies the
panel rebuild needs, not merely convenient addresses.
"""
import sys
import os
import json
import re
import glob

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))

BAD = ("__asm", "asm(", "\tasm", " asm ", "dcd ", "__emit")

print("=== staging sweep ===")
staged = sorted(glob.glob("staging/**/*.c", recursive=True))
integrated = set()
for pat in ("src/**/calls/*.c", "src/**/auto/*.c",
            "libs/**/calls/*.c", "libs/**/auto/*.c"):
    for p in glob.glob(pat, recursive=True):
        integrated.add(os.path.splitext(os.path.basename(p))[0])
pending_staged = []
for p in staged:
    sym = os.path.splitext(os.path.basename(p))[0]
    if sym in integrated:
        continue
    try:
        body = open(p, encoding="utf-8", errors="replace").read()
    except Exception:
        continue
    bad = [w for w in BAD if w in body]
    pending_staged.append((sym, p, bad))
print("staged .c files: %d; not yet integrated: %d" % (len(staged), len(pending_staged)))
for sym, p, bad in pending_staged[:15]:
    print("   %-32s %s  %s" % (sym, p, ("REJECT " + ",".join(bad)) if bad else "clean"))
if not pending_staged:
    print("   nothing pending in staging")

print()
print("=== ov002 frontier ===")
IDX = json.load(open("build/func_index.json"))
# the direct callees of the function just matched
src = open("src/overlays/ov002/calls/func_ov002_0205bff4.c").read()
callees = sorted(set(re.findall(r"\bfunc_(?:ov002_)?[0-9a-f]{8}\b", src)))
callees = [c for c in callees if c != "func_ov002_0205bff4"]
rows = []
for c in callees:
    e = IDX.get(c)
    if not e:
        continue
    rows.append((c in integrated, len(bytearray.fromhex(e["hex"])),
                 len(e["relocs"]), c))
rows.sort(key=lambda r: (r[0], r[1]))
print("direct callees of the rebuild: %d in the index" % len(rows))
print("%-34s %-8s %-8s %s" % ("callee", "bytes", "relocs", "state"))
for done, size, nrel, c in rows:
    print("%-34s %-8d %-8d %s" % (c, size, nrel, "matched" if done else "PENDING"))
