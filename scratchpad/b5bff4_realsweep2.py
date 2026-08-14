"""Take this turn's levers back to the real function. The knobs swept here were
never swept on the real source: how the eighth argument's zero is spelled, whether
the slot is a variable or an expression at the call, and whether the flag is
reset per half or declared per half. All are size-neutral candidates.
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


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def score(src):
    p = "build/try/b5bff4_rs2.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, str(ex).split("\n")[0][:50]
    if len(code) != len(ORIG):
        return len(code), None, None
    a = bytearray(ORIG)
    b = bytearray(code)
    for off in set(OREL) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    return len(code), sum(1 for i in range(len(a)) if a[i] != b[i]), sess(code)


# knob A: the slot computed into a variable, or inlined as a conditional at the
# call site
SLOT_VAR = """        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(*pEntry);
        }
"""


def k_slot(src, v):
    if v == 0:
        return src
    out = src.replace(SLOT_VAR, "")
    out = out.replace("func_ov002_0205b0dc(s->listItems, nSlot,",
                      "func_ov002_0205b0dc(s->listItems,\n"
                      "                    pEntry == 0 ? -1 : "
                      "func_ov002_0205a540(*pEntry),")
    out = out.replace("func_ov002_0205b0dc(s->listEntries, nSlot,",
                      "func_ov002_0205b0dc(s->listEntries,\n"
                      "                    pEntry == 0 ? -1 : "
                      "func_ov002_0205a540(*pEntry),")
    return out


# knob B: the flag declared once, or once per half inside its own block
def k_flag(src, v):
    if v == 0:
        return src
    return src.replace("        u16 *pEntry;\n        int bFlag;\n        int nSlot;\n",
                       "        u16 *pEntry;\n        int nSlot;\n        int bFlag;\n")


# knob C: the trailing zero arguments spelled as a shared local
def k_zero(src, v):
    if v == 0:
        return src
    out = src.replace("        int nOld = nFrom + nColumn * 6;\n"
                      "        u16 *pEntry;\n        int nSlot;\n",
                      "        int nOld = nFrom + nColumn * 6;\n"
                      "        u16 *pEntry;\n        int nSlot;\n")
    return out


# knob D: case 2's two halves in separate blocks
def k_block(src, v):
    if v == 0:
        return src
    head, tail = src.split("    case 2: {", 1)
    body, rest = tail.split("    case 3: {", 1)
    body = body.replace("        pEntry = (u16 *)func_02010154(s->listItems, (u16)nOld);",
                        "        {\n        pEntry = (u16 *)func_02010154(s->listItems, (u16)nOld);")
    body = body.replace("        func_ov002_0205b0dc(s->listItems, nSlot, nFrom, nOld, 1, bFlag, 0, 0);",
                        "        func_ov002_0205b0dc(s->listItems, nSlot, nFrom, nOld, 1, bFlag, 0, 0);\n        }")
    return head + "    case 2: {" + body + "    case 3: {" + rest


# knob E: nTag reset before the second half of case 3 as well
def k_tag2(src, v):
    if v == 0:
        return src
    return src.replace("""        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nClass);
        if (pEntry != 0) {""",
                       """        pEntry = (u16 *)func_02010154(s->listEntries, (u16)nClass);
        if (pEntry != 0) {""")


KNOBS = [("slot", k_slot, 2), ("flag", k_flag, 2), ("zero", k_zero, 2),
         ("block", k_block, 1), ("tag2", k_tag2, 2)]

best = (10 ** 9, None)
seen = {}
for combo in itertools.product(*[range(k[2]) for k in KNOBS]):
    src = BASE
    for (name, fn, _), v in zip(KNOBS, combo):
        src = fn(src, v)
    size, d, sr = score(src)
    tag = " ".join("%s=%d" % (k[0], v) for k, v in zip(KNOBS, combo))
    if size is None:
        print("%-40s FAIL %s" % (tag, sr))
        continue
    if d is None:
        seen[tag] = "size %d" % size
        continue
    seen[tag] = d
    if d < best[0]:
        best = (d, tag)
        print("new best %d bytes  s=%s  %s" % (d, sr, tag))
    if d == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("MATCH " + tag)
        break

print()
vals = sorted(set(v for v in seen.values() if isinstance(v, int)))
print("distinct byte counts:", vals)
print("best: %d bytes  %s" % (best[0], best[1]))
