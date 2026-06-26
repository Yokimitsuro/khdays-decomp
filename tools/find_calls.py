#!/usr/bin/env python3
"""Extrae funciones CON llamadas (bl/blx) + sus datos (disasm con nombres de
   simbolos del .s, delink .o, callees, tamano). Salida JSON ordenada por tamano."""
import glob, re, json, os
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(ROOT, "asm"); DELINK = os.path.join(ROOT, "build", "delinks")

def func_syms(o_path):
    out = {}
    try: elf = ELFFile(open(o_path, "rb"))
    except: return out
    st = elf.get_section_by_name(".symtab")
    if not st: return out
    for sym in st.iter_symbols():
        if sym.name.startswith("func_") and sym["st_info"]["type"] == "STT_FUNC":
            out[sym.name] = sym["st_size"]
    return out

def parse(s_path):
    txt = open(s_path, encoding="utf-8", errors="replace").read()
    cur = None; name = None; mode = None; out = []
    for line in txt.splitlines():
        s = re.sub(r";.*$", "", line).rstrip()
        st = s.strip()
        m = re.match(r"\s*(arm|thumb)_func_start\s+(\w+)", s)
        if m: mode = m.group(1); continue
        m = re.match(r"(func_[0-9a-fA-F]+):", st)
        if m: name = m.group(1); cur = []; continue
        if cur is not None:
            if re.match(r"\s*(arm|thumb)_func_end\s", s):
                out.append((name, mode, cur)); cur = None; name = None; continue
            if st and not st.startswith((".global", ".public")):
                cur.append(st)
    return out

cands = []
for s_path in sorted(glob.glob(os.path.join(ASM, "*.s"))):
    base = os.path.splitext(os.path.basename(s_path))[0]
    delink = os.path.join(DELINK, base + ".o")
    syms = func_syms(delink)
    if not syms: continue
    for name, mode, lines in parse(s_path):
        calls = [re.match(r"(?:bl|blx)\s+(\S+)", l).group(1)
                 for l in lines if re.match(r"(bl|blx)\s+\w", l)]
        if not calls: continue                       # solo funciones con llamadas
        if name not in syms: continue
        ninstr = sum(1 for l in lines if not l.startswith("."))
        cands.append({"name": name, "mode": mode, "delink": delink,
                      "asm": " ; ".join(lines), "callees": sorted(set(calls)),
                      "size": syms[name], "ninstr": ninstr})

cands.sort(key=lambda c: (c["ninstr"], len(c["callees"])))
json.dump(cands, open(os.path.join(ROOT, "build", "calls.json"), "w"))
print("funciones CON llamadas:", len(cands))
print("=== 12 mas simples ===")
for c in cands[:12]:
    print("  %-20s %-5s %2dins  calls=%s" % (c["name"], c["mode"], c["ninstr"], c["callees"]))
