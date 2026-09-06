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

def _read_addends(o_path):
    """RELA r_addend per .text offset (absent -> treated as 0 by the caller). mwccarm
    emits .rela.text, so a struct-field address carries its field offset here rather than
    in the (zeroed) literal-pool word."""
    from elftools.elf.elffile import ELFFile
    out = {}
    elf = ELFFile(open(o_path, "rb"))
    for s in elf.iter_sections():
        if s.name == ".rela.text":
            for r in s.iter_relocations():
                if "r_addend" in r.entry:
                    out[r["r_offset"]] = r["r_addend"]
    return out


def _verified_local_data_relocs(o_path, original_relocs, mine_relocs, addends, module):
    """Accept compiler-local DATA labels only when their complete section is proved.

    Automatic aggregate initializers are emitted as local labels such as @38 or
    the section symbol .rodata. A delinked gap cannot preserve those names and
    records the public data label instead. The spelling may differ while the
    relocation is exact, but only if all local labels imply one final section base
    and the complete emitted section matches the ROM-derived DATA index byte-exact.
    Relocated DATA sections remain on the ordinary named-symbol verification path.
    """
    from elftools.elf.elffile import ELFFile
    import re

    gap_unit = re.search(r"@(ov[0-9]+|main|itcm)(?:_|$)", module or "")
    if gap_unit:
        module = gap_unit.group(1)

    index_path = os.path.join(ROOT, "build", "data_index.json")
    if not os.path.exists(index_path):
        return set(), ""
    with open(index_path, encoding="utf-8") as fh:
        data_index = json.load(fh)
    if isinstance(data_index, dict) and "symbols" in data_index:
        data_index = data_index["symbols"]

    with open(o_path, "rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return set(), ""

        inferred = {}
        accepted = set()
        for off, (mine_name, reloc_type) in mine_relocs.items():
            expected_name = original_relocs.get(off)
            if expected_name is None or mine_name == expected_name or reloc_type != 2:
                continue
            expected_address = SYM_ADDR.get(expected_name)
            if expected_address is None:
                continue
            candidates = symtab.get_symbol_by_name(mine_name) or []
            local = None
            for symbol in candidates:
                section_index = symbol["st_shndx"]
                if (symbol["st_info"]["bind"] == "STB_LOCAL"
                        and isinstance(section_index, int)):
                    section = elf.get_section(section_index)
                    if section is not None and section.name in (".rodata", ".data", ".ctor"):
                        local = (symbol, section)
                        break
            if local is None:
                continue
            symbol, section = local
            relative = symbol["st_value"] + addends.get(off, 0)
            base = expected_address - relative
            previous = inferred.get(section.name)
            if previous is not None and previous[0] != base:
                return set(), ""
            inferred[section.name] = (base, section.data())
            accepted.add(off)

        if not accepted:
            return set(), ""

        notes = []
        for section_name, (base, emitted) in inferred.items():
            relocation_section = elf.get_section_by_name(".rela" + section_name)
            if relocation_section is None:
                relocation_section = elf.get_section_by_name(".rel" + section_name)
            if relocation_section is not None and relocation_section.num_relocations():
                return set(), ""

            expected = [None] * len(emitted)
            for entry in data_index.values():
                if entry.get("module") != module or entry.get("section") != section_name[1:]:
                    continue
                start = entry.get("addr")
                raw = bytes.fromhex(entry.get("hex", ""))
                end = start + len(raw) if start is not None else None
                if start is None or end <= base or start >= base + len(emitted):
                    continue
                if entry.get("relocs"):
                    return set(), ""
                lo = max(start, base)
                hi = min(end, base + len(emitted))
                for address in range(lo, hi):
                    value = raw[address - start]
                    slot = address - base
                    if expected[slot] is not None and expected[slot] != value:
                        return set(), ""
                    expected[slot] = value
            if any(value is None for value in expected) or bytes(expected) != emitted:
                return set(), ""
            notes.append("%s %d bytes @0x%08x" % (section_name, len(emitted), base))

    return accepted, ", ".join(notes)


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
    maddend = _read_addends(o)
    local_relocs, local_data_note = _verified_local_data_relocs(
        o, orel, mrel_full, maddend, e.get("module")
    )
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

        def _mine_addr(off):
            """Final target address of our reloc = symbol address + addend. mwcc emits a
            struct-field reference (data_X.fieldN) as a reloc against the struct's base
            symbol data_X with r_addend = the field offset, so the address it resolves to
            is data_X + offset -- which equals the standalone symbol the ROM was delinked
            against. Only ARM data relocs (R_ARM_ABS32, type 2) carry a meaningful address
            addend; the pc-relative call reloc (type 1) uses -8 as a pipeline fixup, not an
            address offset, so it is excluded."""
            a = SYM_ADDR.get(mrel[off])
            if a is None:
                return None
            typ = mrel_full[off][1]
            return a + (maddend.get(off, 0) if typ == 2 else 0)

        same = all(
            (o in orel and (mrel[o] == orel[o]
                            or (_mine_addr(o) is not None
                                and _mine_addr(o) == SYM_ADDR.get(orel[o]))
                            or o in local_relocs))
            or _abs_ok(o)
            for o in mrel) and all(o in mrel for o in orel)
        if not same:
            print(">>> DIFIERE <<< relocs difieren\n  tuyas=%s\n  orig =%s" % (mrel, orel)); sys.exit(1)
    suffix = ("; " + local_data_note + " verified") if local_data_note else ""
    print(">>> MATCH <<< %d bytes, %d relocs%s" % (size, len(orel), suffix))
    sys.exit(0)

if __name__ == "__main__":
    main()
