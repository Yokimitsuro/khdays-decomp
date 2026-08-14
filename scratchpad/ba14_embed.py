"""Move the parameter save's IR definition point by embedding the assignment
inside the first expression."""
import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
orig = bytes.fromhex(idx[NAME]["hex"])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(orig, 0)]

COMMON = """typedef struct {
    int a;
    int b;
    int c;
} SlotHeader;

extern char *data_ov002_0207fa00;
extern unsigned char data_0204c240;
extern SlotHeader *func_ov022_020881f8(void);
extern int func_ov022_02088254(int index);
extern int func_ov022_02088474(int index);
extern void func_ov002_020726a0(int id, int *unused, void *out);
extern void func_02035c60(void);

void func_ov002_02069b14(int index) {
"""


def run(tag, body, n="index"):
    tail = ("    SlotHeader *src = func_ov022_020881f8();\n\n"
            "    *(SlotHeader *)slot = *src;\n"
            "    slot[3] = func_ov022_02088254(%s);\n"
            "    func_ov002_020726a0(func_ov022_02088474(%s), 0, slot + 4);\n\n"
            "    if ((data_0204c240 & 4) == 0 && %s == 0) {\n"
            "        func_02035c60();\n    }\n}\n") % (n, n, n)
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(COMMON + body + tail)
    try:
        o = compile_c(p, True)
        mine, _ = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex)[:60]))
        return
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
    if len(mine) != len(orig):
        print("%-24s SIZE %d  %s" % (tag, len(mine), " | ".join(mm[1:5])))
        return
    d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
    pr = sum(1 for k in range(1, 9) if OM[k] != mm[k])
    print("%-24s diff=%-3d pro=%d  %s" % (tag, d, pr, " | ".join(mm[1:6])))


print("%-24s          %s" % ("ROM", " | ".join(OM[1:6])))

run("z1_embed", "    int n;\n    int *slot;\n\n"
    "    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + (n = index) * 0x44);\n", "n")

run("z2_comma", "    int n;\n    int *slot;\n\n"
    "    slot = (n = index, (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + n * 0x44));\n", "n")

run("z3_embed_left", "    int n;\n    int *slot;\n\n"
    "    slot = (int *)((n = index) * 0x44 + *(char **)(data_ov002_0207fa00 + 0x8bd0));\n", "n")

run("z4_tbl_embed", "    int n;\n    char *tbl;\n    int *slot;\n\n"
    "    tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    slot = (int *)(tbl + (n = index) * 0x44);\n", "n")

run("z5_deref_embed", "    int n;\n    int *slot;\n\n"
    "    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0 + 0 * (n = index)) + n * 0x44);\n", "n")

run("z6_nested", "    int n;\n    int *slot;\n\n"
    "    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + ((n = index), n) * 0x44);\n", "n")
