#!/usr/bin/env python3
"""Indexa TODAS las funciones de los delink .o: bytes + relocs. Sirve para
   deduplicacion (identicas = decompilar una) y para buscar matches del SDK."""
import glob, json, os, hashlib, re
from collections import defaultdict
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DELINK = os.path.join(ROOT, "build", "delinks")

# ARM/THUMB per function, from the dsd config -- the authority.
#
# The obvious source is the ELF convention (low bit of st_value set = THUMB), and that is what
# this script used to do. It is WRONG for these delinked objects: they do not carry the bit, so
# every function came out "arm". That silently mis-typed 1289 THUMB functions, and the only
# symptom was getcand printing an EMPTY disassembly -- capstone decodes nothing and no tool
# complained. Verified 2026-07-17 by disassembling both ways: as ARM they cover 0-4 of their
# bytes, as THUMB they cover 100% with valid prologues.
SYM_MODE = {}
for _p in glob.glob(os.path.join(ROOT, "config", "arm9", "**", "symbols.txt"), recursive=True):
    with open(_p, encoding="utf-8", errors="replace") as _f:
        for _ln in _f:
            _m = re.match(r"^(\S+)\s+kind:function\((arm|thumb),", _ln)
            if _m:
                SYM_MODE[_m.group(1)] = _m.group(2)

INDEX_PATH = os.path.join(ROOT, "build", "func_index.json")

# ★ MERGE, never overwrite. The delink objects only ever contain the functions that are still
# gaps: once a function has a .c, gen_delinks gives it its own unit and it DISAPPEARS from
# build/delinks/*.o. So a plain rebuild silently drops every function already decompiled --
# which is most of them -- and verify_idx can then no longer check any finished function
# (2026-07-17: a rebuild took the index from 11055 entries to 7811 and broke re-verification for
# ~3200 matched functions). Keeping the old entries costs nothing: their bytes are ROM code and
# never change.
index = {}   # name -> {hex, size, relocs:[(off,sym)], module, mode}
if os.path.exists(INDEX_PATH):
    with open(INDEX_PATH) as _f:
        index = json.load(_f)
    print("indice existente: %d funciones (se fusiona, no se sobrescribe)" % len(index))
for o_path in sorted(glob.glob(os.path.join(DELINK, "*.o"))):
    mod = os.path.splitext(os.path.basename(o_path))[0]
    try: elf = ELFFile(open(o_path, "rb"))
    except: continue
    text = None
    for s in elf.iter_sections():
        if s.name == ".text": text = s.data()
    if text is None: continue
    st = elf.get_section_by_name(".symtab")
    if not st: continue
    relsec = {}
    for s in elf.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations():
                relsec[r["r_offset"]] = st.get_symbol(r["r_info_sym"]).name
    for sym in st.iter_symbols():
        if sym.name.startswith("func_") and sym["st_info"]["type"] == "STT_FUNC":
            v = sym["st_value"] & ~1; sz = sym["st_size"]
            if not sz: continue
            relocs = sorted((o - v, s) for o, s in relsec.items() if v <= o < v + sz)
            mode = SYM_MODE.get(sym.name, "thumb" if (sym["st_value"] & 1) else "arm")
            index[sym.name] = {"hex": text[v:v+sz].hex(), "size": sz,
                               "relocs": relocs, "module": mod, "mode": mode}

# Refresh the mode of pre-existing entries too: they were written before this script learned
# to read symbols.txt, so anything carried over from an older index still has the bogus "arm".
for _n, _d in index.items():
    if _n in SYM_MODE:
        _d["mode"] = SYM_MODE[_n]

json.dump(index, open(INDEX_PATH, "w"))
print("funciones indexadas:", len(index))
print("  thumb: %d  arm: %d  (mode from symbols.txt for %d of them)" %
      (sum(1 for d in index.values() if d["mode"] == "thumb"),
       sum(1 for d in index.values() if d["mode"] == "arm"),
       sum(1 for n in index if n in SYM_MODE)))

# --- deduplicacion: clave = bytes + relocs (idem comportamiento) ---
groups = defaultdict(list)
for name, d in index.items():
    key = d["hex"] + "|" + "|".join("%d:%s" % r for r in d["relocs"])
    groups[key].append(name)
dups = {k: v for k, v in groups.items() if len(v) > 1}
total_dup_funcs = sum(len(v) for v in dups.values())
savings = total_dup_funcs - len(dups)   # decompilas 1 por grupo, reusas el resto
print("grupos de funciones IDENTICAS: %d" % len(dups))
print("funciones en duplicados: %d  ->  decompilando 1/grupo ahorras %d funciones" %
      (total_dup_funcs, savings))
print("\n=== mayores grupos de identicas ===")
for k, v in sorted(dups.items(), key=lambda kv: -len(kv[1]))[:8]:
    sz = index[v[0]]["size"]
    print("  x%-3d  (%d bytes)  %s ..." % (len(v), sz, ", ".join(v[:3])))
