#!/usr/bin/env python3
"""Genera un report.json en formato objdiff (para decomp.dev) a partir de
   nuestros datos verificados: tamanos por funcion + cuales estan hechas.
   No necesita build. Unidades = overlays/modulos."""
import json, glob, os, re
from collections import defaultdict
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
done = set(os.path.splitext(os.path.basename(f))[0]
           for f in glob.glob(os.path.join(ROOT, "src", "auto", "*.c")) +
                    glob.glob(os.path.join(ROOT, "src", "calls", "*.c")))

units = defaultdict(list)   # unit -> [(name, size, matched)]
for name, d in idx.items():
    m = re.search(r"@(ov\d+|main|itcm|dtcm)", d["module"])
    unit = m.group(1) if m else d["module"]
    units[unit].append((name, d["size"], name in done))

def measures(funcs):
    total = sum(s for _, s, _ in funcs)
    matched = sum(s for _, s, m in funcs if m)
    tf = len(funcs); mf = sum(1 for _, _, m in funcs if m)
    return {
        "fuzzyMatchPercent": 100.0 * matched / total if total else 100.0,
        "totalCode": total, "matchedCode": matched,
        "matchedCodePercent": 100.0 * matched / total if total else 100.0,
        "totalData": 0, "matchedData": 0, "matchedDataPercent": 100.0,
        "totalFunctions": tf, "matchedFunctions": mf,
        "matchedFunctionsPercent": 100.0 * mf / tf if tf else 100.0,
        "completeCode": matched, "completeCodePercent": 100.0 * matched / total if total else 100.0,
        "completeData": 0, "completeDataPercent": 100.0,
    }

report_units = []
for unit in sorted(units):
    funcs = sorted(units[unit], key=lambda x: x[0])
    report_units.append({
        "name": unit,
        "measures": measures(funcs),
        "sections": [],
        "functions": [{"name": n, "size": s, "fuzzyMatchPercent": 100.0 if m else 0.0}
                      for n, s, m in funcs],
        "metadata": {"moduleName": unit, "complete": all(m for _, _, m in funcs)},
    })

allfuncs = [f for u in units.values() for f in u]
agg = measures(allfuncs)
agg["totalUnits"] = len(units)
agg["completeUnits"] = sum(1 for u in report_units if u["metadata"]["complete"])
report = {"measures": agg, "units": report_units, "version": 5, "categories": []}
json.dump(report, open(os.path.join(ROOT, "build", "report.json"), "w"))
print("report.json -> %d unidades, %.2f%% code (%d/%d bytes)" %
      (len(units), agg["matchedCodePercent"], agg["matchedCode"], agg["totalCode"]))
