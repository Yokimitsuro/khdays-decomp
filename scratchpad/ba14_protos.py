"""Sweep the three callee prototypes. Their declared widths and signedness feed
the entry-block value numbering even when the emitted body is identical."""
import sys
import os
import re
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
e = idx[NAME]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


# return type of the header-source callee, and how the copy is spelled
HDR = [
    ("SlotHeader *", "*(SlotHeader *)slot = *src;"),
    ("void *", "*(SlotHeader *)slot = *(SlotHeader *)src;"),
    ("char *", "*(SlotHeader *)slot = *(SlotHeader *)src;"),
    ("int *", "*(SlotHeader *)slot = *(SlotHeader *)src;"),
]
# value callee: return type and parameter type
VAL_R = ["int", "unsigned int", "short", "unsigned short", "char",
         "unsigned char", "long"]
# seat-id callee: return type and parameter type
ID_R = ["int", "unsigned int", "short", "unsigned short", "long"]
ARG_T = ["int", "unsigned int", "short", "long"]

TY = """typedef struct {
    int a;
    int b;
    int c;
} SlotHeader;

extern char *data_ov002_0207fa00;
extern unsigned char data_0204c240;
"""


def main():
    tmp = "build/try/ba14_protos.c"
    sigs = {}
    best = (99, None, None)
    n = 0
    for hdrt, copy in HDR:
        for valr in VAL_R:
            for idr in ID_R:
                for argt in ARG_T:
                    src = (TY
                           + "extern %sfunc_ov022_020881f8(void);\n" % hdrt
                           + "extern %s func_ov022_02088254(%s index);\n" % (valr, argt)
                           + "extern %s func_ov022_02088474(%s index);\n" % (idr, argt)
                           + "extern void func_ov002_020726a0(int id, int *unused, void *out);\n"
                           + "extern void func_02035c60(void);\n\n"
                           + "void func_ov002_02069b14(int index) {\n"
                           + "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0)"
                             " + index * 0x44);\n"
                           + "    %ssrc = func_ov022_020881f8();\n\n" % hdrt
                           + "    " + copy + "\n"
                           + "    slot[3] = func_ov022_02088254(index);\n"
                           + "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
                           + "    if ((data_0204c240 & 4) == 0 && index == 0) {\n"
                             "        func_02035c60();\n    }\n}\n")
                    with open(tmp, "w") as f:
                        f.write(src)
                    try:
                        o = compile_c(tmp, True)
                        mine, mrel = text_relocs(o)
                    except Exception:
                        continue
                    n += 1
                    if len(mine) != len(orig):
                        continue
                    a = bytearray(orig)
                    b = bytearray(mine)
                    for off in set(orel) | set(mrel):
                        for k in range(4):
                            if off + k < len(a):
                                a[off + k] = 0
                                b[off + k] = 0
                    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
                    mm = [i.mnemonic + " " + i.op_str
                          for i in md.disasm(bytes(mine), 0)]
                    sig = prosig(mm)
                    key = (hdrt, valr, idr, argt)
                    if sig not in sigs or nd < sigs[sig][0]:
                        sigs[sig] = (nd, key)
                    if nd < best[0]:
                        best = (nd, src, key)
                    if nd == 0:
                        with open("build/try/ba14_protos_WIN.c", "w") as f:
                            f.write(src)
                        print("MATCH with %s" % (key,))
                        print(src)
                        return
    print("compiled %d prototype combinations" % n)
    print("ROM signature: %s" % (prosig(OM),))
    for sig, (nd, key) in sorted(sigs.items(), key=lambda x: x[1][0]):
        print("   sig=%-18s best bytes=%-3d via %s" % (str(sig), nd, key))
    print("best bytes=%d via %s" % (best[0], best[2]))


main()
