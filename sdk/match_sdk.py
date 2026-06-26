#!/usr/bin/env python3
"""Extrae cada funcion de un .o compilado de la NitroSDK y la busca byte-exacta
en build/func_index.json. Reporta matches name->func_XXXXXXXX."""
import json, os, sys
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "func_index.json")

def funcs_from_obj(opath):
    """Devuelve dict {nombre: (bytes, relocs_dict)} para cada STT_FUNC del .text.

    mwccarm emite cada funcion en su propia seccion .text -> indexamos por
    shndx y leemos data() de la seccion correspondiente."""
    elf = ELFFile(open(opath, "rb"))
    sections = list(elf.iter_sections())
    symtab = elf.get_section_by_name(".symtab")
    # relocs por shndx: shndx -> {offset: (name, type)}
    sec_relocs = {}
    for i, s in enumerate(sections):
        if s.name.startswith(".rel"):
            target = s["sh_info"]
            rd = sec_relocs.setdefault(target, {})
            for r in s.iter_relocations():
                nm = symtab.get_symbol(r["r_info_sym"]).name
                rd[r["r_offset"]] = (nm, r["r_info_type"])
    out = {}
    for sym in symtab.iter_symbols():
        if sym["st_info"]["type"] != "STT_FUNC": continue
        if sym.name in ("$a", "$t", "$d", ""): continue
        shndx = sym["st_shndx"]
        if not isinstance(shndx, int): continue
        sec = sections[shndx]
        if not sec.name.startswith(".text"): continue
        val = sym["st_value"] & ~1
        size = sym["st_size"]
        if size == 0: continue
        data = sec.data()
        rel = {o-val: v for o, v in sec_relocs.get(shndx, {}).items() if val <= o < val+size}
        out[sym.name] = (bytes(data[val:val+size]), rel)
    return out

def search(my_bytes, index):
    hx = my_bytes.hex()
    hits = []
    for fname, info in index.items():
        if info["size"] != len(my_bytes): continue
        if info["hex"] == hx: hits.append(fname)
    return hits

def main(opath):
    with open(INDEX) as f: index = json.load(f)
    funcs = funcs_from_obj(opath)
    print("== compilado: %d funciones ==" % len(funcs))
    matched = 0
    for name, (b, rel) in funcs.items():
        hits = search(b, index)
        rel_note = " (con %d relocs - byte-search no las enmascara)" % len(rel) if rel else ""
        if hits:
            matched += 1
            print(" MATCH  %s  (%d bytes) -> %s%s" % (name, len(b), ", ".join(hits), rel_note))
        else:
            print(" miss   %s  (%d bytes)%s" % (name, len(b), rel_note))
    print("\n== %d/%d funciones identificadas ==" % (matched, len(funcs)))

if __name__ == "__main__":
    main(sys.argv[1])
