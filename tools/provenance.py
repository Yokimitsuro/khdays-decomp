#!/usr/bin/env python3
"""Did a function's bytes in the LAST LINK come from its C file -- not a gap or a stub?

    python tools/provenance.py <func> [<func> ...]
    python tools/provenance.py --all        # every .c under calls/ and auto/

A byte-exact module proves nothing about one file: gen_delinks.py drops any source on
known_mismatches.txt (and any function with no source) from delinks.txt, and dsd fills
the hole with original bytes (`_dsd_gap@...o`). This reads what the link wrote down and
runs nothing, so a verdict is exactly as fresh as build/arm9.elf (date printed).

  build/arm9.elf.xMAP     which object supplied which symbol at which address and size
  build/objects.txt       bare object name -> path (calls/, auto/, asm_stubs/, delinks/)
  build/func_index.json   expected size and module;  config/**/symbols.txt  expected address
  days.nds                overlays compared to the ROM itself via ndspy, not dsd_extract/.
                          dsd_extract/arm9_overlays/ov028.bin legitimately differs from the
                          ROM in 975 bytes: it is the build's INPUT, and the build applies
                          ov028's protection to reach the ROM form. Do NOT "repair" it by
                          re-extracting -- that changes the input and breaks the module. main/itcm/dtcm are not checked here.

Verdicts (first one that applies):
  MODULE    overlay binary missing or differs from the ROM -- nothing below counts
  GAP       supplied by a _dsd_gap object: dsd filled it with original bytes
  STUB      supplied by an asm_stubs/ object (real C sits unused; see tools/audit_shadowed.py)
  WRONGSYM  the object at the expected address defines some other name (link-blocker class 3)
  MISPLACED symbol exists but at another address, or with another size, than the index says
  STALE     the .c is newer than its object, or the object is newer than the ELF
  C         supplied by that .c, at the right address, exact size, module exact
Names with no func_index entry (data tables under auto/) are skipped, not failed.
"""
import glob, json, os, re, sys, time
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from verify_idx import SYM_ADDR                      # symbols.txt addresses, already parsed there

IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
ELF = os.path.join(ROOT, "build", "arm9.elf")
MAP_LINE = re.compile(r"^\s+([0-9a-fA-F]{8}) ([0-9a-fA-F]{8}) \.text\s+(\S+)\t\((\S+)\)$")

def load_map():
    """symbol -> (addr, size, object) from the address table; mapping symbols ($a, .text) skipped."""
    out = {}
    for ln in open(ROOT + "/build/arm9.elf.xMAP", encoding="utf-8", errors="replace"):
        m = MAP_LINE.match(ln)
        if m and not m.group(3).startswith(("$", ".")):
            out[m.group(3)] = (int(m.group(1), 16), int(m.group(2), 16), m.group(4))
    return out

def load_objects():
    return {os.path.basename(p): p for p in
            (ln.strip().strip('"') for ln in open(ROOT + "/build/objects.txt")) if p}

_rom = {}
def module_exact(mod):
    """True/False for overlays (against the ROM), None for main/itcm/dtcm, which the linked-module check covers."""
    if not mod.startswith("ov"):
        return None
    if not _rom:
        import ndspy.rom
        _rom.update(ndspy.rom.NintendoDSRom.fromFile(os.path.join(ROOT, "days.nds")).loadArm9Overlays())
    built = os.path.join(ROOT, "build", "build", "arm9_%s.bin" % mod)
    return os.path.exists(built) and open(built, "rb").read() == _rom[int(mod[2:])].data

def verdict(name, MAP, OBJS):
    e = IDX[name]
    if module_exact(e["module"]) is False:
        return "MODULE", e["module"] + " differs from the ROM"
    want = SYM_ADDR.get(name)
    if name not in MAP:
        holder = next((s for s, (a, sz, o) in MAP.items() if a == want and sz), None)
        return ("WRONGSYM", "0x%08x is defined as %s" % (want, holder)) if holder else ("GAP", "no object defines it")
    addr, size, obj = MAP[name]
    if obj.startswith("_dsd_gap@"):
        return "GAP", obj
    path = OBJS.get(obj, "")
    if "asm_stubs" in path.replace("\\", "/"):
        return "STUB", os.path.relpath(path, ROOT)
    if addr != want or size != e["size"]:
        return "MISPLACED", "map 0x%08x/%d vs index 0x%08x/%d" % (addr, size, want or 0, e["size"])
    stem = os.path.relpath(path, ROOT)[len("build") + 1:-2]
    src = next((stem + ext for ext in (".c", ".cpp") if os.path.exists(os.path.join(ROOT, stem + ext))), None)
    if src is None:
        return "STALE", "no source next to " + obj
    t_src, t_obj, t_elf = (os.path.getmtime(os.path.join(ROOT, p)) for p in (src, os.path.relpath(path, ROOT), "build/arm9.elf"))
    if t_src > t_obj or t_obj > t_elf:
        return "STALE", "%s edited after its object or ELF" % src
    return "C", src

def all_names():
    """Every function we claim as decompiled C: one .c under calls/ or auto/."""
    out = set()
    for b in ("src", "libs"):
        for ext in ("*.c", "*.cpp"):
            for q in glob.glob(os.path.join(ROOT, b, "**", ext), recursive=True):
                q = q.replace(os.sep, "/")
                if "/asm_stubs/" not in q and ("/calls/" in q or "/auto/" in q):
                    out.add(os.path.basename(q).rsplit(".", 1)[0])
    return sorted(out)


def main():
    names = all_names() if "--all" in sys.argv else sys.argv[1:]
    print("ELF from", time.strftime("%Y-%m-%d %H:%M", time.localtime(os.path.getmtime(ELF))))
    MAP, OBJS = load_map(), load_objects()
    counts = {}
    for n in names:
        if n not in IDX:
            counts["skipped(not a function)"] = counts.get("skipped(not a function)", 0) + 1
            continue
        v, why = verdict(n, MAP, OBJS)
        counts[v] = counts.get(v, 0) + 1
        if v != "C" or "--all" not in sys.argv:
            print("%-9s %-28s %s" % (v, n, why))
    print(counts)
    sys.exit(0 if set(counts) <= {"C", "skipped(not a function)"} else 1)

if __name__ == "__main__":
    main()
