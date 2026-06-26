#!/usr/bin/env python3
"""Genera PROGRESS.md: progreso de decompilacion por overlay/modulo."""
import json, glob, os, re
from collections import defaultdict
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
done = set(os.path.splitext(os.path.basename(f))[0]
           for f in glob.glob(os.path.join(ROOT, "src", "auto", "*.c")) +
                    glob.glob(os.path.join(ROOT, "src", "calls", "*.c")))

stats = defaultdict(lambda: [0, 0])   # modulo -> [done, total]
for name, d in idx.items():
    m = re.search(r"@(ov\d+|main|itcm|dtcm)", d["module"])
    mod = m.group(1) if m else d["module"]
    stats[mod][1] += 1
    if name in done:
        stats[mod][0] += 1

def keyf(k):
    m = re.match(r"ov(\d+)", k)
    return (1, int(m.group(1))) if m else (0, k)

L = ["# Progress by module", "",
     "Auto-generated. Pick a module that isn't finished, **claim it** (see",
     "[CONTRIBUTING.md](CONTRIBUTING.md#claiming-work)), and decompile its functions.", "",
     "| Module | Done | Total | % |", "|---|---:|---:|---:|"]
td = tt = 0
for k in sorted(stats, key=keyf):
    dn, tot = stats[k]; td += dn; tt += tot
    bar = "✅" if dn == tot else ("🟡" if dn else "⬜")
    L.append("| %s %s | %d | %d | %.0f%% |" % (bar, k, dn, tot, 100 * dn / tot))
L.append("| **TOTAL** | **%d** | **%d** | **%.1f%%** |" % (td, tt, 100 * td / tt))
open(os.path.join(ROOT, "PROGRESS.md"), "w", encoding="utf-8", newline="\n").write("\n".join(L) + "\n")
print("PROGRESS.md -> %d/%d (%.1f%%) en %d modulos" % (td, tt, 100 * td / tt, len(stats)))
