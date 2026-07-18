#!/usr/bin/env python3
"""Distancia REAL de uno o varios .c candidatos al original: bytes distintos tras enmascarar relocs.

    python tools/bytedist.py <func_name> a.c b.c c.c ...

Imprime una linea por fichero, ordenadas de mejor a peor, y marca la ganadora.

POR QUE (2026-07-18): `verify_idx` imprime el offset del PRIMER byte distinto, y eso NO es una
distancia -- una sola eleccion temprana de registro lo desplaza mientras el resto casa. Caso real:
en func_ov141_020cd1dc mover `v[1] = 0;` detras de dos lecturas paso de **37 a 7 bytes distintos**,
y por offset habria parecido irrelevante. En func_ov141_020cd2b0 el offset dijo que una variante
mejoraba (0x38 -> 0x21) cuando en realidad empeoraba 4x (8 -> 36 bytes).

Usalo siempre que compares dos formas candidatas, y sobre todo para barrer varias de una tacada.
Modo ARM/THUMB automatico desde symbols.txt.
"""
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from match import text_relocs, FLAGS

IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
MW = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC = os.path.join(ROOT, "tools", "mwccarm", "license.dat")


def mode_of(name):
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s", ln)
            if m and m.group(1) == name and "function(" in ln:
                return "thumb" if "function(thumb" in ln else "arm"
    return "arm"


def distance(cpath, name, thumb):
    o = cpath + ".o"
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = FLAGS + (["-thumb"] if thumb else [])
    r = subprocess.run([MW, "-c", *flags, "-o", o, cpath],
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        return (10 ** 6, "compile-fail")
    try:
        mine, mr = text_relocs(o)
    except Exception:
        return (10 ** 6, "obj-fail")
    e = IDX[name]
    orig = bytearray.fromhex(e["hex"])
    if len(mine) != len(orig):
        d = len(mine) - len(orig)
        return (10 ** 5 + abs(d), "size %+d" % d)
    orel = {a: b for a, b in e["relocs"]}
    mrel = {a: n for a, (n, _t) in mr.items()}
    m, ob = bytearray(mine), bytearray(orig)
    for a in set(mrel) | set(orel):
        for k in range(4):
            if a + k < len(ob):
                m[a + k] = 0
                ob[a + k] = 0
    n = sum(1 for x, y in zip(m, ob) if x != y)
    if n == 0 and mrel == orel:
        return (0, "MATCH")
    if n == 0:
        return (1, "relocs difieren")
    return (n, "%d bytes" % n)


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    if name not in IDX:
        raise SystemExit("no esta en func_index: " + name)
    thumb = mode_of(name) == "thumb"
    rows = []
    for cp in sys.argv[2:]:
        rows.append((distance(cp, name, thumb), cp))
    rows.sort()
    print("%s (%s)" % (name, "thumb" if thumb else "arm"))
    for (score, label), cp in rows:
        mark = "  <== MEJOR" if (score, label) == rows[0][0] else ""
        print("  %-46s %s%s" % (cp, label, mark))


if __name__ == "__main__":
    main()
