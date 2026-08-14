"""Never-tested axis: the variable NAMES. Declaration order has been swept
exhaustively, but if mwcc numbers webs through any name-keyed structure then
renaming alone would move the allocation while leaving the code identical.
Cheap to falsify and decisive either way.
"""
import sys
import os
import json
import re
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()


def score(src):
    p = "build/try/b5bff4_nm.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:45]
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
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr


def rename(src, old, new):
    return re.sub(r"\b%s\b" % re.escape(old), new, src)


print("%-34s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
size, n, sr = score(BASE)
print("%-34s %-6d %-6s %s" % ("base", size, n, sr))

CASES = [
    ("s -> a", [("s", "a")]),
    ("s -> zzzz", [("s", "zzzz")]),
    ("s -> pSession", [("s", "pSession")]),
    ("nClass -> a", [("nClass", "a")]),
    ("nClass -> zzz", [("nClass", "zzz")]),
    ("nTag -> aaa", [("nTag", "aaa")]),
    ("swap s and nClass names", [("s", "tmpswap"), ("nClass", "s"), ("tmpswap", "nClass")]),
    ("all short", [("nFrom", "a"), ("nTo", "b"), ("s", "c"),
                   ("nClass", "d"), ("nTag", "e"), ("nColumn", "f")]),
    ("all long", [("nFrom", "theSourceSlotIndex"), ("nTo", "theTargetSlotIndex"),
                  ("s", "thePanelSessionPointer"), ("nClass", "theLayoutClass"),
                  ("nTag", "theEntryTagValue"), ("nColumn", "theColumnCount")]),
    ("reverse alphabetical", [("nFrom", "zzz1"), ("nTo", "yyy2"), ("s", "xxx3"),
                              ("nClass", "www4"), ("nTag", "vvv5")]),
    ("alphabetical", [("nFrom", "aaa1"), ("nTo", "bbb2"), ("s", "ccc3"),
                      ("nClass", "ddd4"), ("nTag", "eee5")]),
]
for tag, subs in CASES:
    src = BASE
    for old, new in subs:
        src = rename(src, old, new)
    size, n, sr = score(src)
    if size is None:
        print("%-34s FAIL %s" % (tag, sr))
        continue
    mark = "   MATCH" if n == 0 else ("   MOVED" if sr not in ("r4", "?") else "")
    print("%-34s %-6d %-6s %s%s" % (tag, size, n, sr, mark))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)
