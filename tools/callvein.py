#!/usr/bin/env python3
"""Agrupa las funciones SIN HACER por el CALLEE que comparten.

    python tools/callvein.py [n] [--min-size N] [--max-size N]
    python tools/callvein.py <symbol>        # lista los miembros de esa veta

POR QUE (2026-07-19): la familia de destructores de actor (11 miembros, 64-212 B, 11/11 casada en
una tanda) no la encuentra `nearfam.py` NI `dedupprop.py`. La primera agrupa por secuencia de
mnemonicos y estos miembros tienen bucles y llamadas distintas; la segunda pide bytes identicos.
Lo unico que comparten es que **todos terminan llamando al mismo destructor base**
(`func_ov107_020c68ec`).

Esa es la idea: un callee poco frecuente pero compartido por muchas funciones sin hacer marca una
FAMILIA SEMANTICA -- el mismo patron escrito a mano N veces por el mismo programador. Una vez
entiendes la plantilla, los demas miembros salen leyendo offsets del desensamblado.

El ranking penaliza los callees ubicuos (malloc, memcpy, los helpers de 0203xxxx que llama todo el
mundo): puntua `sin_hacer / (sin_hacer + ya_casadas)`, asi que un simbolo que aparece en 400
funciones ya hechas no sube aunque tenga 30 pendientes.
"""
import glob
import json
import os
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def done_names():
    out = set()
    for sub in ("auto", "calls", "nonmatching"):
        for p in glob.glob(os.path.join(ROOT, "src", "**", sub, "*.c"), recursive=True):
            out.add(os.path.basename(p)[:-2])
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    def opt(k, d):
        return int(sys.argv[sys.argv.index(k) + 1]) if k in sys.argv else d
    lo, hi = opt("--min-size", 40), opt("--max-size", 400)
    done = done_names()

    todo = defaultdict(list)   # symbol -> [unmatched funcs]
    seen = defaultdict(int)    # symbol -> matched funcs that call it
    for n, e in IDX.items():
        syms = set(s for _, s in e["relocs"])
        if n in done:
            for s in syms:
                seen[s] += 1
        elif lo <= e["size"] <= hi:
            for s in syms:
                todo[s].append(n)

    if args and not args[0].isdigit():
        s = args[0]
        members = sorted(todo.get(s, []), key=lambda n: IDX[n]["size"])
        print("%s: %d sin hacer, %d ya casadas" % (s, len(members), seen.get(s, 0)))
        for n in members:
            print("  %4d B  %2d rel  %s" % (IDX[n]["size"], len(IDX[n]["relocs"]), n))
        return

    top = int(args[0]) if args else 25
    rows = []
    for s, members in todo.items():
        if len(members) < 3:
            continue
        # Pureza: que fraccion de todo lo que llama a este simbolo sigue sin hacer.
        purity = len(members) / float(len(members) + seen.get(s, 0))
        rows.append((len(members) * purity, len(members), seen.get(s, 0), s))
    rows.sort(reverse=True)

    print("vetas por callee compartido (%d..%d B) -- score = sin_hacer * pureza" % (lo, hi))
    for score, n, m, s in rows[:top]:
        print("  %6.1f  %3d sin hacer  %4d casadas  %s" % (score, n, m, s))


if __name__ == "__main__":
    main()
