"""Per-object byte-exact comparison for a given module.

For each compiled `.o` under build/src/, find the matching delinked `.o`
under build/delinks/src/ and compare .text bytes (after masking relocations
so cross-object refs don't cause spurious diffs). Report match/mismatch per
file — this mirrors what objdiff shows on decomp.dev.
"""
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]


def load_text(path):
    """Return (.text bytes, {offset: (sym_name, reloc_type)})."""
    e = ELFFile(open(path, "rb"))
    text = b""
    for s in e.iter_sections():
        if s.name == ".text":
            text = s.data()
    symtab = e.get_section_by_name(".symtab")
    rel = {}
    for s in e.iter_sections():
        if s.name in (".rel.text", ".rela.text"):
            for r in s.iter_relocations():
                nm = symtab.get_symbol(r["r_info_sym"]).name
                rel[r["r_offset"]] = (nm, r["r_info_type"])
    return bytearray(text), rel


def compare(mine_path, orig_path):
    mine, mrel = load_text(mine_path)
    orig, orel = load_text(orig_path)
    if len(mine) != len(orig):
        return False, f"size {len(mine)} vs {len(orig)}"
    m = bytearray(mine); o = bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off + k < len(m): m[off + k] = 0; o[off + k] = 0
    if m != o:
        d = next(i for i in range(len(m)) if m[i] != o[i])
        return False, f"byte diff at 0x{d:x}"
    if set(mrel) != set(orel):
        return False, f"reloc offsets differ"
    if any(mrel[k][0] != orel[k][0] for k in mrel):
        return False, "reloc symbols differ"
    return True, "match"


def main():
    prefix = sys.argv[1] if len(sys.argv) > 1 else ""
    ok = fail = missing = 0
    fails = []
    for compiled in sorted((ROOT / "build" / "src").rglob("*.o")):
        rel_path = compiled.relative_to(ROOT / "build")
        if prefix and prefix not in str(rel_path):
            continue
        delinked = ROOT / "build" / "delinks" / rel_path
        if not delinked.exists():
            missing += 1
            continue
        matched, msg = compare(compiled, delinked)
        if matched:
            ok += 1
        else:
            fail += 1
            fails.append((str(rel_path).replace("\\", "/"), msg))

    print(f"MATCH:  {ok}")
    print(f"DIFF:   {fail}")
    print(f"MISSING delink baseline: {missing}")
    for path, msg in fails[:20]:
        print(f"  DIFF {path}  ({msg})")


if __name__ == "__main__":
    main()
