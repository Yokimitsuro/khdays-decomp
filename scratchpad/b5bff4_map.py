"""Harness on the real function: for each variant report the physical register
each of the three contested values lands in, plus size and byte distance, so a
sweep shows direction rather than only a score.

Target mapping, read off the ROM: session r8, class/scratch r4, tag r7.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}


def measure(src, path="build/try/b5bff4_map.c"):
    open(path, "w").write(src)
    o = compile_c(path, False)
    code, mrel = text_relocs(o)
    ins = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(code), 0)]
    ses = cls = "?"
    for t in ins[:12]:
        m = re.match(r"ldr (r[0-9]+|sb|sl|fp), \[r2\]$", t)
        if m and ses == "?":
            ses = m.group(1)
        m = re.match(r"mov (r[0-9]+|sb|sl|fp), r0$", t)
        if m and cls == "?" and ses != "?":
            cls = m.group(1)
    n = None
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    return len(code), ses, cls, n


def report(tag, src):
    try:
        size, ses, cls, n = measure(src)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    print("%-24s size=%-5d session=%-4s class=%-4s bytes=%s%s"
          % (tag, size, ses, cls, n if n is not None else "-",
             "   MATCH" if n == 0 else ""))


if __name__ == "__main__":
    BASE = open("build/try/%s.c" % SYM).read()
    report("base", BASE)
    print("ROM target: session=r8 class=r4")
