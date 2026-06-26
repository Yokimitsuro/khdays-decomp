#!/usr/bin/env python3
"""Imprime los datos de una funcion para un agente decompilador.
   Prioridad: calls.json / candidates.json (curadas, disasm con simbolos) ->
   func_index.json (cualquier funcion del juego)."""
import json, sys, os
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
name = sys.argv[1]

def load(p):
    fp = os.path.join(ROOT, "build", p)
    return json.load(open(fp)) if os.path.exists(fp) else {}
calls = {c["name"]: c for c in load("calls.json")} if isinstance(load("calls.json"), list) else {}
cands = {c["name"]: c for c in load("candidates.json")} if isinstance(load("candidates.json"), list) else {}
index = load("func_index.json")

def disasm(hexs, mode):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    return " ; ".join(i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(hexs), 0))

if name in calls:
    c = calls[name]; thumb = " --thumb" if c["mode"] == "thumb" else ""
    print("name:", name); print("mode:", c["mode"]); print("kind: HAS CALLS (reloc-aware)")
    print("disasm:", c["asm"]); print("callees:", c["callees"])
    print("write_to: E:/KH 3582/decomp/src/calls/%s.c" % name)
    print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/calls/%s.c" --obj "%s" --func %s%s'
          % (name, c["delink"].replace("\\", "/"), name, thumb))
elif name in cands:
    c = cands[name]; thumb = " --thumb" if c["mode"] == "thumb" else ""
    print("name:", name); print("mode:", c["mode"]); print("kind: reloc-free")
    print("disasm:", disasm(c["hex"], c["mode"]))
    print("write_to: E:/KH 3582/decomp/src/auto/%s.c" % name)
    print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/auto/%s.c" %s%s'
          % (name, c["hex"], thumb))
elif name in index:
    d = index[name]; thumb = " --thumb" if d["mode"] == "thumb" else ""
    has_calls = bool(d["relocs"])
    kind = "calls" if has_calls else "auto"
    print("name:", name); print("mode:", d["mode"])
    print("kind:", "HAS CALLS (reloc-aware)" if has_calls else "reloc-free")
    print("disasm:", disasm(d["hex"], d["mode"]))
    if has_calls:
        print("relocations (offset -> symbol, i.e. your callees/data refs):")
        for off, sym in d["relocs"]:
            print("    +0x%x -> %s" % (off, sym))
        print("callees:", sorted(set(s for _, s in d["relocs"])))
        print("write_to: E:/KH 3582/decomp/src/calls/%s.c" % name)
        print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/calls/%s.c" --obj "%s" --func %s%s'
              % (name, os.path.join(ROOT, "build", "delinks", d["module"] + ".o").replace("\\", "/"), name, thumb))
    else:
        print("write_to: E:/KH 3582/decomp/src/auto/%s.c" % name)
        print('verify_cmd: python "E:/KH 3582/decomp/tools/match.py" "E:/KH 3582/decomp/src/auto/%s.c" %s%s'
              % (name, d["hex"], thumb))
else:
    print("desconocida:", name)
