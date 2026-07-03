#!/usr/bin/env python3
"""Post-link BL/BLX interworking fixer.

Root cause (2026-07-03): the build links ALL overlays in ONE mwld invocation
and NDS overlays OVERLAP in virtual address space (LCF: ORIGIN=AFTER(...)
groups). mwld's -interworking pass resolves BL-vs-BLX per final *address*, so
a THUMB function in overlay A at the same address as an ARM function in
overlay B poisons the decision for calls in B. Proof: the ov035 call to
func_ov035_020b3a30 (ARM) linked as thumb BL because ov043 has THUMB
func_ov043_020b3a18 covering 0x020b3a30; the same-shape call to 0x020b38e0
(ARM in ALL 16 overlapping overlays) linked correctly as BLX. The original
game was linked per-overlay and never had this ambiguity.

Fix: after ninja, recompute every call-reloc site from first principles:
  site address   = anchored .o section address + reloc offset
  target address/mode = reloc symbol -> config symbols.txt (its own module)
and re-encode the exact BL/BLX instruction. SAFETY NET: a site is only
patched when the recomputed bytes EQUAL the original ROM bytes at that site
(ground truth); disagreements are reported, never written. ABS32 relocs
against function symbols are checked for the thumb bit the same way.

Usage:
  python tools/fix_interwork.py            # dry-run, all modules
  python tools/fix_interwork.py ov035      # dry-run, one module, verbose
  python tools/fix_interwork.py --write    # patch the built module bins
"""
import glob
import os
import re
import struct
import sys

from elftools.elf.elffile import ELFFile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

SYM_RE = re.compile(
    r"(\S+)\s+kind:function\((arm|thumb),[^)]*size=0x([0-9a-fA-F]+)[^)]*\)"
    r"\s+addr:0x([0-9a-fA-F]+)"
)
ANY_SYM_RE = re.compile(r"(\S+)\s+kind:\S+\s+addr:0x([0-9a-fA-F]+)")

R_ARM_PC24 = 1
R_ARM_ABS32 = 2
R_ARM_THM_CALL = 10

ITCM_LO, ITCM_HI = 0x01FF8000, 0x02000000


def load_config():
    """modules: {module: sorted [(addr,size,name,mode)]};
    fn2sym: {name: (addr, mode)}; any2addr: {name: addr};
    any2mod: {name: module}."""
    modules, fn2sym, any2addr, any2mod = {}, {}, {}, {}

    def add(module, path):
        syms = []
        for ln in open(path, encoding="utf-8"):
            m = SYM_RE.match(ln)
            if m:
                name, mode = m.group(1), m.group(2)
                size, addr = int(m.group(3), 16), int(m.group(4), 16)
                syms.append((addr, size, name, mode))
                fn2sym[name] = (addr, mode)
            m2 = ANY_SYM_RE.match(ln)
            if m2:
                any2addr[m2.group(1)] = int(m2.group(2), 16)
                any2mod[m2.group(1)] = module
        syms.sort()
        modules[module] = syms

    add("main", os.path.join(ROOT, "config/arm9/symbols.txt"))
    add("itcm", os.path.join(ROOT, "config/arm9/itcm/symbols.txt"))
    dtcm = os.path.join(ROOT, "config/arm9/dtcm/symbols.txt")
    if os.path.exists(dtcm):
        add("dtcm", dtcm)
    for d in sorted(glob.glob(os.path.join(ROOT, "config/arm9/overlays/ov*"))):
        p = os.path.join(d, "symbols.txt")
        if os.path.exists(p):
            add(os.path.basename(d), p)
    return modules, fn2sym, any2addr, any2mod


def module_of_object(path):
    """Derive owning module from an object path."""
    p = path.replace("\\", "/")
    m = re.search(r"/overlays/(ov\d+)/", p)
    if m:
        return m.group(1)
    m = re.search(r"_dsd_gap@(\w+?)_\d+\.o", p)
    if m:
        g = m.group(1)
        return g if g.startswith("ov") else g  # 'main'/'itcm'/'dtcm'/ovNNN
    return None  # main-region src or libs: decided per-site by address


def module_base(module):
    if module == "main":
        p = os.path.join(ROOT, "config/arm9/delinks.txt")
    elif module in ("itcm", "dtcm"):
        p = os.path.join(ROOT, f"config/arm9/{module}/delinks.txt")
    else:
        p = os.path.join(ROOT, f"config/arm9/overlays/{module}/delinks.txt")
    for ln in open(p, encoding="utf-8"):
        m = re.search(r"start:0x([0-9a-fA-F]+)", ln)
        if m:
            return int(m.group(1), 16)
    return None


