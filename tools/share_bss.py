#!/usr/bin/env python3
"""Turn a function object's in-file .bss globals into references to the module's shared ones.

    python tools/share_bss.py <object.o> [more.o ...]

Why this exists (ov011, 2026-09-12)
-----------------------------------
The title scene of ov011 was one translation unit that DEFINED its two globals
(`int gCursor = 0; Ov011Scene *gpScene = 0;` at 0x0205e960/0x0205e964). mwccarm
addresses such zero-initialised globals off the `.bss` section symbol
(`ldr rX,=.bss ; ldr rY,[rX,#4]`) and, because they are scalars, lets their
loads move above stores to local aggregates. Several ROM functions can only be
reproduced by declaring the globals that way IN THE SAME FILE -- `extern`
declarations give the same alias class but a per-symbol pool word, so the load
offset differs -- and a function-per-file tree cannot define one global in many
files. The C is the genuine source shape; this pass only reconciles it with our
layout: after compiling a source that carries the marker line

    /* khdays: shared-bss */

every GLOBAL symbol the object defines in `.bss` becomes an undefined reference,
every relocation against the `.bss` section symbol is retargeted to the global
that sits at `.bss+0` (its addend is kept, so `.bss+4` still resolves to base+4),
and the `.bss` section is emptied. The module's delinked bss object keeps
defining the symbols exactly as before, so the link lays nothing new down and
the code bytes are untouched. Byte-exactness of the function is still proved by
tools/verify_idx.py on the UNSTRIPPED object (it accepts the `.bss` reloc when
the anchor global's symbols.txt address is the inferred base).

The same holds for INITIALISED statics (ov027, 2026-09-17): the game-over scene
keeps its choice cursor as `int nChoice = 1;` in `.data`, and mwccarm emits TWO
pool words for it -- the symbol itself where its address is passed to a callee,
and the `.data` section word (offset folded into the load) for every value
access. An `extern` declaration merges both into one word and the function comes
out four bytes short. So a marked source may define `.data` globals as well;
they are handed back to the module's delinked data object the same way, and
verify_idx.py has already proved their bytes against the ROM.
"""
import struct
import sys
from pathlib import Path

SHDR = struct.Struct("<IIIIIIIIII")   # name type flags addr offset size link info align entsize
SYM = struct.Struct("<IIIBBH")        # name value size info other shndx
SHT_SYMTAB, SHT_RELA, SHT_REL = 2, 4, 9
STB_GLOBAL, STT_SECTION = 1, 3
MARKERS = ("/* khdays: shared-bss */", "/* khdays: shared-data */")
SHARED_SECTIONS = (".bss", ".data")


def wants_sharing(source_path):
    try:
        text = Path(source_path).read_text(encoding="utf-8", errors="replace")
    except OSError:
        return False
    return any(marker in text for marker in MARKERS)


def share(path, log=sys.stderr):
    """Rewrite one object in place; returns a short report string or None if untouched."""
    path = Path(path)
    buf = bytearray(path.read_bytes())
    e_shoff, = struct.unpack_from("<I", buf, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", buf, 0x2E)
    shdrs = [SHDR.unpack_from(buf, e_shoff + i * e_shentsize) for i in range(e_shnum)]
    shstr = shdrs[e_shstrndx]

    def cstr(tab, off):
        end = buf.index(b"\0", tab[4] + off)
        return buf[tab[4] + off:end].decode("ascii", "replace")

    names = [cstr(shstr, sh[0]) for sh in shdrs]
    symtab_index = next(i for i, sh in enumerate(shdrs) if sh[1] == SHT_SYMTAB)
    symtab = shdrs[symtab_index]
    strtab = shdrs[symtab[6]]
    nsyms = symtab[5] // SYM.size
    syms = [SYM.unpack_from(buf, symtab[4] + i * SYM.size) for i in range(nsyms)]
    reports = []
    for section_name in SHARED_SECTIONS:
        if section_name not in names:
            continue
        sec_index = names.index(section_name)
        section_sym = None
        anchor = None
        defined = []
        for i, (st_name, st_value, st_size, st_info, st_other, st_shndx) in enumerate(syms):
            if st_shndx != sec_index:
                continue
            if st_info & 0xF == STT_SECTION:
                section_sym = i
            elif st_info >> 4 == STB_GLOBAL:
                defined.append(i)
                if st_value == 0:
                    anchor = i
        if not defined:
            continue
        if anchor is None:
            raise SystemExit("%s: no global at %s+0 to anchor the shared section" % (path, section_name))
        # 1. relocations against the section symbol -> the anchor global, addend kept
        retargeted = 0
        for sh in shdrs:
            if sh[1] not in (SHT_REL, SHT_RELA) or sh[6] != symtab_index:
                continue
            entsize = 12 if sh[1] == SHT_RELA else 8
            for off in range(sh[4], sh[4] + sh[5], entsize):
                r_info, = struct.unpack_from("<I", buf, off + 4)
                if section_sym is not None and (r_info >> 8) == section_sym:
                    struct.pack_into("<I", buf, off + 4, (anchor << 8) | (r_info & 0xFF))
                    retargeted += 1
        # 2. the defined globals become undefined references
        for i in defined:
            st_name, st_value, st_size, st_info, st_other, st_shndx = syms[i]
            SYM.pack_into(buf, symtab[4] + i * SYM.size, st_name, 0, 0, st_info, st_other, 0)
            syms[i] = (st_name, 0, 0, st_info, st_other, 0)
        # 3. an empty section: nothing for the linker to lay down
        sh = list(shdrs[sec_index])
        sh[5] = 0
        SHDR.pack_into(buf, e_shoff + sec_index * e_shentsize, *sh)
        reports.append("%s: shared %s -> %s (%d relocs retargeted, %d globals undefined)" % (
            path.name, section_name, cstr(strtab, syms[anchor][0]), retargeted, len(defined)))
    if not reports:
        return None
    path.write_bytes(bytes(buf))
    report = "; ".join(reports)
    print(report, file=log)
    return report


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    for arg in sys.argv[1:]:
        if share(arg) is None:
            print("%s: no defined .bss/.data globals, untouched" % arg)


if __name__ == "__main__":
    main()
