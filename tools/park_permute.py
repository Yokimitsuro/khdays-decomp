#!/usr/bin/env python3
"""Barre las PERMUTACIONES DEL ORDEN DE DECLARACION de los locales de un park y
   comprueba si alguna hace match byte-exacto.

       python tools/park_permute.py <func>        # un park concreto
       python tools/park_permute.py --sweep       # todos los parks de tamano exacto

   Por que existe (2026-07-22): mwcc reparte los callee-saved siguiendo el orden en
   que se DECLARAN los locales. `func_ov008_0208b148` tenia el stream de instrucciones
   ya correcto y solo casaba con una de las 24 ordenaciones de sus cuatro locales; el
   park llevaba desde el 18/07 archivado como empate de reduccion de fuerza. Cuando el
   tamano ya coincide y solo bailan los registros, esto son 24 compilaciones y medio
   minuto -- hazlo ANTES de escribir una nota de empate.

   Solo permuta el bloque de declaraciones del principio del cuerpo, y solo si NINGUN
   inicializador menciona a otro de los declarados (asi el reordenado es equivalente:
   los inicializadores se evaluan en orden). Si hay dependencias, no toca el fichero.
"""
import os, re, sys, glob, json, itertools, subprocess, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MAXPERM = 720

DECL = re.compile(
    r'^(\s+)((?:unsigned |signed |const |volatile |register |struct \w+ |union \w+ |'
    r'enum \w+ )*(?:void|char|short|int|long|float|double|u8|u16|u32|s8|s16|s32|'
    r'\w+_t|[A-Z]\w*)\s*\**\s*)(\w+)\s*(=[^;]*)?;\s*$')


def modes():
    m = {}
    for sf in glob.glob(os.path.join(ROOT, 'config', 'arm9', '**', 'symbols.txt'),
                        recursive=True):
        for g in re.finditer(r'^(func_\w+) kind:function\((arm|thumb)', open(sf).read(), re.M):
            m[g.group(1)] = g.group(2)
    return m


def split_decls(src, func):
    """Devuelve (cabecera, [lineas de declaracion], resto) o None."""
    lines = src.splitlines(True)
    start = None
    for i, ln in enumerate(lines):
        if re.match(r'^\s*\w[\w \*]*\b%s\s*\(' % re.escape(func), ln) and '{' in ln:
            start = i + 1
            break
        if re.match(r'^\s*\w[\w \*]*\b%s\s*\($' % re.escape(func), ln):
            for j in range(i, min(i + 6, len(lines))):
                if '{' in lines[j]:
                    start = j + 1
                    break
            break
    if start is None:
        return None
    decls, k = [], start
    while k < len(lines):
        ln = lines[k]
        if not ln.strip():
            k += 1
            continue
        m = DECL.match(ln)
        if not m:
            break
        decls.append((ln, m.group(3), m.group(4) or ''))
        k += 1
    if len(decls) < 2:
        return None
    names = set(d[1] for d in decls)
    for _, _, init in decls:
        for other in names:
            if re.search(r'\b%s\b' % re.escape(other), init):
                return None            # inicializador que depende de otro: no tocar
    return ''.join(lines[:start]), decls, ''.join(lines[k:])


def verify(path, func, thumb):
    cmd = [sys.executable, os.path.join(ROOT, 'tools', 'verify_idx.py'), path, func]
    if thumb:
        cmd.append('--thumb')
    try:
        return 'MATCH' in subprocess.run(cmd, capture_output=True, text=True,
                                         timeout=120).stdout
    except Exception:
        return False


def try_park(path, func, thumb, quiet=False):
    src = open(path, encoding='utf-8', errors='replace').read()
    parts = split_decls(src, func)
    if parts is None:
        if not quiet:
            print('%-28s sin bloque de declaraciones permutable' % func)
        return None
    head, decls, tail = parts
    n = len(decls)
    perms = list(itertools.permutations(range(n)))
    if len(perms) > MAXPERM:
        perms = perms[:MAXPERM]
    tmp = os.path.join(ROOT, 'build', 'try', 'permute')
    os.makedirs(tmp, exist_ok=True)
    out = os.path.join(tmp, func + '.c')
    for order in perms:
        open(out, 'w', encoding='utf-8').write(
            head + ''.join(decls[i][0] for i in order) + tail)
        if verify(out, func, thumb):
            if not quiet:
                print('%-28s MATCH con orden %s' % (func, [decls[i][1] for i in order]))
            return [decls[i][1] for i in order], out
    if not quiet:
        print('%-28s ninguna de %d permutaciones casa' % (func, len(perms)))
    return None


def main():
    mode = modes()
    if len(sys.argv) > 1 and sys.argv[1] != '--sweep':
        func = sys.argv[1]
        hits = glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', func + '.c'),
                         recursive=True)
        if not hits:
            print('no hay park para', func)
            return
        try_park(hits[0], func, mode.get(func) == 'thumb')
        return

    wins = []
    for p in sorted(glob.glob(os.path.join(ROOT, 'src', '**', 'nonmatching', '*.c'),
                              recursive=True)):
        func = os.path.basename(p)[:-2]
        r = try_park(p, func, mode.get(func) == 'thumb', quiet=True)
        if r:
            wins.append((func, r[0], r[1]))
            print('MATCH %-28s %s' % (func, r[0]))
    print('\n%d parks resueltos solo con el orden de declaracion' % len(wins))


if __name__ == '__main__':
    main()
