#!/usr/bin/env python3
"""Encuentra funciones ultra-limpias (sin bl/blx, sin pool de datos .word/ldr=.L,
   tamano pequeno) y extrae sus bytes originales del delink .o. Salida: JSON."""
import glob, re, json, os
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(ROOT, "asm")
DELINK = os.path.join(ROOT, "build", "delinks")

def func_bytes(o_path):
    out = {}
    try: elf = ELFFile(open(o_path, "rb"))
    except: return out
    text = None
    for s in elf.iter_sections():
        if s.name == ".text": text = s.data()
    if text is None: return out
    for s in elf.iter_sections():
        if s.name == ".symtab":
            for sym in s.iter_symbols():
                if sym.name.startswith("func_") and sym["st_info"]["type"] == "STT_FUNC":
                    v = sym["st_value"] & ~1; sz = sym["st_size"]
                    if sz: out[sym.name] = text[v:v+sz]
    return out

def parse_funcs(s_path):
    txt = open(s_path, encoding="utf-8", errors="replace").read()
    funcs = []; cur = None; name = None; mode = None
    for line in txt.splitlines():
        s = re.sub(r";.*$", "", line).strip()
        ms = re.match(r"(arm|thumb)_func_start\s+(\w+)", s)
        if ms: mode = ms.group(1); continue
        ml = re.match(r"(func_[0-9a-fA-F]+):", s)
        if ml: name = ml.group(1); cur = []; continue
        if cur is not None:
            if re.match(r"(arm|thumb)_func_end\s", s):
                funcs.append((name, mode, cur)); cur = None; name = None; continue
            if s: cur.append(s)
    return funcs

cands = []
for s_path in sorted(glob.glob(os.path.join(ASM, "*.s"))):
    base = os.path.splitext(os.path.basename(s_path))[0]
    fb = func_bytes(os.path.join(DELINK, base + ".o"))
    if not fb: continue
    for name, mode, lines in parse_funcs(s_path):
        # ultra-limpia: sin llamadas, sin pool de datos
        if any(re.match(r"(bl|blx)\b", l, re.I) for l in lines): continue
        if any(".L_" in l or ".word" in l or ".byte" in l or ".short" in l for l in lines): continue
        if any(re.match(r"(swi|svc|mcr|mrc|mrs|msr)\b", l, re.I) for l in lines): continue
        body = [l for l in lines if l and not l.startswith(".")]
        if not (2 <= len(body) <= 14): continue
        if name not in fb: continue
        cands.append({"name": name, "mode": mode, "module": base,
                      "asm": body, "hex": fb[name].hex()})

cands.sort(key=lambda c: len(c["asm"]))
json.dump(cands, open(os.path.join(ROOT, "build", "candidates.json"), "w"), indent=1)
print("candidatas ultra-limpias:", len(cands))
for c in cands[:12]:
    print("  %-22s %-6s %2d ins  %s" % (c["name"], c["mode"], len(c["asm"]), c["hex"][:24]))
