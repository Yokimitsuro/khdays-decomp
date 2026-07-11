#!/usr/bin/env python3
"""Verifica byte-exacto una C contra el binario del overlay (bytes exactos de la
ROM) + relocs.txt, para funciones stub-linked no presentes en func_index.

    python tools/verify_bin.py <c> <func_name> <ov_num> [--thumb]
"""
import sys, os, re
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs

# overlay base addresses (from list_segments / delinks.txt .text start)
OV_BASE = {"003": 0x0204cac0, "010": 0x0204cac0, "013": 0x0207fa40,
           "019": 0x0207fa40, "028": 0x0208a7e0, "029": 0x020b2ee0,
           "302": 0x020cbf20, "294": 0x020d1980, "295": 0x020d37a0,
           "296": 0x020d55c0, "301": 0x020cbf20, "234": 0x020cbf20,
           "007": 0x0204cac0, "166": 0x020cbf20, "115": 0x020cbf20, "031": 0x020b3220, "050": 0x020b5a20, "070": 0x020b8100, "088": 0x020ba7c0,
           "032": 0x020b3220, "034": 0x020b3220, "052": 0x020b5a20, "053": 0x020b5a20, "072": 0x020b8100, "073": 0x020b8100, "090": 0x020ba7c0,
           "036": 0x020b3220, "055": 0x020b5a20, "075": 0x020b8100, "092": 0x020ba7c0, "012": 0x0205ac40,
           "044": 0x020b3220, "063": 0x020b5a20, "082": 0x020b8100, "099": 0x020ba7c0, "017": 0x0207fa40,
           "057": 0x020b5a20, "064": 0x020b5a20, "077": 0x020b8100, "083": 0x020b8100, "094": 0x020ba7c0, "100": 0x020ba7c0,
           "069": 0x020b8100}

def main():
    cpath, name, ov = sys.argv[1], sys.argv[2], sys.argv[3]
    thumb = "--thumb" in sys.argv
    ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    addr = int(name.split("_")[-1], 16)
    base = OV_BASE[ov]
    binp = os.path.join(ROOT, "build", "build", "arm9_ov%s.bin" % ov)
    data = open(binp, "rb").read()
    # size from symbols.txt
    size = None
    for line in open(os.path.join(ROOT, "config/arm9/overlays/ov%s/symbols.txt" % ov)):
        m = re.match(r'%s\s+kind:function\((?:arm|thumb),size=0x([0-9a-f]+)\)' % re.escape(name), line)
        if m: size = int(m.group(1), 16); break
    if size is None: raise SystemExit("no size for " + name)
    orig = bytearray(data[addr-base:addr-base+size])
    orel = {}
    for line in open(os.path.join(ROOT, "config/arm9/overlays/ov%s/relocs.txt" % ov)):
        m = re.match(r'from:0x([0-9a-f]+)\s+kind:(\S+)\s+to:0x([0-9a-f]+)', line)
        if not m: continue
        fr = int(m.group(1), 16)
        if addr <= fr < addr+size:
            orel[fr-addr] = m.group(3)  # keep target addr as the reloc key
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
    # reloc offsets must line up (names/targets differ cosmetically -> just check offsets)
    if set(mrel) != set(orel):
        print(">>> DIFIERE <<< reloc offsets: tuyas=%s orig=%s" % (sorted(mrel), sorted(orel))); sys.exit(1)
    print(">>> MATCH <<< %d bytes, %d relocs" % (size, len(orel)))
    sys.exit(0)

if __name__ == "__main__":
    main()
