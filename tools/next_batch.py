#!/usr/bin/env python3
"""Selecciona el siguiente lote de funciones-con-llamadas (calls.json) sin hacer,
   ordenadas por simplicidad (ninstr, size). Salta el idiom hand-asm conocido
   {r0,lr} save/restore (no proviene de C limpio, ver func_020036a0).

   Uso:  python tools/next_batch.py [N]      -> imprime JSON array de N nombres
         python tools/next_batch.py [N] -v   -> tambien imprime el asm de cada uno
"""
import json, os, sys, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
N = int(sys.argv[1]) if len(sys.argv) > 1 and sys.argv[1].isdigit() else 18
verbose = "-v" in sys.argv

calls = json.load(open(os.path.join(ROOT, "build", "calls.json")))
done = set(os.path.splitext(f)[0] for f in os.listdir(os.path.join(ROOT, "src", "calls"))
           if f.endswith(".c"))
done.add("func_020036a0")  # hand-asm wrapper, saltada

def is_handasm_r0(asm):
    # stmdb sp!, {r0, lr} ... ldmia sp!, {r0, lr} ; bx lr  -> preserva r0/arg, hand-asm
    return bool(re.match(r"^(stmdb sp!, \{r0|push \{r0)", asm)) and "bx lr" in asm

todo = [c for c in calls if c["name"] not in done and not is_handasm_r0(c["asm"])]
todo.sort(key=lambda c: (c["ninstr"], c["size"]))

batch = todo[:N]
print(json.dumps([c["name"] for c in batch]))
if verbose:
    for c in batch:
        print("# %-16s n=%-2d sz=%-3d | %s" % (c["name"], c["ninstr"], c["size"], c["asm"]),
              file=sys.stderr)
print("# remaining todo: %d" % len(todo), file=sys.stderr)
