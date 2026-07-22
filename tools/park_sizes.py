#!/usr/bin/env python3
"""Compila TODOS los parks de nonmatching/ y ordena por cuanto se desvian del tamano
   de la ROM.

       python tools/park_sizes.py [--all]

   Para que sirve: separa los dos tipos de park, que se atacan de forma distinta.
     delta 0  -> el stream ya es correcto y solo bailan los registros/el orden:
                 barre permutaciones de declaracion (24 compilaciones) antes de
                 tocar nada mas.
     delta !=0 -> falta o sobra codigo: arity del callee, forma del bucle, un cast
                 de mas, un case que no esta escrito. Estructural, no coloreado.

   Sin --all solo lista los que compilan; los que no compilan salen igual al final,
   porque un park que ni compila suele tener un extern podrido y es trabajo facil.
"""
import os, re, sys, json, glob, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import text_relocs, FLAGS

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def modes():
    m = {}
    for sf in glob.glob(os.path.join(ROOT, 'config', 'arm9', '**', 'symbols.txt'),
                        recursive=True):
        for g in re.finditer(r'^(func_\w+) kind:function\((arm|thumb)', open(sf).read(), re.M):
            m[g.group(1)] = g.group(2)
    return m


def main():
    idx = json.load(open(os.path.join(ROOT, 'build', 'func_index.json')))
    mode = modes()
    rows, broken = [], []
    for p in sorted(glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'),
                              recursive=True)):
        n = os.path.basename(p)[:-2]
        if n not in idx:
            continue
        th = mode.get(n) == 'thumb'
        try:
            out = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'verify_idx.py'),
                                  p, n] + (['--thumb'] if th else []),
                                 capture_output=True, text=True, timeout=120).stdout
        except Exception:
            broken.append((n, 'timeout'))
            continue
        if 'MATCH' in out:
            rows.append((0, idx[n]['size'], n, 'MATCH-ALREADY'))
            continue
        g = re.search(r'tamano (\d+) != (\d+)', out)
        if g:
            mine, orig = int(g.group(1)), int(g.group(2))
            rows.append((abs(mine - orig), orig, n, '%+d' % (mine - orig)))
        elif 'byte diff' in out:
            rows.append((0, idx[n]['size'], n, 'same-size'))
        else:
            broken.append((n, out.strip().splitlines()[-1] if out.strip() else 'no-output'))

    rows.sort(key=lambda r: (r[0], r[1]))
    print('%d parks compilados' % len(rows))
    for d, size, n, tag in rows:
        print('  %-12s %4dB  %s' % (tag, size, n))
    if broken:
        print('\n%d NO COMPILAN (extern podrido, arreglo facil):' % len(broken))
        for n, why in broken:
            print('  %-28s %s' % (n, why[:60]))


if __name__ == '__main__':
    main()
