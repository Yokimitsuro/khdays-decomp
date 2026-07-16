#!/usr/bin/env python3
"""Rebuild build/func_index.json from FIRST PRINCIPLES: the extracted module binaries plus the
dsd config (symbols.txt / relocs.txt / delinks.txt).

Why this exists: index_funcs.py reads build/delinks/*.o, which only ever contain the functions
that are still gaps. The moment a function has a .c it leaves those objects, so that script can
never index a finished function -- and a careless rebuild silently drops every function already
decompiled (this happened on 2026-07-17: 11055 entries -> 8789, and verify_idx could no longer
re-check anything finished).

A function's bytes are just the ROM at its address, and its relocations are in relocs.txt. Neither
depends on what has been decompiled, so this reconstruction is complete and stable: it indexes all
of them, done or not, and can be re-run at any time.

★ One deliberate difference: at a relocated word, a delink-derived entry holds the OBJECT's
placeholder while a reconstructed one holds the ROM's linked value. Everything else is byte
identical -- verified below by masking the relocated words and comparing the rest, which is
exactly what every consumer of this index already does (verify_idx.py, dedupprop.py and the
family scans all mask reloc'd words before comparing). So the two kinds of entry are
interchangeable in practice; do not "fix" this by zeroing the words, because the opcode byte of a
`bl` lives in the same word and must survive.

Default is a dry run that VERIFIES itself against the entries already in the index; pass --write
to merge the missing ones in.

Usage:  python tools/rebuild_index.py [--write]
"""
import glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WRITE = "--write" in sys.argv
INDEX_PATH = os.path.join(ROOT, "build", "func_index.json")

SEC_RE = re.compile(r"^\s*\.text\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")
SYM_RE = re.compile(r"^(\S+)\s+kind:(\w+)\(?([^,)]*),?[^)]*\)?[^a-z]*.*addr:0x([0-9a-fA-F]+)")
FUNC_RE = re.compile(r"^(\S+)\s+kind:function\((arm|thumb),size=0x([0-9a-fA-F]+)\)\s+addr:0x([0-9a-fA-F]+)")
REL_RE = re.compile(r"^from:0x([0-9a-fA-F]+)\s+kind:(\S+)\s+to:0x([0-9a-fA-F]+)\s+module:(\S+)")


def module_dirs():
    """Every dsd module directory, paired with the binary it was extracted from."""
    out = []
    main = os.path.join(ROOT, "config", "arm9")
    out.append((main, os.path.join(ROOT, "dsd_extract", "arm9", "arm9.bin")))
    for name in ("itcm", "dtcm"):
        d = os.path.join(main, name)
        if os.path.isdir(d):
            out.append((d, os.path.join(ROOT, "dsd_extract", "arm9", name + ".bin")))
    for d in sorted(glob.glob(os.path.join(main, "overlays", "ov*"))):
        ov = os.path.basename(d)
        out.append((d, os.path.join(ROOT, "dsd_extract", "arm9_overlays", ov + ".bin")))
    return out


def text_start(delinks_path):
    with open(delinks_path, encoding="utf-8", errors="replace") as f:
        for ln in f:
            m = SEC_RE.match(ln)
            if m:
                return int(m.group(1), 16)
    return None


# Pass 1: symbol address -> name, kept PER MODULE. Overlays share address ranges, so a global map
# is ambiguous: 0x02083e08 is a real function in both ov022 and ov023. relocs.txt names the target
# module for exactly this reason -- use it.
def mod_key(d):
    if d == os.path.join(ROOT, "config", "arm9"):
        return "main"
    b = os.path.basename(d)
    return "overlay(%d)" % int(b[2:]) if b.startswith("ov") and b[2:].isdigit() else b


by_mod = {}
for d, _bin in module_dirs():
    p = os.path.join(d, "symbols.txt")
    if not os.path.exists(p):
        continue
    m2 = by_mod.setdefault(mod_key(d), {})
    with open(p, encoding="utf-8", errors="replace") as f:
        for ln in f:
            m = SYM_RE.match(ln)
            if m:
                m2.setdefault(int(m.group(4), 16), m.group(1))


def candidate_mods(mod):
    """relocs.txt names the target module three ways: `main` / `itcm` / `dtcm`, `overlay(N)`, and
    `overlays(N,M)` -- the last for a target that could be in either of two overlays (they never
    share a slot at runtime, so dsd records the ambiguity rather than resolving it)."""
    m = re.match(r"^overlays\(([\d,]+)\)$", mod)
    if m:
        return ["overlay(%s)" % n for n in m.group(1).split(",")]
    return [mod]