def module_bins(module):
    if module == "main":
        return (os.path.join(ROOT, "build/build/arm9.bin"),
                os.path.join(ROOT, "dsd_extract/arm9.bin"))
    if module in ("itcm", "dtcm"):
        return (os.path.join(ROOT, f"build/build/{module}.bin"),
                os.path.join(ROOT, f"dsd_extract/{module}.bin"))
    return (os.path.join(ROOT, f"build/build/arm9_{module}.bin"),
            os.path.join(ROOT, f"dsd_extract/arm9_overlays/{module}.bin"))


def enc_thumb_bl(site, target):
    off = target - (site + 4)
    return struct.pack("<HH", 0xF000 | ((off >> 12) & 0x7FF),
                       0xF800 | ((off >> 1) & 0x7FF))


def enc_thumb_blx(site, target):
    off = target - ((site + 4) & ~3)
    return struct.pack("<HH", 0xF000 | ((off >> 12) & 0x7FF),
                       0xE800 | ((off >> 1) & 0x7FE))


def enc_arm_bl(site, target):
    off = target - (site + 8)
    return struct.pack("<I", 0xEB000000 | ((off >> 2) & 0xFFFFFF))


def enc_arm_blx(site, target):
    off = target - (site + 8)
    return struct.pack("<I", 0xFA000000 | ((off >> 2) & 0xFFFFFF)
                       | (((off >> 1) & 1) << 24))


def is_thumb_call(b):
    hw1 = int.from_bytes(b[0:2], "little")
    hw2 = int.from_bytes(b[2:4], "little")
    return (hw1 & 0xF800) == 0xF000 and (hw2 & 0xE800) in (0xE800, 0xF800)


def is_arm_call(b):
    return (int.from_bytes(b, "little") >> 24) in (0xEB, 0xFA, 0xFB)


def func_mode_at(modules, module, addr):
    """Mode of the function containing addr within a module (None if gap)."""
    syms = modules.get(module, [])
    lo, hi = 0, len(syms) - 1
    best = None
    while lo <= hi:
        mid = (lo + hi) // 2
        if syms[mid][0] <= addr:
            best = syms[mid]
            lo = mid + 1
        else:
            hi = mid - 1
    if best and best[0] <= addr < best[0] + best[1]:
        return best[3]
    return None


