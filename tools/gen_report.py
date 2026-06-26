#!/usr/bin/env python3
"""Genera un report.json en formato objdiff (para decomp.dev) a partir de
   nuestros datos verificados: tamanos por funcion + cuales estan hechas.
   No necesita build. Unidades = overlays/modulos."""
import json, glob, os, re
from collections import defaultdict
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
done = set(os.path.splitext(os.path.basename(f))[0]
           for f in glob.glob(os.path.join(ROOT, "src", "auto", "*.c")) +
                    glob.glob(os.path.join(ROOT, "src", "calls", "*.c")))

def load_funcs():
    """(name, size, unit). Usa func_index.json en local; en CI parsea config/."""
    fi = os.path.join(ROOT, "build", "func_index.json")
    out = []
    if os.path.exists(fi):
        for name, d in json.load(open(fi)).items():
            m = re.search(r"@(ov\d+|main|itcm|dtcm)", d["module"])
            out.append((name, d["size"], m.group(1) if m else d["module"]))
    else:
        for sp in glob.glob(os.path.join(ROOT, "config", "**", "symbols.txt"), recursive=True):
            p = sp.replace("\\", "/")
            mo = re.search(r"overlays/(ov\d+)", p)
            unit = mo.group(1) if mo else ("itcm" if "/itcm/" in p else
                   "dtcm" if "/dtcm/" in p else "main")
            for line in open(sp, encoding="utf-8", errors="replace"):
                m = re.match(r"(\S+)\s+kind:function\([^)]*size=0x([0-9a-fA-F]+)", line)
                if m:
                    out.append((m.group(1), int(m.group(2), 16), unit))
    return out

units = defaultdict(list)   # unit -> [(name, size, matched)]
for name, size, unit in load_funcs():
    units[unit].append((name, size, name in done))

def measures(funcs):
    total = sum(s for _, s, _ in funcs)
    matched = sum(s for _, s, m in funcs if m)
    tf = len(funcs); mf = sum(1 for _, _, m in funcs if m)
    pct = 100.0 * matched / total if total else 100.0
    # protobuf-JSON: uint64 fields go as STRINGS; uint32 + floats as numbers
    return {
        "fuzzyMatchPercent": pct,
        "totalCode": str(total), "matchedCode": str(matched),
        "matchedCodePercent": pct,
        "totalData": "0", "matchedData": "0", "matchedDataPercent": 100.0,
        "totalFunctions": tf, "matchedFunctions": mf,
        "matchedFunctionsPercent": 100.0 * mf / tf if tf else 100.0,
        "completeCode": str(matched), "completeCodePercent": pct,
        "completeData": "0", "completeDataPercent": 100.0,
    }

report_units = []
for unit in sorted(units):
    funcs = sorted(units[unit], key=lambda x: x[0])
    report_units.append({
        "name": unit,
        "measures": measures(funcs),
        "sections": [],
        "functions": [{"name": n, "size": str(s), "fuzzyMatchPercent": 100.0 if m else 0.0}
                      for n, s, m in funcs],
        "metadata": {"moduleName": unit, "complete": all(m for _, _, m in funcs)},
    })

allfuncs = [f for u in units.values() for f in u]
agg = measures(allfuncs)
agg["totalUnits"] = len(units)
agg["completeUnits"] = sum(1 for u in report_units if u["metadata"]["complete"])
report = {"measures": agg, "units": report_units, "version": 2, "categories": []}
os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
json.dump(report, open(os.path.join(ROOT, "build", "report.json"), "w"))
print("report.json -> %d unidades, %.2f%% code (%d/%d bytes)" %
      (len(units), agg["matchedCodePercent"], agg["matchedCode"], agg["totalCode"]))
