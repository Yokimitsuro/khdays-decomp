#!/usr/bin/env python3
"""Porta un .c ya casado a otra funcion de la MISMA FORMA (misma secuencia de mnemonicos).

    python tools/port_template.py <plantilla> <candidata> [--write]
    python tools/port_template.py --all [--write]      # barre todo el ranking de nearfam

Como las dos funciones tienen instruccion por instruccion el mismo mnemonico, las diferencias
son solo (a) los simbolos de los relocs y (b) algunos inmediatos. Este script las empareja por
POSICION y aplica las sustituciones al texto del .c de la plantilla.

Cada resultado se verifica con verify_idx (ARM y THUMB) y **solo se escribe si casa**. Los que
no casan se reportan; un fallo aqui suele significar que el inmediato aparecia en dos papeles
distintos y la sustitucion textual fue ambigua -- en ese caso, edicion a mano.

POR QUE (2026-07-18): la familia d15c dio 68 matches con un generador hecho a medida. Escribir
uno por forma no escala; esto lo hace para cualquiera de las ~125 formas que `nearfam.py` lista.
"""
import glob
import json
import os
import re
import subprocess
import sys
from collections import defaultdict

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
MD = {False: Cs(CS_ARCH_ARM, CS_MODE_ARM), True: Cs(CS_ARCH_ARM, CS_MODE_THUMB)}
OUT = os.path.join(ROOT, "build", "try", "port")


def modes():
    out = {}
    for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
        for ln in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"\s*(\S+)\s.*kind:function\((arm|thumb)", ln)
            if m:
                out[m.group(1)] = m.group(2)
    return out


MODE = modes()


def dis(name):
    e = IDX[name]
    thumb = MODE.get(name) == "thumb"
    return list(MD[thumb].disasm(bytes.fromhex(e["hex"]), int(name[-8:], 16))), e, thumb


def imms(op):
    return [int(m, 0) for m in re.findall(r"#(-?(?:0x)?[0-9a-fA-F]+)", op)]


def build_map(tpl, cand):
    """(subs_simbolos, subs_inmediatos) o None si las formas no encajan."""
    ti, te, _ = dis(tpl)
    ci, ce, _ = dis(cand)
    if len(ti) != len(ci):
        return None
    if [i.mnemonic for i in ti] != [i.mnemonic for i in ci]:
        return None

    sym = {}
    trel, crel = dict(te["relocs"]), dict(ce["relocs"])
    if sorted(trel) != sorted(crel):
        return None
    for off in trel:
        if trel[off] != crel[off]:
            sym[trel[off]] = crel[off]

    val = {}
    for a, b in zip(ti, ci):
        ia, ib = imms(a.op_str), imms(b.op_str)
        if len(ia) != len(ib):
            return None
        for x, y in zip(ia, ib):
            if x != y:
                # un mismo valor no puede mapear a dos distintos: seria ambiguo
                if val.get(x, y) != y:
                    return None
                val[x] = y
    return sym, val