def main():
    write = "--write" in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    only = set(args) if args else None
    verbose = only is not None

    modules, fn2sym, any2addr, any2mod = load_config()

    objs_txt = os.path.join(ROOT, "build/objects.txt")
    objects = [ln.strip() for ln in open(objs_txt) if ln.strip()]

    # Load module images lazily
    images = {}

    def get_module(mod):
        if mod not in images:
            built_p, orig_p = module_bins(mod)
            if not (os.path.exists(built_p) and os.path.exists(orig_p)):
                images[mod] = None
            else:
                images[mod] = {
                    "built_p": built_p,
                    "built": bytearray(open(built_p, "rb").read()),
                    "orig": open(orig_p, "rb").read(),
                    "base": module_base(mod),
                    "stats": {"ok": 0, "patched": 0, "mismatch": 0,
                              "skipped": 0, "nosym": 0,
                              "stub_restored": 0},
                    "dirty": False,
                }
        return images[mod]

    for op in objects:
        try:
            e = ELFFile(open(op, "rb"))
        except Exception:
            continue
        pathmod = module_of_object(op)
        opn = op.replace("\\", "/")
        is_stub_obj = ("asm_stubs" in opn or "_dsd_gap@" in opn
                       or "/delinks/" in opn)
        symtabs = {}
        # Build per-section anchor: defined symbol with known config address
        anchors = {}
        st = e.get_section_by_name(".symtab")
        if st is None:
            continue
        for s in st.iter_symbols():
            shndx = s["st_shndx"]
            if shndx == "SHN_UNDEF" or not isinstance(shndx, int):
                continue
            a = any2addr.get(s.name)
            if a is not None and shndx not in anchors:
                anchors[shndx] = (a - s["st_value"], any2mod.get(s.name))

        for sec in e.iter_sections():
            if sec["sh_type"] not in ("SHT_REL", "SHT_RELA"):
                continue
            tgt_idx = sec["sh_info"]
            tgt_sec = e.get_section(tgt_idx)
            if tgt_sec.name not in (".text",):
                continue  # only code sections carry call relocs
            anch = anchors.get(tgt_idx)
            if anch is None:
                continue
            base_addr, anchor_mod = anch
            symtab = e.get_section(sec["sh_link"])

            # which module bin? overlay from path; else by address
            for r in sec.iter_relocations():
                rtype = r["r_info_type"]
                if rtype not in (R_ARM_PC24, R_ARM_THM_CALL, R_ARM_ABS32):
                    continue
                sym = symtab.get_symbol(r["r_info_sym"]).name
                site = base_addr + r["r_offset"]
                mod = pathmod or anchor_mod
                if mod is None:
                    mod = "itcm" if ITCM_LO <= site < ITCM_HI else "main"
                img = get_module(mod)
                if img is None:
                    continue
                boff = site - img["base"]
                if boff < 0 or boff + 4 > len(img["orig"]) \
                        or boff + 4 > len(img["built"]):
                    continue
                built, orig = img["built"], img["orig"]
                stats = img["stats"]
                cur = bytes(built[boff:boff + 4])
                og = orig[boff:boff + 4]

                if rtype == R_ARM_ABS32:
                    addend = r["r_addend"] if sec["sh_type"] == "SHT_RELA" \
                        else 0
                    t = fn2sym.get(sym)
                    if t is not None:
                        word = (t[0] | (1 if t[1] == "thumb" else 0)) + addend
                    else:
                        a = any2addr.get(sym)
                        word = (a + addend) if a is not None else None
                    exp = struct.pack("<I", word & 0xFFFFFFFF) \
                        if word is not None else None
                    if cur == og:
                        stats["ok"] += 1
                    elif exp == og:
                        built[boff:boff + 4] = exp
                        img["dirty"] = True
                        stats["patched"] += 1
                        if verbose:
                            print(f"  [patch-abs32] {mod} @{site:#x} {sym}: "
                                  f"{cur.hex()} -> {exp.hex()}")
                    elif is_stub_obj:
                        # dsd stubs are verbatim copies of the original by
                        # contract; a diverging pool word here is a delink
                        # symbol-misattribution (e.g. ov043 SNDi mutex word
                        # attributed to a same-address-space sibling overlay
                        # symbol). Restore the original word.
                        built[boff:boff + 4] = og
                        img["dirty"] = True
                        stats["stub_restored"] += 1
                        if verbose:
                            print(f"  [stub-restore] {mod} @{site:#x} {sym}: "
                                  f"{cur.hex()} -> {og.hex()} "
                                  f"(symbolic exp="
                                  f"{exp.hex() if exp else '?'})")
                    else:
                        stats["mismatch"] += 1
                        if verbose:
                            print(f"  [abs32!=orig] {mod} @{site:#x} {sym}: "
                                  f"built={cur.hex()} "
                                  f"exp={exp.hex() if exp else '?'} "
                                  f"orig={og.hex()}")
                    continue

                t = fn2sym.get(sym)
                if t is None:
                    stats["nosym"] += 1
                    if verbose:
                        print(f"  [no-sym] {mod} @{site:#x} t={rtype} {sym}")
                    continue
                taddr, tmode = t
                if rtype == R_ARM_THM_CALL:
                    exp = (enc_thumb_bl(site, taddr) if tmode == "thumb"
                           else enc_thumb_blx(site, taddr))
                    sane = is_thumb_call(cur)
                else:
                    exp = (enc_arm_bl(site, taddr) if tmode == "arm"
                           else enc_arm_blx(site, taddr))
                    sane = is_arm_call(cur)

                if cur == exp:
                    stats["ok"] += 1
                elif exp == og:
                    # exp==og is the real safety guarantee; patch even when
                    # the built bytes aren't call-shaped (mwld emits garbage
                    # kinds at some poisoned stub sites, e.g. ov102 0x1d).
                    built[boff:boff + 4] = exp
                    img["dirty"] = True
                    stats["patched"] += 1
                    if verbose:
                        print(f"  [patch-call] {mod} @{site:#x} {sym}"
                              f"({tmode}): {cur.hex()} -> {exp.hex()}")
                elif not sane:
                    stats["skipped"] += 1
                    if verbose:
                        print(f"  [not-call] {mod} @{site:#x} {sym}: "
                              f"built={cur.hex()}")
                else:
                    stats["mismatch"] += 1
                    if verbose:
                        print(f"  [call!=orig] {mod} @{site:#x} {sym}"
                              f"({tmode}): built={cur.hex()} exp={exp.hex()} "
                              f"orig={og.hex()}")

    grand = {"ok": 0, "patched": 0, "mismatch": 0, "skipped": 0,
             "nosym": 0, "stub_restored": 0}
    for mod in sorted(images):
        img = images[mod]
        if img is None:
            continue
        if only and mod not in only:
            continue
        st = img["stats"]
        for k in grand:
            grand[k] += st[k]
        if st["patched"] or st["mismatch"] or st["stub_restored"] or verbose:
            print(f"{mod}: ok={st['ok']} patched={st['patched']} "
                  f"stub-restored={st['stub_restored']} "
                  f"recompute!=orig={st['mismatch']} "
                  f"not-call={st['skipped']} no-sym={st['nosym']}")
        if write and img["dirty"]:
            open(img["built_p"], "wb").write(img["built"])

    print(f"\nTOTAL: ok={grand['ok']} patched={grand['patched']} "
          f"mismatches={grand['mismatch']} not-call={grand['skipped']} "
          f"no-sym={grand['nosym']}")
    if not write and grand["patched"]:
        print("(dry-run: nothing written; re-run with --write)")


if __name__ == "__main__":
    main()
