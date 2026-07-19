#!/usr/bin/env python3
"""Compila un .c con TODOS los niveles de optimizacion de mwccarm y mide contra el ROM.

    python tools/allopt.py <fichero.c> <func_name> [--thumb]

POR QUE (2026-07-19): hermana de `allcc.py`. Aquel varia la BUILD del compilador y dejo demostrado
que para la clase A (permutacion de registros) todas las 2.0/3.0 dan el mismo residuo. Lo que
`allcc.py` NO varia son los FLAGS, y la PLANIFICACION de instrucciones -- la clase B del censo de
empates -- es justo lo que cambia entre niveles de optimizacion.

El arbol compila con `-O4,p` (p = optimizar para velocidad). Si un residuo de planificacion cae con
`-O4,s` o `-O3,p`, no era un empate: era un fichero compilado con otros flags, y eso se anota por
fichero igual que la build (ver `config/arm9/file_compilers.json` para el mecanismo equivalente).

Un acierto aqui NO autoriza a cambiar los flags por defecto del arbol.
"""
import os
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import json

from match import LIC, text_relocs  # noqa: E402

MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
BASE = ["-proc", "arm946e", "-interworking", "-lang", "c99",
        "-enum", "int", "-char", "signed", "-inline", "on,noauto",
        "-Cpp_exceptions", "off", "-gccext,on"]

LEVELS = ["-O0", "-O1", "-O2", "-O3", "-O4",
          "-O1,p", "-O2,p", "-O3,p", "-O4,p",
          "-O1,s", "-O2,s", "-O3,s", "-O4,s"]


def masked(a, b, relocs):
    """Distancia byte a byte enmascarando los offsets con reloc."""
    skip = set()
    for off, _ in relocs:
        skip.update(range(off, off + 4))
    return sum(1 for i in range(min(len(a), len(b)))
               if i not in skip and a[i] != b[i])


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    cpath, name = sys.argv[1], sys.argv[2]
    thumb = "--thumb" in sys.argv
    idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
    orig = bytes.fromhex(idx[name]["hex"])
    relocs = idx[name]["relocs"]

    print("%d niveles  (referencia: -O4,p)" % len(LEVELS))
    best = None
    for lvl in LEVELS:
        obj = os.path.join(ROOT, "build", "try", "_opt.o")
        cmd = [MWCC, "-c", lvl] + BASE + (["-thumb"] if thumb else []) + \
              ["-o", obj, cpath]
        env = dict(os.environ, LM_LICENSE_FILE=LIC)
        r = subprocess.run(cmd, capture_output=True, env=env)
        if r.returncode != 0 or not os.path.exists(obj):
            print("  %-8s no compila" % lvl)
            continue
        mine, _ = text_relocs(obj)
        # ⚠ El antivirus mantiene el .o abierto un instante tras compilarlo (mismo fallo que en
        # gen_delinks.py). Reintentar en vez de morir.
        for _try in range(8):
            try:
                os.remove(obj)
                break
            except OSError:
                time.sleep(0.05 * (_try + 1))
        if len(mine) != len(orig):
            print("  %-8s tamano %+d" % (lvl, len(mine) - len(orig)))
            continue
        d = masked(orig, mine, relocs)
        tag = "  <== MATCH" if d == 0 else ""
        print("  %-8s %d bytes%s" % (lvl, d, tag))
        if best is None or d < best[1]:
            best = (lvl, d)
    if best:
        print("\nmejor: %s con %d bytes" % best)


if __name__ == "__main__":
    main()
