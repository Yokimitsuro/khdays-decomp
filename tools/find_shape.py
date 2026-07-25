"""Ask whether a codegen shape has EVER been produced from real C in this repo.

    python tools/find_shape.py

Before concluding "mwcc cannot emit X", state the positive form of X and search the
matched corpus for it. This script is that search, kept because doing it by hand is
how a false claim got written down: while matching func_ov000_02050ec4 the note said
"mwcc never hoists a load above a store to a stack slot", and the corpus answered with
49 byte-exact functions that do exactly that.

Two rules are baked in, both learned the expensive way:

  * Only real C in auto/ or calls/ counts. An asm_stubs blob reproduces the ROM with
    any compiler, so including one makes the answer meaningless -- and a stub can sit
    in calls/ with a decorative struct header, so the body is checked for `dcd`/`asm`
    rather than trusting the directory.
  * Validate the predicate against bytes you KNOW contain the shape before believing a
    zero. A search that could never have matched returns zero just as convincingly as
    a real absence.

Edit the predicate below for the shape you are chasing. As written it looks for a load
from a non-sp base immediately followed by a store to a stack slot, where the loaded
value is still consumed afterwards.
"""
import sys, os, re, json, glob
sys.path.insert(0, "tools")
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.abspath(".")
IDX = json.load(open("build/func_index.json"))

realc = {}
for pat in ("src/**/calls/*.c", "src/**/auto/*.c"):
    for f in glob.glob(pat, recursive=True):
        n = f.replace("\\", "/")
        if "/asm_stubs/" in n or "/nonmatching/" in n:
            continue
        body = open(f, encoding="utf-8", errors="replace").read()
        if re.search(r"^\s*dcd |^asm ", body, re.M):     # an asm stub is not C
            continue
        realc[os.path.basename(f)[:-2]] = f

thumb_syms = set()
for dirpath, _d, files in os.walk("config"):
    if "symbols.txt" in files:
        for line in open(os.path.join(dirpath, "symbols.txt"), encoding="utf-8",
                         errors="replace"):
            if "kind:function(thumb" in line:
                thumb_syms.add(line.split()[0])

arm = Cs(CS_ARCH_ARM, CS_MODE_ARM)
thm = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

LD = re.compile(r"^(r\d+|ip|lr), \[(r\d+|ip|lr)(, #(0x[0-9a-f]+|\d+))?\]$")
ST = re.compile(r"^(r\d+|ip|lr), \[sp(, #(0x[0-9a-f]+|\d+))?\]$")

hits = []
for name, f in sorted(realc.items()):
    e = IDX.get(name)
    if not e or not e.get("hex"):
        continue
    md = thm if name in thumb_syms else arm
    ins = list(md.disasm(bytes.fromhex(e["hex"]), 0))
    for k in range(len(ins) - 1):
        a, b = ins[k], ins[k + 1]
        if a.mnemonic != "ldr" or b.mnemonic != "str":
            continue
        ma, mb = LD.match(a.op_str), ST.match(b.op_str)
        if not ma or not mb:
            continue
        if ma.group(2) == "sp":            # want a non-sp base for the load
            continue
        dest = ma.group(1)
        if dest == mb.group(1):            # storing what we just loaded is a copy
            continue
        # the loaded value must still be consumed after the store
        used_after = any(dest in ins[j].op_str for j in range(k + 2, min(k + 10, len(ins))))
        if used_after:
            hits.append((name, f, k * 4, a.mnemonic + " " + a.op_str,
                         b.mnemonic + " " + b.op_str))
            break

print("matched real-C functions scanned: %d" % len(realc))
print("functions containing load-before-stack-store with the value used later: %d"
      % len(hits))
for n, f, off, x, y in hits[:25]:
    print("  %-28s +0x%03X  %-26s | %s" % (n, off, x, y))
    print("      %s" % f)
