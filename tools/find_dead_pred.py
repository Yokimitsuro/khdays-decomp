"""Busca en los parks el patron 'instruccion predicada MUERTA': un salto condicional
   b<cond> X donde la instruccion en X esta predicada con la condicion CONTRARIA, asi
   que nunca puede ejecutarse.

   Eso no es basura del compilador: significa que el ORIGINAL repite un test que tu C
   no tiene (mwcc reusa los flags en vez de volver a comparar). Confirmado en
   func_ov008_02077f1c y func_ov024_02084fac el 2026-07-18.
"""
import json, os, re, sys, glob
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = r"E:\KH 3582\decomp"
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))

OPP = {"eq": "ne", "ne": "eq", "mi": "pl", "pl": "mi", "lt": "ge", "ge": "lt",
       "gt": "le", "le": "gt", "cs": "cc", "cc": "cs", "hi": "ls", "ls": "hi"}
CONDS = set(OPP)

modes = {}
for p in glob.glob(os.path.join(ROOT, "config/arm9/**/symbols.txt"), recursive=True):
    for ln in open(p, encoding="utf-8", errors="replace"):
        m = re.match(r"\s*(\S+)\s", ln)
        if m and "function(" in ln:
            modes[m.group(1)] = "thumb" if "function(thumb" in ln else "arm"


def cond_of(mnem):
    for c in CONDS:
        if mnem.endswith(c) and len(mnem) > len(c):
            return c
    return None


def scan(name):
    e = IDX[name]
    th = modes.get(name) == "thumb"
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if th else CS_MODE_ARM)
    ins = [(i.address, i.mnemonic, i.op_str) for i in md.disasm(bytes.fromhex(e["hex"]), 0)]
    at = {a: k for k, (a, _m, _o) in enumerate(ins)}
    out = []
    for k, (a, mn, op) in enumerate(ins):
        if not mn.startswith("b"):
            continue
        c = cond_of(mn)
        if not c or mn in ("bl", "blx", "bx"):
            continue
        m = re.match(r"^#(?:0x)?([0-9a-fA-F]+)$", op.strip())
        if not m:
            continue
        tgt = int(m.group(1), 16)
        j = at.get(tgt)
        if j is None or j <= k:
            continue
        tm = ins[j][1]
        tc = cond_of(tm)
        if tc and tc == OPP[c]:
            out.append("%s #%x -> %04x: %s %s (MUERTA)" % (mn, tgt, tgt, tm, ins[j][2]))
    return out


parks = []
for pat in ("src/**/nonmatching/*.c", "libs/**/nonmatching/*.c"):
    for f in glob.glob(os.path.join(ROOT, pat), recursive=True):
        n = os.path.basename(f.replace(os.sep, "/"))[:-2]
        if n in IDX:
            parks.append(n)
parks.sort()

hits = []
for n in parks:
    try:
        d = scan(n)
    except Exception:
        continue
    if d:
        hits.append((n, d))

print("parks escaneados:", len(parks))
print("con instruccion predicada MUERTA:", len(hits))
for n, d in hits:
    print("  %-32s (%s)" % (n, modes.get(n)))
    for x in d:
        print("        ", x)
