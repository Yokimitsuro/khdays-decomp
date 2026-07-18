#!/usr/bin/env python3
"""Porta un .c ya casado a otra funcion de la MISMA FORMA (misma secuencia de mnemonicos).

    python tools/port_template.py <plantilla> <candidata> [--write]
    python tools/port_template.py --all [--write]      # barre todo el ranking de nearfam

Como las dos funciones tienen instruccion por instruccion el mismo mnemonico, las diferencias
son solo (a) los simbolos de los relocs y (b) algunos inmediatos. Este script las empareja por
POSICION y aplica las sustituciones al texto del .c de la plantilla.

Cada resultado se verifica con verify_idx (ARM y THUMB) y **solo se escribe si casa**. Los que
no casan se reportan; un fallo aqui suele significar que el inmediato aparecia en dos papeles
distintos y la sustitucion textual fue ambigua -- en ese caso, edicion a mano.

POR QUE (2026-07-18): la familia d15c dio 68 matches con un generador hecho a medida. Escribir
uno por forma no escala; esto lo hace para cualquiera de las ~125 formas que `nearfam.py` lista.
"""
import glob
import json
import os
import re
import subprocess
import sys
from collections import defaultdict

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
MD = {False: Cs(CS_ARCH_ARM, CS_MODE_ARM), True: Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
OUT = os.path.join(ROOT, "build", "try", "port")


def modes():
    out = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s.*kind:function\((arm|thumb)", ln)
            if m:
                out[m.group(1)] = m.group(2)
    return out


MODE = modes()


def dis(name):
    e = IDX[name]
    thumb = MODE.get(name) == "thumb"
    return list(MD[thumb].disasm(bytes.fromhex(e["hex"]), int(name[-8:], 16))), e, thumb


def imms(op):
    return [int(m, 0) for m in re.findall(r"#(-?(?:0x)?[0-9a-fA-F]+)", op)]


def build_map(tpl, cand):
    """(subs_simbolos, subs_inmediatos) o None si las formas no encajan."""
    ti, te, _ = dis(tpl)
    ci, ce, _ = dis(cand)
    if len(ti) != len(ci):
        return None
    if [i.mnemonic for i in ti] != [i.mnemonic for i in ci]:
        return None

    sym = {}
    trel, crel = dict(te["relocs"]), dict(ce["relocs"])
    if sorted(trel) != sorted(crel):
        return None
    for off in trel:
        if trel[off] != crel[off]:
            sym[trel[off]] = crel[off]

    val = {}
    for a, b in zip(ti, ci):
        ia, ib = imms(a.op_str), imms(b.op_str)
        if len(ia) != len(ib):
            return None
        for x, y in zip(ia, ib):
            if x != y:
                # un mismo valor no puede mapear a dos distintos: seria ambiguo
                if val.get(x, y) != y:
                    return None
                val[x] = y
    return sym, val


def render(tpl, cand, sym, val):
    src = None
    for sub in ("auto", "calls"):
        for p in glob.glob(os.path.join(ROOT, "src", "**", sub, tpl + ".c"), recursive=True):
            if "asm_stubs" not in p.replace("\\", "/").split("/"):
                src = p
    if src is None:
        return None
    s = open(src, encoding="utf-8").read()

    # 1) simbolos (mas largos primero, para no romper prefijos comunes)
    for a in sorted(sym, key=len, reverse=True):
        s = re.sub(r"\b%s\b" % re.escape(a), sym[a], s)
    # 2) el nombre de la funcion
    s = re.sub(r"\b%s\b" % re.escape(tpl), cand, s)
    # 3) inmediatos, en las dos grafias que usamos en el arbol
    for a in sorted(val, key=lambda v: -abs(v)):
        b = val[a]
        s = re.sub(r"\b0x0*%x\b" % a, "0x%x" % b, s, flags=re.I)
        if 0 <= a <= 4096:
            s = re.sub(r"(?<![\w.])%d(?![\w.])" % a, str(b), s)
    return s


def try_one(tpl, cand, write):
    m = build_map(tpl, cand)
    if m is None:
        return "forma/relocs no encajan"
    s = render(tpl, cand, *m)
    if s is None:
        return "no encuentro el .c de la plantilla"
    os.makedirs(OUT, exist_ok=True)
    p = os.path.join(OUT, cand + ".c")
    open(p, "w", newline="\n", encoding="utf-8").write(s)
    for extra in ([], ["--thumb"]):
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify_idx.py"),
                            p, cand] + extra, capture_output=True, text=True, cwd=ROOT)
        if "MATCH" in r.stdout:
            if write:
                ov = re.match(r"func_(ov\d+)_", cand)
                dst = os.path.join(ROOT, "src", "overlays", ov.group(1), "calls",
                                   cand + ".c") if ov else os.path.join(
                    ROOT, "src", "calls", cand + ".c")
                if not os.path.exists(dst):
                    os.makedirs(os.path.dirname(dst), exist_ok=True)
                    open(dst, "w", newline="\n", encoding="utf-8").write(s)
            return "MATCH"
    return "DIFIERE"


def all_shapes():
    """Reusa la agrupacion de nearfam sin reimplementarla."""
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import nearfam
    done = nearfam.matched_paths()
    skip = nearfam.parked()
    buckets = defaultdict(lambda: {"tpl": [], "todo": []})
    for name, e in IDX.items():
        mode = MODE.get(name)
        if mode is None:
            continue
        s = nearfam.shape(name, e, mode == "thumb")
        if s is None:
            continue
        b = buckets[s]
        (b["tpl"] if name in done else b["todo"]).append(name)
    out = []
    for b in buckets.values():
        todo = [n for n in b["todo"] if n not in skip]
        if b["tpl"] and todo:
            out.append((b["tpl"], todo))
    out.sort(key=lambda r: -len(r[1]))
    return out


def main():
    write = "--write" in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith("--")]

    if "--all" in sys.argv:
        tot = defaultdict(int)
        for tpls, todo in all_shapes():
            for cand in todo:
                res = "sin plantilla util"
                for tpl in tpls:
                    res = try_one(tpl, cand, write)
                    if res == "MATCH":
                        break
                tot[res] += 1
                if res == "MATCH":
                    print("  MATCH   %-28s <- %s" % (cand, tpl))
        print("\n" + "  ".join("%s=%d" % kv for kv in sorted(tot.items())))
        return

    if len(args) != 2:
        raise SystemExit(__doc__)
    print(try_one(args[0], args[1], write))


if __name__ == "__main__":
    main()
