#!/usr/bin/env python3
"""Compila un .c con TODAS las versiones de mwccarm de tools/mwccarm/ y mide contra el ROM.

    python tools/allcc.py <fichero.c> <func_name> [--thumb]

POR QUE (2026-07-19): cuando un residuo es puro reparto de registros y la busqueda exhaustiva
sobre el FUENTE se agota (ordenes de declaracion, formas del bucle, tipos, aridad), lo unico que
queda por variar es el compilador. El arbol usa 3.0/patch4, pero tenemos la coleccion entera;
si alguna build reproduce el reparto del ROM, el empate no era un empate.

Ojo: un acierto aqui NO autoriza a cambiar la build por defecto del arbol -- se anota en
config/arm9/file_compilers.json para ese fichero, que es el mecanismo que ya existe.
"""
import glob
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from match import FLAGS, LIC, text_relocs   # noqa: E402  (mismos flags que el arbol)


def main():
    cpath, name = sys.argv[1], sys.argv[2]
    thumb = "--thumb" in sys.argv
    e = json.load(open(os.path.join(ROOT, "build", "func_index.json")))[name]
    orig = bytes.fromhex(e["hex"])
    mask = set()
    for o, s in e["relocs"]:
        mask.update(range(o, o + 4))

    out = os.path.join(ROOT, "build", "try", "allcc.o")
    ccs = sorted(glob.glob(os.path.join(ROOT, "tools", "mwccarm", "**", "mwccarm.exe"),
                           recursive=True))
    env = dict(os.environ)
    env["LM_LICENSE_FILE"] = LIC
    print("%d compiladores" % len(ccs))
    for cc in ccs:
        tag = os.path.relpath(os.path.dirname(cc), os.path.join(ROOT, "tools", "mwccarm"))
        cmd = [cc, "-c"] + FLAGS + (["-thumb"] if thumb else []) + ["-o", out, cpath]
        r = subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=ROOT)
        if r.returncode != 0 or not os.path.exists(out):
            print("  %-24s no compila" % tag)
            continue
        try:
            mine, _ = text_relocs(out)
        except Exception:
            mine = None
        if mine is None:
            print("  %-24s sin .text" % tag)
            continue
        if len(mine) != len(orig):
            print("  %-24s tamano %+d" % (tag, len(mine) - len(orig)))
            continue
        d = sum(1 for i, (a, b) in enumerate(zip(orig, mine)) if a != b and i not in mask)
        print("  %-24s %s" % (tag, "MATCH" if d == 0 else "%d bytes" % d))
        try:
            os.remove(out)
        except OSError:
            pass


if __name__ == "__main__":
    main()
