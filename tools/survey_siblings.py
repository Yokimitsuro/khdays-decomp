"""List an overlay's pending functions and, for each, the best matched sibling.

Prints the displacement to every candidate sibling so the dominant one is
obvious: a whole actor class transplanted into another overlay shows up as one
constant offset repeated across every pending function.

Usage: python build/try/survey.py ovNNN
"""
import json, os, re, sys

ROOT = "E:/KH 3582/decomp"
ov = sys.argv[1]
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

have = set()
for base in ("src", "libs"):
    for dp, _d, fs in os.walk(os.path.join(ROOT, base)):
        p = dp.replace("\\", "/").split("/")
        if p[-1] in ("calls", "auto") and "asm_stubs" not in p:
            have.update(f[:-2] for f in fs if f.endswith(".c"))

sym = os.path.join(ROOT, "config", "arm9", "overlays", ov, "symbols.txt")
funcs = [re.match(r"(\S+)\s+kind:function\(", l).group(1)
         for l in open(sym, encoding="utf-8", errors="ignore") if "kind:function(" in l]
miss = [f for f in funcs if f not in have]
print("%s pending: %d" % (ov, len(miss)))

votes = {}
rows = []
for n in miss:
    a = idx[n]
    addr = int(n.split("_")[-1], 16)
    cands = []
    for k, v in idx.items():
        m = re.match(r"func_(ov\d+)_([0-9a-f]{8})$", k)
        if m and k in have and len(v["hex"]) == len(a["hex"]) and len(v["relocs"]) == len(a["relocs"]):
            key = (m.group(1), addr - int(m.group(2), 16))
            cands.append(key)
            votes[key] = votes.get(key, 0) + 1
    rows.append((n, len(a["hex"]) // 2, cands))

best = sorted(votes.items(), key=lambda kv: -kv[1])[:3]
print("dominant (source overlay, displacement) pairs:")
for (sov, d), c in best:
    print("   %s  disp=0x%x  covers %d/%d" % (sov, d, c, len(miss)))

if best:
    sov, disp = best[0][0]
    print("\nper function against %s at 0x%x:" % (sov, disp))
    for n, sz, cands in rows:
        ok = (sov, disp) in cands
        print("   %-26s %4d B  %s" % (n, sz, "sibling present" if ok else "NO SIBLING"))
