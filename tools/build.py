#!/usr/bin/env python3
"""Build harness: ensambla (.s) / compila (.c) cada delink unit y lo compara
   byte-exacto (modulo relocs) contra el delink original de dsd.
   Uso: python tools/build.py [--verbose]
"""
import os, glob, subprocess, sys, re
from elftools.elf.elffile import ELFFile

ROOT   = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM    = os.path.join(ROOT, "asm")
SRC    = os.path.join(ROOT, "src")
DELINK = os.path.join(ROOT, "build", "delinks")
OBJ    = os.path.join(ROOT, "build", "obj")
AS     = open(os.path.join("/tmp/aspath.txt")).read().strip() if os.path.exists("/tmp/aspath.txt") else None
# fallback fijo al toolchain instalado
if not AS or not os.path.exists(AS):
    import glob as _g
    c = _g.glob(r"C:\Program Files (x86)\Arm GNU Toolchain*\*\bin\arm-none-eabi-as.exe")
    AS = c[0] if c else "arm-none-eabi-as"
MWCC = os.path.join(ROOT, "tools", "mwccarm", "3.0_patch4", "mwccarm.exe")
LIC  = os.path.join(ROOT, "tools", "mwccarm", "license.dat")
os.makedirs(OBJ, exist_ok=True)
verbose = "--verbose" in sys.argv

def load(path):
    elf = ELFFile(open(path, "rb")); text = bytearray(); rel = set()
    for s in elf.iter_sections():
        if s.name == ".text": text = bytearray(s.data())
    for s in elf.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations(): rel.add(r["r_offset"])
    return text, rel

def assemble(s_path, o_path):
    pp = re.sub(r";[^\n]*", "", open(s_path, encoding="utf-8", errors="replace").read())
    pps = o_path + ".s"; open(pps, "w", encoding="utf-8").write(pp)
    r = subprocess.run([AS, "-march=armv5te", "-mno-warn-deprecated", "-I", ROOT,
                        "-o", o_path, pps], capture_output=True, text=True)
    return r.returncode == 0, r.stderr

def compare(mine_o, tgt_o):
    mine, mr = load(mine_o); tgt, tr = load(tgt_o)
    if len(mine) != len(tgt): return False, "tam %d!=%d" % (len(mine), len(tgt))
    for off in (mr | tr):
        for k in range(4):
            if off + k < len(mine): mine[off + k] = 0; tgt[off + k] = 0
    d = sum(1 for i in range(len(mine)) if mine[i] != tgt[i])
    return d == 0, ("%d bytes diff" % d if d else "ok")

ok = bad = skip = 0; fails = []
for s in sorted(glob.glob(os.path.join(ASM, "*.s"))):
    name = os.path.splitext(os.path.basename(s))[0]
    tgt = os.path.join(DELINK, name + ".o")
    if not os.path.exists(tgt): skip += 1; continue
    o = os.path.join(OBJ, name + ".o")
    aok, err = assemble(s, o)
    if not aok:
        bad += 1; fails.append((name, "ASM: " + err.strip().split("\n")[0][:80])); continue
    cok, msg = compare(o, tgt)
    if cok: ok += 1
    else: bad += 1; fails.append((name, msg))
    if verbose: print(("OK  " if cok else "BAD ") + name + " " + msg)

print("\n==== BUILD: %d OK / %d BAD / %d skip (sin target) ====" % (ok, bad, skip))
for n, m in fails[:25]: print("  BAD %-28s %s" % (n, m))
sys.exit(1 if bad else 0)
