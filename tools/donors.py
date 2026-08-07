"""Find a matched donor for each pending function by shared call targets.

The size-and-shape survey misses siblings whose tuning constants changed the
body length -- which is most of them. What survives retuning is WHO the function
calls: two copies of one routine in different overlays call the same shared
helpers. Rank matched functions by how much of the pending function's external
call set they reproduce. Usage: python build/try/donors.py ovNNN
"""
import json, os, re, sys

ROOT = "E:/KH 3582/decomp"
ov = sys.argv[1]
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

have = {}
for base in ("src", "libs"):
    for dp, _d, fs in os.walk(os.path.join(ROOT, base)):
        p = dp.replace("\\", "/").split("/")
        if p[-1] in ("calls", "auto") and "asm_stubs" not in p:
            for f in fs:
                if f.endswith(".c"):
                    have[f[:-2]] = os.path.join(dp, f)

sym = os.path.join(ROOT, "config", "arm9", "overlays", ov, "symbols.txt")
funcs = [re.match(r"(\S+)\s+kind:function\(", l).group(1)
         for l in open(sym, encoding="utf-8", errors="ignore") if "kind:function(" in l]
miss = [f for f in funcs if f not in have]


def shared(n):
    """External targets only: drop this overlay's own symbols, which never match."""
    return set(s for _o, s in idx[n]["relocs"] if ("_" + ov + "_") not in s)


print("%s pending: %d" % (ov, len(miss)))
for n in miss:
    want = shared(n)
    if not want:
        print("   %-26s %4d B  no external calls" % (n, len(idx[n]["hex"]) // 2))
        continue
    best = []
    for k in have:
        got = set(s for _o, s in idx.get(k, {}).get("relocs", []))
        hit = len(want & got)
        if hit:
            best.append((hit / float(len(want)), hit, k))
    best.sort(reverse=True)
    line = "   %-26s %4d B  %2d ext" % (n, len(idx[n]["hex"]) // 2, len(want))
    for frac, hit, k in best[:2]:
        line += "   %s %d/%d" % (k, hit, len(want))
    print(line if best else line + "   NO DONOR")
