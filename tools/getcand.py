#!/usr/bin/env python3
"""Imprime los datos de una funcion candidata para un agente decompilador.
   Soporta funciones reloc-free (candidates.json) y con-llamadas (calls.json)."""
import json, sys, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
name = sys.argv[1]

def load(p):
    fp = os.path.join(ROOT, "build", p)
    return {c["name"]: c for c in json.load(open(fp))} if os.path.exists(fp) else {}

calls = load("calls.json")
cands = load("candidates.json")

if name in calls:
    c = calls[name]
    thumb = " --thumb" if c["mode"] == "thumb" else ""
    print("name:", name)
    print("mode:", c["mode"])
    print("kind: HAS CALLS (reloc-aware)")
    print("disasm:", c["asm"])           # ya trae nombres de simbolos del .s
    print("callees:", c["callees"])
    print("write_to: E:/KH 3582/decomp/src/calls/%s.c" % name)
    print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/calls/%s.c" --obj "%s" --func %s%s'
          % (name, c["delink"].replace("\\", "/"), name, thumb))
elif name in cands:
    c = cands[name]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if c["mode"] == "thumb" else CS_MODE_ARM)
    disasm = " ; ".join(i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(c["hex"]), 0))
    thumb = " --thumb" if c["mode"] == "thumb" else ""
    print("name:", name)
    print("mode:", c["mode"])
    print("kind: reloc-free")
    print("disasm:", disasm)
    print("write_to: E:/KH 3582/decomp/src/auto/%s.c" % name)
    print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/auto/%s.c" %s%s'
          % (name, c["hex"], thumb))
else:
    print("desconocida:", name)
