#!/usr/bin/env python3
"""Genera el contenido de un scratch de decomp.me para una funcion.
   Uso: python tools/decompme.py func_XXXXXXXX"""
import json, sys, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
name = sys.argv[1]

def load(p):
    fp = os.path.join(ROOT, "build", p)
    return {c["name"]: c for c in json.load(open(fp))} if os.path.exists(fp) else {}
calls = load("calls.json"); cands = load("candidates.json")

FLAGS = "-O4,p -proc arm946e -interworking -lang c99 -enum int -char signed -inline on,noauto -Cpp_exceptions off -gccext,on"

if name in calls:
    c = calls[name]
    insns = c["asm"].split(" ; ")
    callees = c["callees"]
elif name in cands:
    c = cands[name]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if c["mode"] == "thumb" else CS_MODE_ARM)
    insns = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(c["hex"]), 0)]
    callees = []
else:
    print("funcion no encontrada:", name); sys.exit(1)

print("="*70)
print("DECOMP.ME SCRATCH para", name)
print("="*70)
print("\n[Platform]  Nintendo DS")
print("[Compiler]  3.0 build 139 (MW 2.0sp2p4)")
print("\n[Compiler flags]")
print(FLAGS)
print("\n[Diff label]")
print(name)
print("\n[Target assembly]  (pega esto en 'Target assembly')")
print(".text")
if c["mode"] == "thumb":
    print(".thumb")
    print(".global " + name)
    print(".thumb_func")
else:
    print(".arm")
    print(".global " + name)
print(name + ":")
for ins in insns:
    print("    " + ins)
print("\n[Context]  (pega esto en 'Context')")
print("typedef signed char s8;    typedef unsigned char u8;")
print("typedef signed short s16;  typedef unsigned short u16;")
print("typedef signed int s32;    typedef unsigned int u32;")
print("typedef signed long long s64; typedef unsigned long long u64;")
print("typedef float f32;         typedef double f64;")
for ce in callees:
    print("extern int %s();" % ce)
print("\n" + "="*70)
