#!/usr/bin/env python3
"""Verifica byte-exacto una C contra el binario MAIN (build/build/arm9.bin, base
0x02000000) + config/arm9/relocs.txt, para funciones main-region stub-linked no
carveadas (no aparecen en func_index; match.py --obj no las encuentra en el gap).

    python tools/verify_main.py <c> <func_name> [--thumb]

Companion de verify_bin.py (que hace lo mismo para overlays). Reloc-aware: enmascara
los 4 bytes de cada offset con reloc antes de comparar, y exige que los offsets de
reloc coincidan (nombres/targets pueden diferir cosméticamente).
"""
import sys, os, re
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs

BASE = 0x02000000

def main():
    cpath, name = sys.argv[1], sys.argv[2]
    thumb = "--thumb" in sys.argv
    ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    addr = int(name.split("_")[-1], 16)
    data = open(os.path.join(ROOT, "build", "build", "arm9.bin"), "rb").read()
    size = None
    for line in open(os.path.join(ROOT, "config/arm9/symbols.txt")):
        m = re.match(r'%s\s+kind:function\((?:arm|thumb),size=0x([0-9a-f]+)\)' % re.escape(name), line)
        if m: size = int(m.group(1), 16); break
    if size is None: raise SystemExit("no size for " + name)
    orig = bytearray(data[addr-BASE:addr-BASE+size])
    orel = {}
    for line in open(os.path.join(ROOT, "config/arm9/relocs.txt")):
        m = re.match(r'from:0x([0-9a-f]+)\s+kind:(\S+)\s+to:0x([0-9a-f]+)', line)
        if not m: continue
        fr = int(m.group(1), 16)
        if addr <= fr < addr+size:
            orel[fr-addr] = m.group(3)
    o = compile_c(cpath, thumb)
    mine, mrel_full = text_relocs(o)
    mrel = {of: nm for of, (nm, _t) in mrel_full.items()}
    if len(mine) != size:
        print(">>> DIFIERE <<< tamano %d != %d" % (len(mine), size)); sys.exit(1)
    mt = bytearray(mine); ob = bytearray(orig)
    for of in set(mrel) | set(orel):
        for k in range(4):
            if of+k < size: mt[of+k] = 0; ob[of+k] = 0
    if mt != ob:
        d = [i for i in range(size) if mt[i] != ob[i]]
        print(">>> DIFIERE <<< byte diff @0x%X" % d[0]); sys.exit(1)
    if set(mrel) != set(orel):
        print(">>> DIFIERE <<< reloc offsets: tuyas=%s orig=%s" % (sorted(mrel), sorted(orel))); sys.exit(1)
    print(">>> MATCH <<< %d bytes, %d relocs" % (size, len(orel)))
    sys.exit(0)

if __name__ == "__main__":
    main()
