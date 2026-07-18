#!/usr/bin/env python3
"""Elige la siguiente CABEZA DE FAMILIA que atacar entre las funciones sin hacer.

    python tools/pick_family.py [N]        # top N cabezas (por defecto 12)
    python tools/pick_family.py --all      # incluye las descartadas, con el motivo

Agrupa las funciones sin hacer por hex enmascarado (reloc-agnostico) y aplica los tres
filtros que el 2026-07-18 demostraron valer mas que cualquier heuristica de tamano:

 1. **>= 4 miembros.** Un analisis paga toda la familia via `dedupprop --write`.
 2. **La forma NO puede coincidir con un fichero de `nonmatching/`.** Si coincide, el
    empate ya esta diagnosticado y atacarla es repetirlo. De 8 cabezas candidatas
    miradas a mano ese dia, 6 cayeron por aqui.
 3. **La cabeza NO puede tener un salto hacia atras** (bucle). Un bucle trae reduccion
    de fuerza (mwcc convierte el indice en puntero caminante) y relecturas que fusiona
    por CSE -- dos clases de empate conocidas, y aparecen JUNTAS. Marcador de ese dia:
    las dos cabezas rectas casaron (12 y 6 funciones), las dos con bucle se parkearon.

Modo ARM/THUMB leido de symbols.txt, nunca asumido.
"""
import glob
import json
import os
import re
import sys
from collections import defaultdict
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
N = 12
for a in sys.argv[1:]:
    if a.isdigit():
        N = int(a)
SHOW_ALL = "--all" in sys.argv


def masked(e):
    b = bytearray.fromhex(e["hex"])
    for off, _s in e["relocs"]:
        for i in range(4):
            if off + i < len(b):
                b[off + i] = 0
    return bytes(b).hex()


def load_modes():
    m = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            g = re.match(r"\s*(\S+)\s", ln)
            if g and "function(" in ln:
                m[g.group(1)] = "thumb" if "function(thumb" in ln else "arm"
    return m


MODES = load_modes()


def has_loop(name):
    e = IDX[name]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if MODES.get(name) == "thumb" else CS_MODE_ARM)
    for i in md.disasm(bytes.fromhex(e["hex"]), 0):
        mn = i.mnemonic
        if mn.startswith("b") and not mn.startswith(("bl", "bx", "bic")):
            m = re.match(r"^#(?:0x)?([0-9a-fA-F]+)$", i.op_str.strip())
            if m and int(m.group(1), 16) < i.address:
                return True
    return False


def main():
    done, parked = set(), set()
    for pat in ("src/**/*.c", "libs/**/*.c"):
        for f in glob.glob(os.path.join(ROOT, pat), recursive=True):
            g = f.replace(os.sep, "/")
            if "/asm_stubs/" in g:
                continue
            done.add(os.path.basename(g)[:-2])
    for pat in ("src/**/nonmatching/*.c", "libs/**/nonmatching/*.c"):
        for f in glob.glob(os.path.join(ROOT, pat), recursive=True):
            n = os.path.basename(f.replace(os.sep, "/"))[:-2]
            if n in IDX:
                parked.add(masked(IDX[n]))

    groups = defaultdict(list)
    for n, e in IDX.items():
        if n in done or not (60 <= e["size"] <= 400):
            continue
        groups[masked(e)].append(n)

    fams = [(len(v), IDX[sorted(v)[0]]["size"], sorted(v)[0], k)
            for k, v in groups.items() if len(v) >= 4]
    fams.sort(reverse=True)

    good, skipped = [], []
    for cnt, sz, rep, key in fams:
        if key in parked:
            skipped.append((cnt, sz, rep, "forma YA PARKEADA"))
        elif has_loop(rep):
            skipped.append((cnt, sz, rep, "tiene bucle"))
        else:
            good.append((cnt, sz, rep))

    print("familias >=4 miembros: %d  (cubren %d funciones)"
          % (len(fams), sum(f[0] for f in fams)))
    print("descartadas: %d  |  ATACABLES: %d (cubren %d)"
          % (len(skipped), len(good), sum(g[0] for g in good)))
    print()
    print("=== siguientes cabezas a atacar ===")
    for cnt, sz, rep in good[:N]:
        print("  %2d miembros %4dB  %-28s (%s)" % (cnt, sz, rep, MODES.get(rep, "?")))
    if SHOW_ALL:
        print()
        print("=== descartadas ===")
        for cnt, sz, rep, why in skipped[:40]:
            print("  %2d miembros %4dB  %-28s %s" % (cnt, sz, rep, why))


if __name__ == "__main__":
    main()
