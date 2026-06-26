#!/usr/bin/env python3
"""Indexa TODAS las funciones de los delink .o: bytes + relocs. Sirve para
   deduplicacion (identicas = decompilar una) y para buscar matches del SDK."""
import glob, json, os, hashlib
from collections import defaultdict
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DELINK = os.path.join(ROOT, "build", "delinks")

index = {}   # name -> {hex, size, relocs:[(off,sym)], module}
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
            mode = "thumb" if (sym["st_value"] & 1) else "arm"
            index[sym.name] = {"hex": text[v:v+sz].hex(), "size": sz,
                               "relocs": relocs, "module": mod, "mode": mode}

json.dump(index, open(os.path.join(ROOT, "build", "func_index.json"), "w"))
print("funciones indexadas:", len(index))

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
