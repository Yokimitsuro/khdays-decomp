#!/usr/bin/env python3
"""Compara la ARIDAD DECLARADA de cada callee de un park con la que se puede LEER en la
   ROM: cuantos de r0..r3 se escriben de verdad antes del `bl`.

       python tools/park_arity.py            # todos los parks, solo los sospechosos
       python tools/park_arity.py <func>     # detalle de uno

   Por que existe (2026-07-22): tres parks cayeron el mismo dia por esto y ninguno estaba
   archivado como un problema de aridad -- estaban archivados como "necesita un callee-saved
   de mas", "el 5o argumento va a la ranura de r3 empujado" y "presion de registros".
   Un argumento de sobra en un `extern` fuerza a mwcc a mantener vivo un valor que la ROM
   no mantiene, y el sintoma que ves es un registro o un push de mas.

   ⚠ MIRA LAS DOS DIRECCIONES. Declarar de MENOS tambien rompe: `func_ov008_02072d9c`
   estaba declarado con un argumento y toma dos, y el sintoma era un `mov r1,r0` de la ROM
   que parecia "nuestro compilador es mas listo". La prueba estaba en el orden: la ROM emite
   `mov r0,r4` ANTES del store, asi que r1 sigue vivo en el `bl` -- es un argumento.

   ⚠ LAS DOS DIRECCIONES NO VALEN LO MISMO. "de mas" (declarado > escrito) es fiable: un
   registro que la ROM nunca escribe no puede ser un argumento. "DE MENOS" es RUIDOSO --
   el escaneo hacia atras cruza bloques basicos y cuenta escrituras que son de otra cosa
   (veras `OS_RestoreInterrupts declarado 1, la ROM escribe 3`, que es falso). Usalo solo
   como lista de sitios donde MIRAR el orden a mano.

   ⚠ LEE EL RESULTADO COMO UNA PISTA, NO COMO UNA SENTENCIA. Solo dice "la ROM no escribe
   rN antes de esta llamada". Eso puede significar:
     - el callee tiene menos argumentos (el caso interesante), o
     - el argumento se reenvia sin tocar desde un parametro del propio caller.
   Lo segundo se distingue mirando si la llamada esta dentro de un bucle o despues de otra
   llamada: si rN tuviera que sobrevivir a un `bl` y nadie lo salva, no es un argumento.
"""
import os, re, sys, json, glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ARGREGS = ['r0', 'r1', 'r2', 'r3']


def modes():
    m = {}
    for sf in glob.glob(os.path.join(ROOT, 'config', 'arm9', '**', 'symbols.txt'),
                        recursive=True):
        for g in re.finditer(r'^(func_\w+) kind:function\((arm|thumb)', open(sf).read(), re.M):
            m[g.group(1)] = g.group(2)
    return m


def declared_args(src):
    """{callee: n_args} a partir de los `extern` del fichero."""
    out = {}
    for m in re.finditer(r'extern\s+[\w\s\*]+?\b(\w+)\s*\(([^;{]*)\)\s*;', src):
        name, args = m.group(1), m.group(2).strip()
        if args in ('', 'void'):
            out[name] = 0
        else:
            depth, n = 0, 1
            for ch in args:
                if ch in '([':
                    depth += 1
                elif ch in ')]':
                    depth -= 1
                elif ch == ',' and depth == 0:
                    n += 1
            out[name] = n
    return out


def inferred_args(idx, mode, func):
    """{callee: max argumento visto} leyendo la ROM."""
    e = idx[func]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode.get(func) == 'thumb' else CS_MODE_ARM)
    md.detail = True
    ins = list(md.disasm(bytes.fromhex(e['hex']), 0))
    relocs = {off: sym for off, sym in e['relocs']}
    out = {}
    for i, cur in enumerate(ins):
        if not cur.mnemonic.startswith('bl'):
            continue
        sym = relocs.get(cur.address)
        if sym is None:
            continue
        seen = set()
        # hacia atras hasta la llamada anterior o el principio
        for prev in reversed(ins[:i]):
            if prev.mnemonic.startswith('bl') or prev.mnemonic.startswith('bx'):
                break
            ops = prev.op_str.split(',')
            if ops:
                d = ops[0].strip()
                if d in ARGREGS:
                    seen.add(ARGREGS.index(d))
                # str rX, [sp...] = argumento en pila -> hay 5o o mas
                if prev.mnemonic.startswith('str') and '[sp' in prev.op_str:
                    seen.add(4)
        n = (max(seen) + 1) if seen else 0
        out[sym] = max(out.get(sym, 0), n)
    return out


def report(func, path, idx, mode, verbose):
    src = open(path, encoding='utf-8', errors='replace').read()
    dec = declared_args(src)
    inf = inferred_args(idx, mode, func)
    rows = []
    for callee, n_inf in sorted(inf.items()):
        n_dec = dec.get(callee)
        if n_dec is None:
            continue
        if n_dec != n_inf:
            rows.append((callee, n_dec, n_inf))
    if rows or verbose:
        print('%s' % func)
        for callee, n_dec, n_inf in rows:
            flag = 'DE MENOS' if n_dec < n_inf else 'de mas'
            print('    %-32s declarado %d, la ROM escribe %d   (%s)'
                  % (callee, n_dec, n_inf, flag))
        if verbose and not rows:
            print('    (nada sospechoso; %d callees comprobados)' % len(inf))
    return len(rows)


def main():
    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    mode = modes()
    if len(sys.argv) > 1:
        func = sys.argv[1]
        hits = glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', func + '.c'),
                         recursive=True)
        if not hits:
            print('no hay park para', func)
            return
        report(func, hits[0], idx, mode, True)
        return
    total = 0
    for p in sorted(glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'),
                              recursive=True)):
        func = os.path.basename(p)[:-2]
        if func in idx:
            total += report(func, p, idx, mode, False)
    print('\n%d callees cuya aridad declarada no cuadra con la ROM' % total)


if __name__ == '__main__':
    main()
