#!/usr/bin/env python3
"""Como tools/park_templates.py pero con DISTANCIA DE EDICION en vez de igualdad exacta.

       python tools/park_templates_fuzzy.py [max_dist]     # por defecto 3

   Por que: el 2026-07-22, func_ov083_020b9794 resulto ser el octavo miembro de la
   familia BindRig y el escaneo exacto NO lo agrupo con los otros siete, porque su
   bloque de rig vive en el objeto en vez de detras de una global -- le falta la carga
   del pool y la secuencia difiere en una instruccion. Una familia puede DERIVAR una o
   dos instrucciones y seguir siendo la misma funcion.

   ⚠ Igual que en la version exacta, las plantillas de src/**/asm_stubs/ se excluyen:
   tienen los mnemonicos correctos por construccion y no son C.
"""
import os, re, sys, json, glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load():
    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    mode = {}
    for sf in glob.glob(os.path.join(ROOT, 'config', 'arm9', '**', 'symbols.txt'), recursive=True):
        for m in re.finditer(r'^(func_\w+) kind:function\((arm|thumb)', open(sf).read(), re.M):
            mode[m.group(1)] = m.group(2)
    return idx, mode


def sig(idx, mode, name):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode.get(name) == 'thumb' else CS_MODE_ARM)
    return tuple(i.mnemonic for i in md.disasm(bytes.fromhex(idx[name]['hex']), 0))


def edit(a, b, cap):
    """Distancia de Levenshtein con corte temprano en `cap`."""
    if abs(len(a) - len(b)) > cap:
        return cap + 1
    prev = list(range(len(b) + 1))
    for i, x in enumerate(a, 1):
        cur = [i] + [0] * len(b)
        best = i
        for j, y in enumerate(b, 1):
            cur[j] = min(prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + (x != y))
            if cur[j] < best:
                best = cur[j]
        if best > cap:
            return cap + 1
        prev = cur
    return prev[-1]


def main():
    cap = int(sys.argv[1]) if len(sys.argv) > 1 else 3
    idx, mode = load()

    templates = {}
    for p in (glob.glob(os.path.join(ROOT, 'src', '**', 'calls', '*.c'), recursive=True) +
              glob.glob(os.path.join(ROOT, 'src', '**', 'auto', '*.c'), recursive=True)):
        if 'asm_stubs' in p.replace(os.sep, '/'):
            continue
        templates[os.path.basename(p)[:-2]] = p

    parked = {os.path.basename(p)[:-2]: p
              for p in glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'),
                                 recursive=True)}

    def sigs(names):
        out = {}
        for n in names:
            if n not in idx:
                continue
            try:
                s = sig(idx, mode, n)
            except Exception:
                continue
            if len(s) >= 8:
                out[n] = s
        return out

    ps = sigs(parked)
    ts = sigs(templates)

    hits = []
    for pn, pv in ps.items():
        best = None
        for tn, tv in ts.items():
            if pn == tn:
                continue
            d = edit(pv, tv, cap)
            if d <= cap and (best is None or d < best[0]):
                best = (d, tn)
                if d == 0:
                    break
        if best:
            hits.append((best[0], len(pv), pn, best[1], templates[best[1]]))

    hits.sort()
    print('%d parks con plantilla a distancia <= %d (de %d aparcados)'
          % (len(hits), cap, len(parked)))
    for d, n, pn, tn, path in hits:
        print('  d=%d %4d instr  %-28s <- %-28s  %s'
              % (d, n, pn, tn, os.path.relpath(path, ROOT)))


if __name__ == '__main__':
    main()