def sym_at(t, mod):
    """Name for a reloc target, resolved inside the module(s) the reloc names.

    Three traps, each of which produced silently wrong names:
      - the address is tried AS-IS first, because data symbols can sit on an odd address
        (data_02041ae1 is real and distinct from data_02041ae0); &~1 is only the THUMB bit on a
        code target, so it is the fallback, not the rule;
      - the lookup is per module, because overlays overlap in address space (0x02083e08 is a real
        function in BOTH ov022 and ov023);
      - `overlays(N,M)` targets have to try each named overlay.
    """
    for key in candidate_mods(mod) + ["main"]:
        table = by_mod.get(key, {})
        if t in table:
            return table[t]
        if (t & ~1) in table:
            return table[t & ~1]
    return "0x%08x" % t

# Pass 2: rebuild each module's functions.
rebuilt = {}
for d, binpath in module_dirs():
    sp, rp, dp = (os.path.join(d, n) for n in ("symbols.txt", "relocs.txt", "delinks.txt"))
    if not (os.path.exists(sp) and os.path.exists(dp) and os.path.exists(binpath)):
        continue
    base = text_start(dp)
    if base is None:
        continue
    blob = open(binpath, "rb").read()
    mod = os.path.basename(d) if d != os.path.join(ROOT, "config", "arm9") else "main"

    rels = {}
    if os.path.exists(rp):
        with open(rp, encoding="utf-8", errors="replace") as f:
            for ln in f:
                m = REL_RE.match(ln)
                if m:
                    rels[int(m.group(1), 16)] = (int(m.group(3), 16), m.group(4))

    with open(sp, encoding="utf-8", errors="replace") as f:
        for ln in f:
            m = FUNC_RE.match(ln)
            if not m:
                continue
            name, mode, size, addr = m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16)
            off = addr - base
            if size == 0 or off < 0 or off + size > len(blob):
                continue
            r = sorted((a - addr, sym_at(t, tm))
                       for a, (t, tm) in rels.items() if addr <= a < addr + size)
            rebuilt[name] = {"hex": blob[off:off + size].hex(), "size": size,
                             "relocs": [list(x) for x in r], "module": mod, "mode": mode}

print("rebuilt from ROM+config: %d functions" % len(rebuilt))

index = {}
if os.path.exists(INDEX_PATH):
    index = json.load(open(INDEX_PATH))
print("current index: %d functions" % len(index))

def masked(entry):
    """hex with every reloc'd word zeroed -- the only place the ROM and the object legitimately
    disagree, and what every consumer compares on anyway."""
    b = bytearray.fromhex(entry["hex"])
    for off, _sym in entry["relocs"]:
        if off + 4 <= len(b):
            b[off:off + 4] = b"\x00\x00\x00\x00"
    return bytes(b)


# Self-check: for every function BOTH have, the reconstruction must agree once the relocated
# words are masked. If it does not, the reconstruction is wrong and must not be merged.
same = bad = 0
for n, e in index.items():
    if n not in rebuilt:
        continue
    got = rebuilt[n]
    ok = (masked(got) == masked(e) and got["size"] == e["size"]
          and [list(x) for x in got["relocs"]] == [list(x) for x in e["relocs"]])
    if ok:
        same += 1
    else:
        bad += 1
        if bad <= 5:
            print("  MISMATCH %s" % n)
            if masked(got) != masked(e):
                mg, me = masked(got), masked(e)
                d = [i for i in range(min(len(mg), len(me))) if mg[i] != me[i]]
                print("    bytes differ at %d offsets (first: %s), sizes %d vs %d"
                      % (len(d), d[:6], len(mg), len(me)))
            if [list(x) for x in got["relocs"]] != [list(x) for x in e["relocs"]]:
                print("    relocs: rebuilt=%s" % got["relocs"][:4])
                print("            index  =%s" % [list(x) for x in e["relocs"]][:4])
print("cross-check vs existing entries (reloc words masked): %d agree, %d DISAGREE" % (same, bad))

missing = [n for n in rebuilt if n not in index]
print("functions the index is missing: %d" % len(missing))

# A handful of disagreements is expected and harmless: relocs.txt only records relocations dsd
# resolved against real symbols, so a reference to a LINKER-defined symbol (ARM9_CTOR_START and
# friends) is invisible here. Those functions are already in the index and this script only ADDS
# missing entries, so their good entries are never touched. A large count would mean the
# reconstruction itself is broken, and that must not be merged.
if bad > 5:
    print("\nrefusing to merge: %d disagreements is too many to be linker symbols -- the"
          " reconstruction is wrong." % bad)
    sys.exit(1)
if bad:
    print("  (those %d are already in the index and are NOT overwritten; expected cause is a"
          " reloc to a linker-defined symbol, which relocs.txt does not record)" % bad)
if not WRITE:
    print("\ndry run; pass --write to merge the missing entries in.")
    sys.exit(0)

for n in missing:
    index[n] = rebuilt[n]
json.dump(index, open(INDEX_PATH, "w"))
print("merged. index now: %d functions" % len(index))
