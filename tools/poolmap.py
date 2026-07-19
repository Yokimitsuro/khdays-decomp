#!/usr/bin/env python3
"""Desensambla una funcion ANOTANDO a que simbolo apunta cada carga pc-relativa.

    python tools/poolmap.py func_ovNNN_ADDR

Modo ARM/THUMB automatico desde symbols.txt. Cada `ldr rX,[pc,#N]` sale con el offset del pool
al que apunta y, si hay reloc en ese offset, con el simbolo.

POR QUE (2026-07-19): en func_ov188_020cee00 supuse que dos `ldr [pc]` distintos cargaban dos
simbolos distintos. Apuntaban a **la misma palabra**, y estuve cuatro compilaciones persiguiendo
un falso problema de "orden del pool" cuando lo que hacia mal era pasar dos tablas donde el
original pasa una. Mapear esto ANTES de escribir la primera linea de C cuesta un comando.

Tambien marca las palabras del pool que NO carga nadie: si sobra una y el flujo de instrucciones
ya casa, revisa los limites del simbolo (mwcc comparte pools entre funciones vecinas).
"""
import glob
import json
import os
import re
import sys

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def mode_of(name):
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s.*kind:function\((arm|thumb)", ln)
            if m and m.group(1) == name:
                return m.group(2)
    return "arm"


def main():
    if len(sys.argv) != 2:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    if name not in IDX:
        raise SystemExit("no esta en func_index: " + name)
    e = IDX[name]
    thumb = mode_of(name) == "thumb"
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    rel = {o: s for o, s in e["relocs"]}
    code = bytes.fromhex(e["hex"])
    base = int(name[-8:], 16)

    print("%s  (%s, %d bytes)" % (name, "thumb" if thumb else "arm", e["size"]))
    used = set()
    lines = []
    off = 0
    for i in md.disasm(code, base):
        tag = ""
        if rel.get(off):
            tag = "   ; -> %s" % rel[off]
        m = re.search(r"\[pc, #(0x[0-9a-f]+|\d+)\]", i.op_str)
        if m and i.mnemonic.startswith("ldr"):
            n = int(m.group(1), 0)
            # ARM: PC = insn + 8. THUMB: PC = (insn + 4) alineado a 4.
            pc = (off + 8) if not thumb else ((off + 4) & ~3)
            t = pc + n
            used.add(t)
            word = int.from_bytes(code[t:t + 4], "little") if t + 4 <= len(code) else None
            sym = rel.get(t)
            tag = "   ; pool %s = %s" % (hex(t), sym if sym else hex(word) if word is not None else "?")
        lines.append("  %04x  %-8s %-32s%s" % (off, i.mnemonic, i.op_str, tag))
        off += i.size
    print("\n".join(lines))

    # palabras del pool que nadie carga
    pool_start = min(used) if used else len(code)
    orphans = [o for o in range(pool_start, len(code), 4) if o not in used]
    if orphans:
        print("\n⚠ palabras del pool que NADIE carga: %s" %
              ", ".join("%s (%s)" % (hex(o), rel.get(o) or hex(int.from_bytes(code[o:o+4], "little")))
                        for o in orphans))
        print("  Si el flujo de instrucciones ya casa, revisa los limites del simbolo:")
        print("  mwcc comparte el pool entre funciones vecinas.")


if __name__ == "__main__":
    main()
