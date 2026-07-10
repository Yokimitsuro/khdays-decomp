#!/usr/bin/env python3
"""Sweep ALL mwccarm generations against a stub-linked overlay function.
Compiles <c> with every tools/mwccarm/**/mwccarm.exe and reports which (if any)
produce byte-exact output (reloc-aware). Use before concluding a func is a tie.

    python tools/verify_sweep.py <c> <func_name> <ov_num> [--thumb]
"""
import sys, os, re, glob, subprocess
from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIC = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
FLAGS = ["-O4,p", "-proc", "arm946e", "-interworking", "-lang", "c99",
         "-enum", "int", "-char", "signed", "-inline", "on,noauto",
         "-Cpp_exceptions", "off", "-gccext,on"]
OV_BASE = {"003": 0x0204cac0, "010": 0x0204cac0, "013": 0x0207fa40,
           "019": 0x0207fa40, "029": 0x020b2ee0, "302": 0x020cbf20,
           "294": 0x020d1980, "295": 0x020d37a0, "296": 0x020d55c0,
           "301": 0x020cbf20, "234": 0x020cbf20, "007": 0x0204cac0}


def text_relocs(o_path):
    elf = ELFFile(open(o_path, "rb"))
    text = b""
    for s in elf.iter_sections():
        if s.name == ".text":
            text = s.data()
    symtab = elf.get_section_by_name(".symtab")
    rel = {}
    for s in elf.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations():
                nm = symtab.get_symbol(r["r_info_sym"]).name
                rel[r["r_offset"]] = nm
    return bytearray(text), rel


import tempfile
TMPDIR = tempfile.mkdtemp(prefix="mwsweep_")
_ctr = [0]


def compile_with(mwcc, cpath, thumb):
    _ctr[0] += 1
    o = os.path.join(TMPDIR, "o%d.o" % _ctr[0])
    env = dict(os.environ, LM_LICENSE_FILE=LIC)
    flags = FLAGS + (["-thumb"] if thumb else [])
    r = subprocess.run([mwcc, "-c", *flags, "-o", o, cpath],
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        return None, (r.stdout + r.stderr).strip().splitlines()[-1:] or ["fail"]
    return o, None


def main():
    cpath, name, ov = sys.argv[1], sys.argv[2], sys.argv[3]
    thumb = "--thumb" in sys.argv
    addr = int(name.split("_")[-1], 16)
    base = OV_BASE[ov]
    data = open(os.path.join(ROOT, "build", "build", "arm9_ov%s.bin" % ov), "rb").read()
    size = None
    for line in open(os.path.join(ROOT, "config/arm9/overlays/ov%s/symbols.txt" % ov)):
        m = re.match(r'%s\s+kind:function\((?:arm|thumb),size=0x([0-9a-f]+)\)' % re.escape(name), line)
        if m:
            size = int(m.group(1), 16); break
    if size is None:
        raise SystemExit("no size for " + name)
    orig = bytearray(data[addr - base:addr - base + size])
    orel = {}
    for line in open(os.path.join(ROOT, "config/arm9/overlays/ov%s/relocs.txt" % ov)):
        m = re.match(r'from:0x([0-9a-f]+)\s+kind:(\S+)\s+to:0x([0-9a-f]+)', line)
        if not m:
            continue
        fr = int(m.group(1), 16)
        if addr <= fr < addr + size:
            orel[fr - addr] = m.group(3)

    compilers = sorted(glob.glob(os.path.join(ROOT, "tools", "mwccarm", "**", "mwccarm.exe"), recursive=True))
    any_match = False
    for mwcc in compilers:
        tag = os.path.relpath(mwcc, os.path.join(ROOT, "tools", "mwccarm")).replace("\\mwccarm.exe", "").replace("/mwccarm.exe", "")
        o, err = compile_with(mwcc, cpath, thumb)
        if o is None:
            print("  %-16s compile-fail: %s" % (tag, err[0] if err else ""))
            continue
        mine, mrel = text_relocs(o)
        try:
            os.remove(o)
        except Exception:
            pass
        if len(mine) != size:
            print("  %-16s SIZE %d != %d" % (tag, len(mine), size))
            continue
        mt = bytearray(mine); ob = bytearray(orig)
        for of in set(mrel) | set(orel):
            for k in range(4):
                if of + k < size:
                    mt[of + k] = 0; ob[of + k] = 0
        if mt == ob and set(mrel) == set(orel):
            print("  %-16s >>> MATCH <<<" % tag)
            any_match = True
        else:
            d = [i for i in range(size) if mt[i] != ob[i]]
            print("  %-16s diff@0x%X (%d bytes differ)" % (tag, d[0] if d else -1, len(d)))
    print("MATCH FOUND" if any_match else "no version matched")
    sys.exit(0 if any_match else 1)


if __name__ == "__main__":
    main()
