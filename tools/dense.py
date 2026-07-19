#!/usr/bin/env python3
"""Lista las funciones sin hacer ordenadas por DENSIDAD DE RELOCS.

    python tools/dense.py [n] [--min-size N] [--max-size N] [--thumb|--arm]

POR QUE (2026-07-19): en una funcion donde casi todo son `bl`, los bytes del salto van
enmascarados por el reloc, asi que el ruido de planificacion y de reparto de registros -- que es
lo que bloquea la mayoria de los empates de este proyecto -- **no cuenta**. Solo hay que acertar
el orden de las llamadas y sus argumentos, y eso se lee del desensamblado sin ambiguedad.

Medido el 2026-07-19: con densidad >= 0.45 casaron 11 de 12 al PRIMER intento, frente a ~1 de 6
en las reloc-free del mismo dia. Es la formulacion cuantitativa del consejo de la skill
("prefiere funciones medianas CON llamadas, 4+ relocs").
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from nearfam import matched_paths, parked, modes  # noqa: E402

IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def main():
    args = sys.argv[1:]
    n = 20
    lo, hi = 48, 220
    want = None
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--min-size":
            i += 1; lo = int(args[i])
        elif a == "--max-size":
            i += 1; hi = int(args[i])
        elif a == "--thumb":
            want = "thumb"
        elif a == "--arm":
            want = "arm"
        else:
            n = int(a)
        i += 1

    done, skip, md = matched_paths(), parked(), modes()
    out = []
    for name, e in IDX.items():
        if name in done or name in skip:
            continue
        mode = md.get(name)
        if mode is None or not e["relocs"]:
            continue
        if want and mode != want:
            continue
        if not (lo <= e["size"] <= hi):
            continue
        out.append((len(e["relocs"]) * 4.0 / e["size"], len(e["relocs"]), e["size"], name, mode))
    out.sort(key=lambda x: -x[0])
    print("%d candidatas (%d..%d B%s)" % (len(out), lo, hi, ", " + want if want else ""))
    for d, r, s, name, mode in out[:n]:
        print("  %.2f  %2d relocs %4d B %-5s %s" % (d, r, s, mode, name))


if __name__ == "__main__":
    main()
