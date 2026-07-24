#!/usr/bin/env python3
"""Permuta el ORDEN DE DECLARACION de los locales de una funcion y mide cada permutacion.

    python tools/declperm.py <fichero.c> <func_name> [--thumb] [--max N]

POR QUE (2026-07-22): el orden de declaracion colorea los registros callee-saved, y un residuo
que es solo una permutacion de registros suele caer con la permutacion correcta. Hacerlo a mano
cuesta una iteracion por prueba; con 4-5 locales hay 24-120 ordenes y el barrido tarda segundos.
Cerro func_ov008_02069954 (permutacion 33 de 120).

Detecta el bloque de declaraciones como las lineas consecutivas al principio del cuerpo que
declaran UNA variable cada una y no tienen inicializador. Si tus declaraciones llevan
inicializador, separalas primero (declaracion arriba, asignacion abajo) -- que es justo lo que
hace falta para que la permutacion signifique algo.
"""
import itertools, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

def main():
    cpath, name = sys.argv[1], sys.argv[2]
    thumb = "--thumb" in sys.argv
    cap = 400
    if "--max" in sys.argv:
        cap = int(sys.argv[sys.argv.index("--max") + 1])
    src = open(cpath, encoding="utf-8", errors="replace").read()
    lines = src.splitlines(True)
    # find the function body
    for i, ln in enumerate(lines):
        if re.match(r'^\w[\w \*]*\b' + re.escape(name) + r'\s*\(', ln):
            break
    else:
        raise SystemExit("no encuentro la definicion de " + name)
    j = i
    while '{' not in lines[j]:
        j += 1
    j += 1
    # Collect the leading declaration block. A declaration WITH an initializer is split
    # into a bare declaration plus an assignment; the assignments keep their source order,
    # so only the declaration order is permuted (2026-07-24 -- before this, every park that
    # wrote `int x = 0;` was simply out of the tool's reach, which is most of them).
    decls, inits = [], []
    bare = re.compile(r'^(\s+)([A-Za-z_][\w \*]*?\s+\*?)(\w+)\s*;\s*$')
    withinit = re.compile(r'^(\s+)([A-Za-z_][\w \*]*?\s+\*?)(\w+)\s*=\s*(.+);\s*$')
    while j < len(lines):
        m = bare.match(lines[j])
        if m:
            decls.append('%s%s%s;\n' % (m.group(1), m.group(2), m.group(3)))
            j += 1; continue
        m = withinit.match(lines[j])
        if m and not lines[j].lstrip().startswith(('return', 'if', 'for', 'while', 'do', 'switch')):
            decls.append('%s%s%s;\n' % (m.group(1), m.group(2), m.group(3)))
            inits.append('%s%s = %s;\n' % (m.group(1), m.group(3), m.group(4)))
            j += 1; continue
        break
    if len(decls) < 2:
        raise SystemExit("menos de 2 declaraciones al principio del cuerpo")
    # one SOURCE line was consumed per declaration, whether or not it had an initializer
    head, tail = ''.join(lines[:j - len(decls)]), ''.join(inits) + ''.join(lines[j:])
    orig = bytearray.fromhex(IDX[name]["hex"])
    orel = {o: s for o, s in IDX[name]["relocs"]}
    tmp = os.path.join(ROOT, "build", "try", "_declperm.c")
    os.makedirs(os.path.dirname(tmp), exist_ok=True)
    best = []
    perms = list(itertools.permutations(range(len(decls))))
    if len(perms) > cap:
        print("%d permutaciones, limitando a %d" % (len(perms), cap)); perms = perms[:cap]
    for p in perms:
        open(tmp, "w", encoding="utf-8").write(head + ''.join(decls[k] for k in p) + tail)
        try:
            o = compile_c(tmp, thumb)
        except SystemExit:
            continue
        mine, mrel = text_relocs(o)
        if len(mine) != len(orig):
            continue
        mt, ob = bytearray(mine), bytearray(orig)
        for off in set(mrel) | set(orel):
            for k in range(4):
                if off + k < len(orig): mt[off + k] = 0; ob[off + k] = 0
        d = sum(1 for k in range(len(orig)) if mt[k] != ob[k])
        best.append((d, p))
    best.sort()
    for d, p in best[:5]:
        print("%3d off  ->  %s" % (d, ' '.join(decls[k].strip() for k in p)))
    if best and best[0][0] == 0:
        open(cpath + ".MATCH", "w", encoding="utf-8").write(
            head + ''.join(decls[k] for k in best[0][1]) + tail)
        print("MATCH escrito en", cpath + ".MATCH")

if __name__ == "__main__":
    main()
