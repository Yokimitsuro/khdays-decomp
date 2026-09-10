#!/usr/bin/env python3
"""Print what a decompiler needs for one function: mode, disassembly, relocations,
   where the .c goes and the exact verify command.

       python tools/getcand.py <func_name>

   Source of truth is build/func_index.json: hex + relocs + mode + module for every
   function, finished or not. The curated build/calls.json / build/candidates.json
   lists this tool used to prefer are no longer produced (they were derived from
   asm/, which the dsd delinks replaced) and carried nothing the index does not.

   Output format is parsed by dispgen.py, dispdec.py and reloc_canon.py: keep the
   `disasm:` line and the `+0x<off> -> <sym>` reloc lines stable.
"""
import json, os, sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "func_index.json")


def src_dir(module, kind):
    """main/itcm functions live flat under src/<kind>/, overlays under src/overlays/ovNNN/<kind>/."""
    if module.startswith("ov"):
        return "src/overlays/%s/%s" % (module, kind)
    return "src/%s" % kind


def main():
    if len(sys.argv) != 2:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    if not os.path.exists(INDEX):
        raise SystemExit("missing build/func_index.json -- produce it with tools/rebuild_index.py --write")
    d = json.load(open(INDEX)).get(name)
    if d is None:
        raise SystemExit("not in build/func_index.json: " + name)
    thumb = d["mode"] == "thumb"
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    disasm = " ; ".join(i.mnemonic + " " + i.op_str for i in md.disasm(bytes.fromhex(d["hex"]), 0))
    if not disasm:
        disasm = "(capstone decoded nothing as %s -- the mode recorded in the index is suspect)" % d["mode"]
    kind = "calls" if d["relocs"] else "auto"
    cpath = "%s/%s.c" % (src_dir(d["module"], kind), name)
    py = os.path.relpath(sys.executable, ROOT).replace(os.sep, "/")
    print("name:", name)
    print("mode:", d["mode"])
    print("module:", d["module"])
    print("size:", d["size"])
    print("kind:", "HAS CALLS (reloc-aware)" if d["relocs"] else "reloc-free")
    print("disasm:", disasm)
    if d["relocs"]:
        print("relocations (offset -> symbol, i.e. your callees/data refs):")
        for off, sym in d["relocs"]:
            print("    +0x%x -> %s" % (off, sym))
        print("callees:", sorted(set(s for _, s in d["relocs"])))
    print("write_to:", cpath)
    print('verify_cmd: %s tools/verify_idx.py "%s" %s%s'
          % (py, cpath, name, " --thumb" if thumb else ""))


if __name__ == "__main__":
    main()
