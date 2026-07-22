#!/usr/bin/env python3
"""Empareja cada funcion aparcada en nonmatching/ con una funcion YA MATCHEADA cuya
   secuencia de mnemonicos sea identica -- es decir, una PLANTILLA de la que copiar
   el C cambiando solo inmediatos, offsets y simbolos.

       python tools/park_templates.py                 # lista los pares, mas cortos primero
       python tools/park_templates.py <park>          # diff lado a lado park vs plantilla

   Por que existe: agrupar los parks por hex identico solo encuentra gemelos exactos.
   Muchas familias estan PARAMETRIZADAS -- misma secuencia de instrucciones con otros
   offsets -- y esas no aparecen en el agrupado por hex. El 2026-07-22 esta busqueda
   encontro 97 parks con plantilla existente, sobre 362 aparcados.

   ⚠ Las plantillas de src/**/asm_stubs/ NO valen: no son C real, son envoltorios de
   ensamblador. Se excluyen.
"""
import os, re, sys, json, glob
from collections import defaultdict
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
    e = idx[name]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode.get(name) == 'thumb' else CS_MODE_ARM)
    return tuple(i.mnemonic for i in md.disasm(bytes.fromhex(e['hex']), 0))


def pairs():
    idx, mode = load()

    templates = {}
    for p in glob.glob(os.path.join(ROOT, 'src', '**', 'calls', '*.c'), recursive=True) + \
             glob.glob(os.path.join(ROOT, 'src', '**', 'auto', '*.c'), recursive=True):
        if 'asm_stubs' in p.replace('\\', '/'):
            continue
        templates[os.path.basename(p)[:-2]] = p

    parked = {}
    for p in glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'), recursive=True):
        parked[os.path.basename(p)[:-2]] = p

    by_sig = defaultdict(list)
    for n in parked:
        if n in idx:
            try:
                s = sig(idx, mode, n)
            except Exception:
                continue
            if len(s) >= 6:
                by_sig[s].append(n)

    out = []
    for n, path in templates.items():
        if n not in idx:
            continue
        try:
            s = sig(idx, mode, n)
        except Exception:
            continue
        if s in by_sig:
            for park in by_sig[s]:
                if park != n:
                    out.append((len(s), park, n, path))
    out.sort()
    return idx, mode, out


def show_diff(idx, mode, park, template):
    md_p = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode.get(park) == 'thumb' else CS_MODE_ARM)
    md_t = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode.get(template) == 'thumb' else CS_MODE_ARM)
    a = list(md_t.disasm(bytes.fromhex(idx[template]['hex']), 0))
    b = list(md_p.disasm(bytes.fromhex(idx[park]['hex']), 0))
    print('=== %s (plantilla)  vs  %s (park)' % (template, park))
    for x, y in zip(a, b):
        mark = '' if x.op_str == y.op_str else '   <<'
        print('%-36s | %-36s%s' % (x.mnemonic + ' ' + x.op_str,
                                   y.mnemonic + ' ' + y.op_str, mark))
    print('relocs plantilla:', idx[template]['relocs'])
    print('relocs park     :', idx[park]['relocs'])


def main():
    idx, mode, rows = pairs()
    if len(sys.argv) > 1:
        want = sys.argv[1]
        for _, park, tmpl, path in rows:
            if park == want:
                show_diff(idx, mode, park, tmpl)
                print('\nfuente de la plantilla:', os.path.relpath(path, ROOT))
                return
        print('sin plantilla para', want)
        return

    print('%d parks con plantilla ya matcheada (de %d aparcados)'
          % (len(rows), len(glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'),
                                      recursive=True))))
    for n, park, tmpl, path in rows:
        print('  %3d instr  %-26s <- %-26s  %s'
              % (n, park, tmpl, os.path.relpath(path, ROOT)))


if __name__ == '__main__':
    main()
