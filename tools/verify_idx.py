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


def _load_sym_addrs():
    """symbol -> address, so the reloc check can compare addresses, not spellings."""
    out = {}
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, 'config')):
        if 'symbols.txt' not in files:
            continue
        with open(os.path.join(dirpath, 'symbols.txt'), encoding='utf-8', errors='replace') as fh:
            for line in fh:
                parts = line.split()
                if len(parts) < 2:
                    continue
                for tok in parts[1:]:
                    if tok.startswith('addr:'):
                        try:
                            out[parts[0]] = int(tok[5:], 16)
                        except ValueError:
                            pass
                        break
    return out


def _load_abs_syms():
    """Linker-ABSOLUTE symbols from build/arm9.lcf, e.g. `OVERLAY_12_ID = 12;`.

    NitroSDK's FS_OVERLAY_ID(name) is `(u32)&SDK_OVERLAY_name_ID`, i.e. the ADDRESS of an
    absolute symbol, so the source takes an address and mwcc emits a literal-pool word plus a
    relocation. The ROM is already linked: that word holds the plain value (12) and points into
    no section, so dsd records no relocation there. Our object legitimately has one more reloc
    than the ROM, and the real build resolves it from arm9.lcf -- func_ov001_0204ce40 has shipped
    in calls/ that way with the gate at 306. Without this the tool reports `relocs difieren` on
    C the build accepts, which is the one failure mode that makes it disagree with the gate.
    """
    out = {}
    lcf = os.path.join(ROOT, "build", "arm9.lcf")
    if not os.path.exists(lcf):
        return out
    import re as _re
    pat = _re.compile(r'^\s*(\w+)\s*=\s*(0[xX][0-9a-fA-F]+|\d+)\s*;')
    with open(lcf, encoding='utf-8', errors='replace') as fh:
        for line in fh:
            m = pat.match(line)
            if m:
                out[m.group(1)] = int(m.group(2), 0)
    return out


SYM_ADDR = _load_sym_addrs()
ABS_SYM = _load_abs_syms()
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
        # Two symbols may share one address, and func_020234e8 REQUIRES it: the
        # ROM's literal pool holds 0x0204be08 in two separate entries, and mwcc
        # emits two entries only for two distinct symbols. func_index.json resolves
        # an address to its FIRST symbol, so a legitimate alias reads as a mismatch
        # here. Compare ADDRESSES when the spellings differ -- only a genuine
        # address difference is an error.
        def _abs_ok(off):
            """Our reloc points at a linker-absolute symbol and the ROM word holds its value."""
            val = ABS_SYM.get(mrel[off])
            if val is None or off + 4 > size:
                return False
            rom = int.from_bytes(orig[off:off + 4], "little")
            if rom != val:
                return False
            o = orel.get(off)
            # The ROM side is either absent (plain literal, no reloc) or recorded by the index
            # as the literal itself, e.g. '0x0000001c'.
            if o is None:
                return True
            try:
                return int(o, 16) == val
            except (TypeError, ValueError):
                return False

        same = all(
            (o in orel and (mrel[o] == orel[o]
                            or (SYM_ADDR.get(mrel[o]) is not None
                                and SYM_ADDR.get(mrel[o]) == SYM_ADDR.get(orel[o]))))
            or _abs_ok(o)
            for o in mrel) and all(o in mrel for o in orel)
        if not same:
            print(">>> DIFIERE <<< relocs difieren\n  tuyas=%s\n  orig =%s" % (mrel, orel)); sys.exit(1)
    print(">>> MATCH <<< %d bytes, %d relocs" % (size, len(orel)))
    sys.exit(0)

if __name__ == "__main__":
    main()
