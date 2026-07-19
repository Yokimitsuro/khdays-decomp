#!/usr/bin/env python3
"""Encuentra funciones SIN HACER cuya FORMA coincide con una ya casada.

    python tools/nearfam.py                 # ranking de candidatas
    python tools/nearfam.py <func_name>     # que plantilla casada le corresponde

`dedupprop.py` propaga entre gemelas byte-identicas tras enmascarar relocs. Esto va un paso
mas alla: agrupa por la SECUENCIA DE MNEMONICOS (ignorando registros e inmediatos), asi que
encuentra funciones que son la misma plantilla con otras constantes y otros offsets.

POR QUE (2026-07-18): tres de los cuatro matches de la iteracion 41 salieron de reusar un .c
ya casado sustituyendo offsets -- a mano, porque los reconoci de vista al desensamblar. Esto
lo hace de forma exhaustiva. Una plantilla casada suele valer varias familias, no una.

El ranking prioriza:
  - que la plantilla este CASADA (hay un .c en auto/ o calls/ del que copiar), y
  - cuantas funciones sin hacer comparten esa forma (una edicion, N matches).

Uso tipico: coge la primera linea, abre el .c de la plantilla, sustituye offsets/constantes
leyendo el desensamblado de la candidata, y mide con tools/bytedist.py.
"""
import glob
import json
import os
import re
import sys
from collections import defaultdict

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

# Mnemonicos cuyo sufijo condicional NO queremos perder: la condicion es parte de la forma.
_MD = {False: Cs(CS_ARCH_ARM, CS_MODE_ARM), True: Cs(CS_ARCH_ARM, CS_MODE_THUMB)}


def modes():
    """name -> 'arm' | 'thumb' leido de symbols.txt (nunca asumido)."""
    out = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s.*kind:function\((arm|thumb)", ln)
            if m:
                out[m.group(1)] = m.group(2)
    return out


def shape(name, entry, thumb):
    """Firma de forma: los mnemonicos del CODIGO. Sin registros, sin inmediatos y SIN EL POOL.

    ⚠ Lo del pool no es cosmetico. capstone desensambla las palabras literales del final como
    instrucciones basura, y su contenido difiere entre funciones de la misma forma, asi que
    incluirlas **parte familias que deberian estar juntas** y el ranking pierde miembros. El
    inicio del pool = el minimo destino de un `ldr rX,[pc,#N]` (igual que poolmap.py, 2026-07-19).
    """
    try:
        addr = int(name[-8:], 16)
    except ValueError:
        return None
    code = bytes.fromhex(entry["hex"])
    ins = list(_MD[thumb].disasm(code, addr))
    if not ins:
        return None
    pool, off = len(code), 0
    for i in ins:
        m = re.search(r"\[pc, #(0x[0-9a-fA-F]+|\d+)\]", i.op_str)
        if m and i.mnemonic.startswith("ldr"):
            pc = (off + 8) if not thumb else ((off + 4) & ~3)
            pool = min(pool, pc + int(m.group(1), 0))
        off += i.size
    keep, off = [], 0
    for i in ins:
        if off >= pool:
            break
        keep.append(i)
        off += i.size
    ins = keep
    if not ins:
        return None
    # Un puñado de instrucciones no distingue nada; pedimos algo de cuerpo.
    if len(ins) < 8:
        return None
    return " ".join(i.mnemonic for i in ins)


def matched_paths():
    """name -> ruta del .c casado (auto/ o calls/), excluyendo asm_stubs y nonmatching."""
    out = {}
    for sub in ("auto", "calls"):
        # ⚠ `*.c`, NO `func_*.c`. Las funciones ya casadas con nombre de SDK
        # (GXS_LoadBG3Scr_0x..., MI_*, G2S_*) viven en ficheros que no empiezan por `func_`, y
        # filtrarlas las hacia aparecer como PENDIENTES. El 2026-07-19 "descubri" asi una familia
        # de 14 GXS_LoadBG3Scr/Char que llevaba dias entera hecha, y llegue a pisar el .c bueno
        # con uno peor. El indice usa el nombre real del simbolo; el glob tambien debe hacerlo.
        for p in glob.glob(os.path.join(ROOT, "src", "**", sub, "*.c"), recursive=True):
            rel = os.path.relpath(p, ROOT)
            # ⚠ src/**/asm_stubs/calls/ tambien casa el glob, y un stub "casa" trivialmente:
            # contarlo como plantilla hace que el ranking mienta (regla de la skill).
            if "asm_stubs" in rel.replace("\\", "/").split("/"):
                continue
            out[os.path.basename(p)[:-2]] = rel
    return out


def parked():
    return {os.path.basename(p)[:-2]
            for p in glob.glob(os.path.join(ROOT, "src", "**", "nonmatching", "*.c"),
                               recursive=True)}


def main():
    md = modes()
    done = matched_paths()
    skip = parked()

    buckets = defaultdict(lambda: {"tpl": [], "todo": []})
    for name, e in IDX.items():
        mode = md.get(name)
        if mode is None:
            continue
        s = shape(name, e, mode == "thumb")
        if s is None:
            continue
        b = buckets[s]
        (b["tpl"] if name in done else b["todo"]).append(name)

    if len(sys.argv) > 1:
        want = sys.argv[1]
        for s, b in buckets.items():
            if want in b["todo"] or want in b["tpl"]:
                print("forma de %s (%d instrucciones)" % (want, len(s.split())))
                if b["tpl"]:
                    print("  PLANTILLAS CASADAS:")
                    for t in b["tpl"]:
                        print("    %-28s %s" % (t, done[t]))
                else:
                    print("  (ninguna plantilla casada con esta forma)")
                others = [n for n in b["todo"] if n != want]
                if others:
                    print("  otras sin hacer con la misma forma: %d" % len(others))
                    for n in others[:12]:
                        print("    %s" % n)
                return
        raise SystemExit("no encontrada (o forma demasiado corta): " + want)

    rows = []
    for s, b in buckets.items():
        todo = [n for n in b["todo"] if n not in skip]
        if b["tpl"] and todo:
            rows.append((len(todo), len(s.split()), b["tpl"][0], done[b["tpl"][0]], todo))
    rows.sort(key=lambda r: (-r[0], r[1]))

    total = sum(r[0] for r in rows)
    print("formas con plantilla casada Y funciones sin hacer: %d  (cubren %d funciones)"
          % (len(rows), total))
    print("\n=== plantillas mas rentables (1 edicion -> N matches) ===")
    for n, ln, tpl, path, todo in rows[:25]:
        print("  %3d sin hacer  %3d insn  plantilla %-28s %s" % (n, ln, tpl, path))
        print("                 -> %s" % ", ".join(todo[:6]) + (" ..." if len(todo) > 6 else ""))


if __name__ == "__main__":
    main()
