#!/usr/bin/env python3
"""Genera la familia de 16 arranques de overlay (cabeza func_ov038_020b327c).

    python tools/gen_ov038_boot.py [--write]

Los 16 miembros son la MISMA funcion con otros simbolos: mismo tamaño, mismos inmediatos,
mismos offsets de pool. Basta con mapear pool-offset -> simbolo entre la plantilla y la
candidata y sustituir en el texto.

POR QUE no vale `port_template.py` aqui: su mapa de inmediatos empareja por POSICION de
instruccion y el .c tiene el mismo literal (0x514, 0x664, ...) en varios papeles, asi que una
sustitucion textual ambigua rompia 9 de los 15 gemelos. Mapear por el POOL es exacto: cada
palabra del pool tiene un unico simbolo.
"""
import io
import json
import os
import re
import subprocess
import sys

from capstone import CS_ARCH_ARM, CS_MODE_THUMB, Cs

MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

# Offsets de los tres `movs` cuyo inmediato cambia de un miembro a otro. Todos los miembros son
# instruccion por instruccion identicos, asi que el offset identifica la instruccion sin
# ambiguedad -- y a diferencia del emparejamiento por posicion de port_template.py, aqui se sabe
# QUE literal del fuente toca cada uno.
VARY = {0x0e: "params.c", 0x24: "slotsize", 0x2e: "params.b"}


def handle_offsets(name):
    """Los cuatro offsets donde se guardan los handles de hueso, en orden.

    Varian de un miembro a otro (ov042 escribe en 0x514 en vez de 0x518) y eso cambia el TAMAÑO
    de la funcion: 0x514 ya esta en el pool para el bucle, asi que reusarlo ahorra una palabra.
    Por eso cuatro miembros salian con "offsets de reloc distintos" -- no era otro simbolo, era
    otro literal. Se leen del desensamblado: cada `str r0,[r4,r1]` va precedido de la carga de
    r1, o del pool o de un movs+lsls.
    """
    code = bytes.fromhex(IDX[name]["hex"])
    rel = relocs(name)
    ins = list(MD.disasm(code, 0))
    offs = []
    pend = None
    movs = None
    off = 0
    pos = []
    for i in ins:
        pos.append((off, i)); off += i.size
    for k, (o, i) in enumerate(pos):
        if i.mnemonic == "movs" and i.op_str.startswith("r1, #"):
            movs = int(i.op_str.split("#")[1], 0)
        elif i.mnemonic == "lsls" and i.op_str.startswith("r1, r1, #") and movs is not None:
            pend = movs << int(i.op_str.split("#")[1], 0)
        elif i.mnemonic == "ldr" and i.op_str.startswith("r1, [pc"):
            t = (o + 4 & ~3) + int(i.op_str.split("#")[1].rstrip("]"), 0)
            if t not in rel:
                pend = int.from_bytes(code[t:t + 4], "little")
        elif i.mnemonic == "str" and i.op_str == "r0, [r4, r1]" and pend is not None:
            offs.append(pend); pend = None
    return offs


def imms_at(name):
    code = bytes.fromhex(IDX[name]["hex"])
    out = {}
    off = 0
    for i in MD.disasm(code, 0):
        if off in VARY and i.mnemonic == "movs":
            out[VARY[off]] = int(i.op_str.split("#")[1], 0)
        off += i.size
    return out

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
TPL = "func_ov038_020b327c"
TPL_C = os.path.join(ROOT, "src", "overlays", "ov038", "calls", TPL + ".c")
MEMBERS = ["func_ov040_020b327c", "func_ov041_020b3290", "func_ov042_020b327c",
           "func_ov057_020b5a7c", "func_ov059_020b5a7c", "func_ov060_020b5a90",
           "func_ov061_020b5a7c", "func_ov077_020b815c", "func_ov079_020b815c",
           "func_ov080_020b8170", "func_ov081_020b815c", "func_ov094_020ba81c",
           "func_ov096_020ba81c", "func_ov097_020ba830", "func_ov098_020ba81c"]


def relocs(name):
    return {o: s for o, s in IDX[name]["relocs"]}


def main():
    write = "--write" in sys.argv
    tpl_rel = relocs(TPL)
    src = io.open(TPL_C, encoding="utf-8").read()
    ok = bad = 0
    for cand in MEMBERS:
        if cand not in IDX:
            print("  %-24s no esta en el indice" % cand)
            continue
        crel = relocs(cand)
        # ⚠ Emparejar por ORDEN, no por offset. Los miembros que reusan una palabra del pool
        # (ov042 escribe el handle en 0x514, que ya estaba) tienen el pool desplazado, asi que
        # exigir los mismos offsets los rechazaba aunque la secuencia de simbolos sea la misma.
        ts = [tpl_rel[o] for o in sorted(tpl_rel)]
        cs = [crel[o] for o in sorted(crel)]
        if len(ts) != len(cs):
            print("  %-24s %d relocs vs %d" % (cand, len(ts), len(cs)))
            bad += 1
            continue
        sub = {a: b for a, b in zip(ts, cs) if a != b}
        tv, cv = imms_at(TPL), imms_at(cand)
        s = src
        if tv.get("slotsize") != cv.get("slotsize"):
            s = s.replace("*(int *)(obj + 0xc) = %d;" % tv["slotsize"],
                          "*(int *)(obj + 0xc) = %d;" % cv["slotsize"])
        if tv.get("params.b") != cv.get("params.b"):
            s = s.replace("params.b = 0x%x << 8;" % tv["params.b"],
                          "params.b = 0x%x << 8;" % cv["params.b"])
        th, ch = handle_offsets(TPL), handle_offsets(cand)
        if len(th) == len(ch) == 4:
            for a, b in zip(th, ch):
                if a != b:
                    s = s.replace("*(int *)(obj + 0x%x) = b != 0" % a,
                                  "*(int *)(obj + 0x%x) = b != 0" % b)
        if tv.get("params.c") != cv.get("params.c"):
            s = s.replace("params.c = %d << 8;" % tv["params.c"],
                          "params.c = %d << 8;" % cv["params.c"])
        for a in sorted(sub, key=len, reverse=True):
            s = re.sub(r"\b%s\b" % re.escape(a), sub[a], s)
        s = re.sub(r"\b%s\b" % re.escape(TPL), cand, s)
        out = os.path.join(ROOT, "build", "try", "boot_" + cand + ".c")
        io.open(out, "w", encoding="utf-8", newline="\n").write(s)
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify_idx.py"),
                            out, cand, "--thumb"], capture_output=True, text=True, cwd=ROOT)
        if "MATCH" in r.stdout:
            ok += 1
            print("  %-24s MATCH" % cand)
            if write:
                ov = re.match(r"func_(ov\d+)_", cand).group(1)
                dst = os.path.join(ROOT, "src", "overlays", ov, "calls", cand + ".c")
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                io.open(dst, "w", encoding="utf-8", newline="\n").write(s)
        else:
            bad += 1
            print("  %-24s DIFIERE" % cand)
    print("MATCH=%d  DIFIERE=%d" % (ok, bad))


if __name__ == "__main__":
    main()
