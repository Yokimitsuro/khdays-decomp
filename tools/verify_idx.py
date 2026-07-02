#!/usr/bin/env python3
"""Verifica byte-exacto una funcion C contra build/func_index.json (ground truth
   extraido de la ROM), SIN necesitar dsd delink/configure. Reloc-aware: enmascara
   las palabras relocalizadas y exige que (offset -> simbolo) coincidan.

       python tools/verify_idx.py <c> <func_name> [--thumb]
"""
import sys, os, json
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = os.path.join(ROOT, "build", "func_index.json")

def main():
    cpath = sys.argv[1]
    name = sys.argv[2]
    thumb = "--thumb" in sys.argv
    idx = json.load(open(IDX))
    if name not in idx:
        raise SystemExit("no en func_index: " + name)
    e = idx[name]
    orig = bytearray.fromhex(e["hex"])
    orel = {off: sym for off, sym in e["relocs"]}
    o = compile_c(cpath, thumb)
    mine, mrel_full = text_relocs(o)
    mrel = {off: nm for off, (nm, _t) in mrel_full.items()}
    size = len(orig)
    if len(mine) != size:
        print(">>> DIFIERE <<< tamano %d != %d" % (len(mine), size)); sys.exit(1)
    mt = bytearray(mine); ob = bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off + k < size:
                mt[off + k] = 0; ob[off + k] = 0
    if mt != ob:
        d = [i for i in range(size) if mt[i] != ob[i]]
        print(">>> DIFIERE <<< byte diff @0x%X (tras enmascarar relocs)" % d[0]); sys.exit(1)
    if mrel != orel:
        print(">>> DIFIERE <<< relocs difieren\n  tuyas=%s\n  orig =%s" % (mrel, orel)); sys.exit(1)
    print(">>> MATCH <<< %d bytes, %d relocs" % (size, len(orel)))
    sys.exit(0)

if __name__ == "__main__":
    main()
