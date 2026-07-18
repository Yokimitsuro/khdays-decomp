#!/usr/bin/env python3
"""Ordena los parks de nonmatching/ por CERCANIA REAL al original.

    python tools/rank_parks.py            # ranking completo + los mas cercanos
    python tools/rank_parks.py 3          # solo los que difieren en <=3 instrucciones

Cercania = numero de instrucciones que difieren tras ALINEAR los dos streams
(difflib sobre el desensamblado), no la diferencia de tamano en bytes.

POR QUE: el delta de bytes NO mide cercania y creerlo cuesta una sesion entera.
El 2026-07-18 filtre los parks a "+-4 bytes = una instruccion ARM = firma de
argumento perdido" y salieron 103 candidatos que parecian una veta enorme. Medidos
de verdad, **1 de los 103** era una diferencia de una sola instruccion; los otros 102
difieren en 5-58 instrucciones y coinciden en tamano por casualidad. El ranking real
saca 14 parks a <=2 instrucciones, y de los 5 primeros que mire, 3 se arreglaron en
minutos (dos por signo ldrb/ldrsb, uno por `v = i = 0`).

Escribe build/try/rank.json con las instrucciones solo-ROM y solo-mias de cada park,
que es lo que da el diagnostico directo (signo, orden de cmp, if-conversion, ...).

Modo ARM/THUMB automatico desde symbols.txt via _argprobe.
"""
import json
import os
import sys
from collections import Counter
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import _argprobe as P

ROOT = P.ROOT
LIMIT = int(sys.argv[1]) if len(sys.argv) > 1 else 2


def parks():
    tri = os.path.join(ROOT, "build", "sweep", "triage", "triage.json")
    if os.path.exists(tri):
        rows = json.load(open(tri))
        return [(r[0], r[1], r[4]) for r in rows
                if r[2] in ("off", "size") and os.path.exists(r[1])]
    import glob
    import re
    modes = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s", ln)
            if m:
                if "function(thumb" in ln:
                    modes[m.group(1)] = "thumb"
                elif "function(arm" in ln:
                    modes[m.group(1)] = "arm"
    out = []
    for pat in ("src/**/nonmatching/*.c", "libs/**/nonmatching/*.c"):
        for f in glob.glob(os.path.join(ROOT, pat), recursive=True):
            g = f.replace(os.sep, "/")
            n = os.path.basename(g)[:-2]
            if n in P.IDX:
                out.append((n, g, modes.get(n, "arm")))
    return out


def one(case):
    name, cpath, mode = case
    th = (mode == "thumb")
    base = P.build(cpath, name, th, 950)
    if not base:
        return None
    ro, mo = P.rom_only(name, base[0], th)
    return (name, cpath, mode, ro, mo)


def main():
    cases = parks()
    print("parks vivos:", len(cases))
    rows = []
    with ThreadPoolExecutor(max_workers=10) as ex:
        for i, r in enumerate(ex.map(one, cases)):
            if r:
                rows.append(r)
            if (i + 1) % 50 == 0:
                print("  ...%d/%d" % (i + 1, len(cases)), file=sys.stderr)
    rows.sort(key=lambda r: (max(len(r[3]), len(r[4])), len(r[3]) + len(r[4])))
    os.makedirs(os.path.join(ROOT, "build", "try"), exist_ok=True)
    json.dump(rows, open(os.path.join(ROOT, "build", "try", "rank.json"), "w"), indent=1)

    c = Counter(max(len(r[3]), len(r[4])) for r in rows)
    print()
    print("=== distribucion de la distancia real ===")
    for k in sorted(c)[:12]:
        print("   %2d instr  x%d" % (k, c[k]))
    near = [r for r in rows if max(len(r[3]), len(r[4])) <= LIMIT]
    print()
    print("=== <=%d instrucciones: %d ===" % (LIMIT, len(near)))
    for name, cpath, mode, ro, mo in near:
        print("  %-34s (%s)" % (name, mode))
        print("        ROM  : %s" % (ro if ro else "-"))
        print("        mias : %s" % (mo if mo else "-"))


if __name__ == "__main__":
    main()
