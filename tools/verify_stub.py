#!/usr/bin/env python3
"""Verifica byte-exacto una C contra un asm_stub (para funciones stub-linked que
NO estan en func_index, p.ej. ov003). Parsea los `dcd` del stub como bytes orig,
detecta relocs (dcd <simbolo> no-hex), compila la C reloc-aware y compara
enmascarando las palabras relocalizadas.

    python tools/verify_stub.py <c> <stub.c> <func_name> [--thumb]
"""
import sys, os, re
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compile_c, text_relocs

def main():
    cpath, stubpath, name = sys.argv[1], sys.argv[2], sys.argv[3]
    thumb = "--thumb" in sys.argv
    orig = bytearray(); orel = {}
    off = 0
    for line in open(stubpath):
        m = re.search(r'dcd\s+(.+?)\s*$', line)
        if not m: continue
        tok = m.group(1).strip()
        hx = re.match(r'0x([0-9a-fA-F]{1,8})$', tok)
        if hx:
            orig += int(hx.group(1), 16).to_bytes(4, 'little')
        else:
            # a symbol reference -> reloc word (value unknown, mask it)
            orel[off] = tok
            orig += b'\x00\x00\x00\x00'
        off += 4
    o = compile_c(cpath, thumb)
    mine, mrel_full = text_relocs(o)
    mrel = {of: nm for of, (nm, _t) in mrel_full.items()}
    size = len(orig)
    if len(mine) != size:
        print(">>> DIFIERE <<< tamano %d != %d" % (len(mine), size)); sys.exit(1)
    mt = bytearray(mine); ob = bytearray(orig)
    for o2 in set(mrel) | set(orel):
        for k in range(4):
            if o2 + k < size: mt[o2+k] = 0; ob[o2+k] = 0
    if mt != ob:
        d = [i for i in range(size) if mt[i] != ob[i]]
        print(">>> DIFIERE <<< byte diff @0x%X" % d[0]); sys.exit(1)
    if mrel != orel:
        print(">>> DIFIERE <<< relocs difieren\n  tuyas=%s\n  orig =%s" % (mrel, orel)); sys.exit(1)
    print(">>> MATCH <<< %d bytes, %d relocs" % (size, len(orel)))
    sys.exit(0)

if __name__ == "__main__":
    main()
