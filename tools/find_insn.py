#!/usr/bin/env python3
"""Busca una instruccion (o secuencia) en las funciones YA CASADAS y te dice en que .c salio.

    python tools/find_insn.py 'ldr r\\d+, \\[r\\d+\\], #'          # regex sobre una instruccion
    python tools/find_insn.py --seq 'ldrh' 'ldrh' 'strh'          # secuencia consecutiva
    python tools/find_insn.py 'umull' --limit 5

POR QUE EXISTE (2026-07-18): necesitaba un `ldr r0,[r4],#0x18` post-indexado, escribi SIETE
formas C candidatas, las compile todas y ninguna lo emitia -- con la regex validada contra la
ROM, asi que el negativo era real. El metodo era el error: **175 funciones ya casadas contienen
post-indexados**, y una tenia el paso exacto, con un comentario explicando la forma. La respuesta
llevaba en el arbol desde antes.

Regla: cuando necesites una instruccion que no sabes producir, greppea el corpus casado ANTES de
hacer experimentos de compilacion. Son 12.000+ funciones de C bueno conocido.

⚠ El pool literal al final de cada funcion se desensambla como instrucciones basura: filtra por
registros normales o ignora los aciertos cerca del final. Modo ARM/THUMB leido de symbols.txt.
"""
import glob
import json
import os
import re
import sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))


def load_modes():
    m = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            g = re.match(r"\s*(\S+)\s", ln)
            if g and "function(" in ln:
                m[g.group(1)] = "thumb" if "function(thumb" in ln else "arm"
    return m


def matched_sources():
    """name -> path, contando SOLO C real (ni asm_stubs/ ni nonmatching/)"""
    out = {}
    for pat in ("src/**/*.c", "libs/**/*.c"):
        for f in glob.glob(os.path.join(ROOT, pat), recursive=True):
            g = f.replace(os.sep, "/")
            if "/asm_stubs/" in g or "/nonmatching/" in g:
                continue
            out[os.path.basename(g)[:-2]] = g
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        raise SystemExit(__doc__)
    seq_mode = "--seq" in sys.argv
    limit = 20
    for a in sys.argv[1:]:
        if a.startswith("--limit"):
            limit = int(a.split("=")[1]) if "=" in a else 20
    pats = [re.compile(a) for a in args]
    modes = load_modes()
    srcs = matched_sources()

    hits = []
    for name, path in sorted(srcs.items()):
        e = IDX.get(name)
        if not e:
            continue
        md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if modes.get(name) == "thumb" else CS_MODE_ARM)
        try:
            ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
        except Exception:
            continue
        if seq_mode:
            for k in range(len(ins) - len(pats) + 1):
                if all(p.search(ins[k + j]) for j, p in enumerate(pats)):
                    hits.append((name, path, " ; ".join(ins[k:k + len(pats)])))
                    break
        else:
            for s in ins:
                if pats[0].search(s):
                    hits.append((name, path, s))
                    break

    print("funciones casadas que contienen el patron: %d" % len(hits))
    for name, path, s in hits[:limit]:
        print("  %-28s %-52s %s" % (name, s, path.replace(ROOT.replace(os.sep, "/") + "/", "")))
    if len(hits) > limit:
        print("  ... (%d mas; usa --limit=N)" % (len(hits) - limit))


if __name__ == "__main__":
    main()