def render(tpl, cand, sym, val, scaled=False, guard_shifts=True, min_val=0):
    """scaled=True sustituye ADEMAS los valores divididos por 4.

    El desensamblado habla en offsets de byte (`str ip, [r3, #0x3c]`) pero el .c a menudo usa
    indices de array (`state[0xf]`). Sin esto, un cambio de offset 0x3c -> 0x10 no toca el
    `[0xf]` del fuente y quedan 4 bytes de residuo que parecen otra cosa.
    """
    src = None
    for sub in ("auto", "calls"):
        for p in glob.glob(os.path.join(ROOT, "src", "**", sub, tpl + ".c"), recursive=True):
            if "asm_stubs" not in p.replace("\\", "/").split("/"):
                src = p
    if src is None:
        return None
    s = open(src, encoding="utf-8").read()

    # 1) simbolos (mas largos primero, para no romper prefijos comunes)
    for a in sorted(sym, key=len, reverse=True):
        s = re.sub(r"\b%s\b" % re.escape(a), sym[a], s)
    # 2) el nombre de la funcion
    s = re.sub(r"\b%s\b" % re.escape(tpl), cand, s)
    # 3) inmediatos, en las dos grafias que usamos en el arbol.
    # ⚠ Antes, blinda los ANCHOS DE BITFIELD (`unsigned b : 8;`). No son inmediatos del codigo:
    # el ancho se convierte en un par lsl/lsr cuyo desplazamiento es 32-ancho, asi que un valor
    # como 8 puede ser a la vez un offset de campo Y un ancho, y sustituirlo textualmente mueve
    # el bitfield de byte. Es el fallo que se comio 6 candidatas de una forma (2026-07-18).
    guards = []

    def _tok(n):
        out = ""
        while True:
            out += chr(ord("A") + n % 26)
            n //= 26
            if not n:
                return out

    def _stash(m):
        guards.append(m.group(0))
        # el token NO puede llevar digitos: la sustitucion de inmediatos los pisaria
        return "\x00%s\x00" % _tok(len(guards) - 1)

    s = re.sub(r":\s*\d+", _stash, s)
    # ⚠ Y los DESPLAZAMIENTOS: `(u << 0x10) >> 0x18` es el idiom con el que este arbol escribe
    # un bitfield empaquetado. Esos 0x10/0x18 son estructura (que byte de la palabra), no datos,
    # asi que un mapeo legitimo como 0x10 -> 5 los destroza y el residuo aparece en un sitio
    # que no tiene nada que ver. Detectado en la forma de func_ov270_020d4104 (2026-07-18).
    if guard_shifts:
        s = re.sub(r"(<<|>>)\s*(0x[0-9a-fA-F]+|\d+)", _stash, s)

    # min_val: ignora los mapeos de valores pequeños. Un literal como 8 aparece en varios papeles
    # (offset de campo, indice, constante) y la sustitucion textual no distingue: si el mapa dice
    # 8 -> 24 por UNA instruccion, reescribe tambien los `+ 8` que debian quedarse. Saltarse los
    # pequeños rescata justo esos casos, y como cada salida se verifica no hay riesgo.
    val = {a: b for a, b in val.items() if abs(a) >= min_val}
    subs = dict(val)
    if scaled:
        for a, b in val.items():
            if a % 4 == 0 and b % 4 == 0 and a >= 8 and a // 4 not in subs:
                subs[a // 4] = b // 4

    for a in sorted(subs, key=lambda v: -abs(v)):
        b = subs[a]
        s = re.sub(r"\b0x0*%x\b" % a, "0x%x" % b, s, flags=re.I)
        if 0 <= a <= 4096:
            s = re.sub(r"(?<![\w.])%d(?![\w.])" % a, str(b), s)
    def _pop(m):
        n, mul = 0, 1
        for ch in m.group(1):
            n += (ord(ch) - ord("A")) * mul
            mul *= 26
        return guards[n]

    return re.sub(r"\x00([A-Z]+)\x00", _pop, s)


def try_one(tpl, cand, write):
    m = build_map(tpl, cand)
    if m is None:
        return "forma/relocs no encajan"
    os.makedirs(OUT, exist_ok=True)
    p = os.path.join(OUT, cand + ".c")
    # Estrategias, de la mas conservadora a la mas agresiva. Se acepta la primera que VERIFIQUE,
    # asi que añadir una nunca empeora: solo puede rescatar candidatas que antes quedaban en
    # DIFIERE. La ultima desprotege los desplazamientos por si alguna si mueve de verdad el byte.
    for scaled, guard, minv in ((False, True, 0), (True, True, 0),
                                (True, True, 16), (True, False, 0)):
        s = render(tpl, cand, *m, scaled=scaled, guard_shifts=guard, min_val=minv)
        if s is None:
            return "no encuentro el .c de la plantilla"
        open(p, "w", newline="\n", encoding="utf-8").write(s)
        for extra in ([], ["--thumb"]):
            r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "verify_idx.py"),
                                p, cand] + extra, capture_output=True, text=True, cwd=ROOT)
            if "MATCH" not in r.stdout:
                continue
            if write:
                ov = re.match(r"func_(ov\d+)_", cand)
                dst = os.path.join(ROOT, "src", "overlays", ov.group(1), "calls",
                                   cand + ".c") if ov else os.path.join(
                    ROOT, "src", "calls", cand + ".c")
                if not os.path.exists(dst):
                    os.makedirs(os.path.dirname(dst), exist_ok=True)
                    open(dst, "w", newline="\n", encoding="utf-8").write(s)
            return "MATCH"
    return "DIFIERE"


def all_shapes():
    """Reusa la agrupacion de nearfam sin reimplementarla."""
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import nearfam
    done = nearfam.matched_paths()
    skip = nearfam.parked()
    buckets = defaultdict(lambda: {"tpl": [], "todo": []})
    for name, e in IDX.items():
        mode = MODE.get(name)
        if mode is None:
            continue
        s = nearfam.shape(name, e, mode == "thumb")
        if s is None:
            continue
        b = buckets[s]
        (b["tpl"] if name in done else b["todo"]).append(name)
    out = []
    for b in buckets.values():
        todo = [n for n in b["todo"] if n not in skip]
        if b["tpl"] and todo:
            out.append((b["tpl"], todo))
    out.sort(key=lambda r: -len(r[1]))
    return out


def main():
    write = "--write" in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith("--")]

    if "--all" in sys.argv:
        tot = defaultdict(int)
        for tpls, todo in all_shapes():
            for cand in todo:
                res = "sin plantilla util"
                for tpl in tpls:
                    res = try_one(tpl, cand, write)
                    if res == "MATCH":
                        break
                tot[res] += 1
                # Imprime SIEMPRE el par: los DIFIERE son la cola de edicion a mano y sin el
                # nombre de la plantilla hay que recalcularlos (y tras un --write ya no salen,
                # porque la candidata pasa a contar como hecha).
                print("  %-24s %-28s <- %s" % (res, cand, tpl))
        print("\n" + "  ".join("%s=%d" % kv for kv in sorted(tot.items())))
        return

    if len(args) != 2:
        raise SystemExit(__doc__)
    print(try_one(args[0], args[1], write))


if __name__ == "__main__":
    main()
