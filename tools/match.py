#!/usr/bin/env python3
"""Compila una funcion C con mwccarm (build 139, licencia parcheada) y la compara
   byte-exacto contra el original.

   Modo simple (reloc-free):
       python tools/match.py <c> <hex_original> [--thumb]
   Modo reloc-aware (funciones con llamadas):
       python tools/match.py <c> --obj <delink.o> --func <name> [--thumb]
   En modo reloc-aware enmascara los bytes relocalizados y exige que los simbolos
   relocalizados (callees) coincidan en offset+nombre+tipo.
"""
import sys, os, subprocess, io
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC  = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
FLAGS = ["-O4,p", "-proc", "arm946e", "-interworking", "-lang", "c99",
         "-enum", "int", "-char", "signed", "-inline", "on,noauto",
         "-Cpp_exceptions", "off", "-gccext,on"]

def compile_c(cpath, thumb=False):
    o = cpath + ".o"
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = FLAGS + (["-thumb"] if thumb else [])
    r = subprocess.run([MWCC, "-c", *flags, "-o", o, cpath],
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        print(r.stdout, r.stderr); raise SystemExit("compilacion fallo")
    return o

def text_relocs(o_path):
    elf = ELFFile(open(o_path, "rb"))
    text = b""
    for s in elf.iter_sections():
        if s.name == ".text": text = s.data()
    symtab = elf.get_section_by_name(".symtab")
    rel = {}
    for s in elf.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations():
                nm = symtab.get_symbol(r["r_info_sym"]).name
                rel[r["r_offset"]] = (nm, r["r_info_type"])
    return bytearray(text), rel

def orig_func(delink_o, name):
    elf = ELFFile(open(delink_o, "rb"))
    text = b""
    for s in elf.iter_sections():
        if s.name == ".text": text = s.data()
    symtab = elf.get_section_by_name(".symtab")
    val = size = None
    for sym in symtab.iter_symbols():
        if sym.name == name and sym["st_info"]["type"] == "STT_FUNC":
            val = sym["st_value"] & ~1; size = sym["st_size"]
    if val is None: raise SystemExit("simbolo no encontrado en delink: " + name)
    fb = bytearray(text[val:val+size]); rel = {}
    for s in elf.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations():
                if val <= r["r_offset"] < val+size:
                    nm = symtab.get_symbol(r["r_info_sym"]).name
                    rel[r["r_offset"]-val] = (nm, r["r_info_type"])
    return fb, rel

def show(code, thumb=False):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    for i in md.disasm(bytes(code), 0):
        print("   %-12s %s" % (" ".join("%02x" % b for b in i.bytes), i.mnemonic+" "+i.op_str))

def cmp_reloc(mine, mrel, orig, orel):
    size = len(orig)
    if len(mine) < size:
        return False, "tu funcion es mas corta (%d < %d)" % (len(mine), size)
    mt = bytearray(mine[:size]); ob = bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off+k < size: mt[off+k] = 0; ob[off+k] = 0
    if mt != ob:
        d = [i for i in range(size) if mt[i] != ob[i]]
        return False, "byte diff @0x%X (tras enmascarar relocs)" % d[0]
    ms = {o: v for o, v in mrel.items() if o < size}
    if ms != orel:
        return False, "relocs/callees difieren:\n   tuyas=%s\n   orig =%s" % (ms, orel)
    return True, "ok"

if __name__ == "__main__":
    cpath = sys.argv[1]
    thumb = "--thumb" in sys.argv
    o = compile_c(cpath, thumb)
    mine, mrel = text_relocs(o)
    print("=== compilado (.text, %d bytes, %d relocs) ===" % (len(mine), len(mrel)))
    show(mine, thumb)
    if "--obj" in sys.argv:
        delink = sys.argv[sys.argv.index("--obj")+1]
        name = sys.argv[sys.argv.index("--func")+1]
        orig, orel = orig_func(delink, name)
        ok, msg = cmp_reloc(mine, mrel, orig, orel)
        print("\norig %d bytes, %d relocs %s" % (len(orig), len(orel), dict(orel)))
        print(">>> MATCH <<<" if ok else ">>> DIFIERE <<< " + msg)
        sys.exit(0 if ok else 1)
    else:
        args = [a for a in sys.argv[2:] if not a.startswith("--")]
        if args:
            orig = bytes.fromhex(args[0].replace(" ", ""))
            ok = bytes(mine[:len(orig)]) == orig
            print("orig :", orig.hex())
            print(">>> MATCH <<<" if ok else ">>> DIFIERE <<<")
            sys.exit(0 if ok else 1)
