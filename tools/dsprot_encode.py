#!/usr/bin/env python3
"""Post-compile step for the DS Protect 1.10 units of ov028: encrypt their marked ranges.

DS Protect keeps parts of its checks encrypted in the ROM. In the source a range is opened
and closed by two hand-written markers (src/overlays/ov028/dsprot/dsprot_ranges.h) that carry
the same 16-bit key as the word 0xEB00kkkk; at run time the opening marker decrypts the
instructions up to the matching key and the closing one encrypts them again. The library's
build encrypted every range after compiling each unit, before linking -- which is why no call
inside a range may need a relocation. This does the same to our objects:

* every `.text` section of the object becomes `.rodata` (the ROM keeps the encrypted code in
  the overlay's read-only data, which is where the delinks place it);
* between the key word of each opening marker and the next copy of that key, every word is
  encoded with the library's scheme: bytes 0 and 1 XOR a modified-RC4 keystream, byte 2 XOR 1,
  byte 3 kept. The RC4 key is the key word repeated four times with its first and last bytes
  inverted, and its key schedule walks S from 255 down to 0.

    python tools/dsprot_encode.py <object.o>
"""

from __future__ import annotations

import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE_DIR = "src/overlays/ov028/dsprot/"

SHT_REL, SHT_RELA = 9, 4
SHF_ALLOC = 0x2
SHDR = struct.Struct("<IIIIIIIIII")

# Opening marker: stmfd sp!,{r0-r7}; mov r0,#6; add r0,pc,r0,lsl #1; bl <start>; ldmfd sp!,{r0-r7};
# b +8; .word key. The bl word is left out of the match (it carries a relocation).
OPEN_MARKER = (0xE92D00FF, 0xE3A00006, 0xE08F0080, None, 0xE8BD00FF, 0xEA000000)
KEY_HIGH = 0xEB000000


def wants_encoding(src_path) -> bool:
    try:
        rel = Path(src_path).resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return False
    return rel.startswith(SOURCE_DIR)


def _rc4_init(key: list[int]) -> dict:
    s = list(range(256))
    j = 0
    k = 0
    for i in range(255, -1, -1):          # the library walks S downwards
        t = s[i]
        j = (j + key[k] + t) & 0xFF
        s[i], s[j] = s[j], t
        k = (k + 1) % len(key)
    return {"i": 0, "j": 0, "s": s}


def _rc4_byte(state: dict) -> int:
    s = state["s"]
    i = (state["i"] + 1) & 0xFF
    a = s[i]
    j = (a + state["j"]) & 0xFF
    b = s[j]
    state["i"], state["j"] = i, j
    s[j], s[i] = a, b
    return s[(a + b) & 0xFF]


def range_key(key_word: int) -> list[int]:
    key = [(key_word >> (8 * (i % 4))) & 0xFF for i in range(16)]
    key[0] ^= 0xFF
    key[15] ^= 0xFF
    return key


def code_range(data: bytearray, start: int, count: int, key_word: int) -> None:
    """Encode (or decode) `count` words at byte offset `start` in place."""
    state = _rc4_init(range_key(key_word))
    for n in range(count):
        o = start + 4 * n
        data[o] ^= _rc4_byte(state)
        data[o + 1] ^= _rc4_byte(state)
        data[o + 2] ^= 0x01


def find_ranges(data: bytes, what: str = "section"):
    """(start_offset, word_count, key_word) of every marked range, in order."""
    words = [struct.unpack_from("<I", data, o)[0] for o in range(0, len(data) - 3, 4)]
    ranges = []
    n = 0
    while n + 7 <= len(words):
        if all(p is None or words[n + k] == p for k, p in enumerate(OPEN_MARKER)) \
                and words[n + 6] & 0xFFFF0000 == KEY_HIGH:
            key_word = words[n + 6]
            first = n + 7
            end = first
            while end < len(words) and words[end] != key_word:
                end += 1
            if end == len(words):
                raise ValueError(f"{what}: range {key_word:#010x} is never closed")
            ranges.append((4 * first, end - first, key_word))
            n = end + 1
            continue
        n += 1
    return ranges


def encode(obj_path) -> int:
    path = Path(obj_path)
    buf = bytearray(path.read_bytes())
    if buf[:4] != b"\x7fELF":
        raise ValueError(f"{path.name}: not an ELF object")
    e_shoff, = struct.unpack_from("<I", buf, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", buf, 0x2E)
    shdrs = [list(SHDR.unpack_from(buf, e_shoff + i * e_shentsize)) for i in range(e_shnum)]
    strtab = shdrs[e_shstrndx]

    def name_of(index):
        off = strtab[4] + shdrs[index][0]
        return bytes(buf[off:buf.index(b"\0", off)]).decode()

    # a ".rodata" name for the code sections: reuse the string or append one to .shstrtab
    names = bytes(buf[strtab[4]:strtab[4] + strtab[5]])
    at = names.find(b".rodata\0")
    if at < 0:
        table = names + b".rodata\0"
        while len(buf) % 4:
            buf.append(0)
        strtab[4] = len(buf)
        strtab[5] = len(table)
        buf += table
        at = len(names)
    reloc_offsets = {}
    for h in shdrs:
        if h[1] in (SHT_REL, SHT_RELA):
            entry = 12 if h[1] == SHT_RELA else 8
            reloc_offsets.setdefault(h[7], set()).update(
                struct.unpack_from("<I", buf, o)[0] for o in range(h[4], h[4] + h[5], entry))
    total = 0
    for index, h in enumerate(shdrs):
        if name_of(index) != ".text" or not h[5]:
            continue
        data = bytearray(buf[h[4]:h[4] + h[5]])
        for start, count, key_word in find_ranges(data, f"{path.name} section {index}"):
            inside = [o for o in reloc_offsets.get(index, ()) if start <= o < start + 4 * count]
            if inside:
                raise ValueError(f"{path.name}: relocation inside encrypted range {key_word:#010x} "
                                 f"at +0x{min(inside):x}; calls in a range must go through pointers")
            code_range(data, start, count, key_word)
            total += 1
        buf[h[4]:h[4] + h[5]] = data
        h[0] = at
        h[2] = SHF_ALLOC
    for i, h in enumerate(shdrs):
        SHDR.pack_into(buf, e_shoff + i * e_shentsize, *h)
    path.write_bytes(bytes(buf))
    return total


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit(__doc__)
    print(f"{sys.argv[1]}: {encode(sys.argv[1])} range(s) encrypted")


if __name__ == "__main__":
    main()
