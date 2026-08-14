"""Split the parameter's early arithmetic use from its late call-argument uses,
so mwcc may place the callee-saved copy later than entry."""
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

BASE = """typedef struct {
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


def run(tag, body, n):
    tail = ("    SlotHeader *src = func_ov022_020881f8();\n\n"
            "    *(SlotHeader *)slot = *src;\n"
            "    slot[3] = func_ov022_02088254(%s);\n"
            "    func_ov002_020726a0(func_ov022_02088474(%s), 0, slot + 4);\n\n"
            "    if ((data_0204c240 & 4) == 0 && %s == 0) {\n"
            "        func_02035c60();\n    }\n}\n") % (n, n, n)
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(BASE + body + tail)
    try:
        o = compile_c(p, True)
        mine, _ = text_relocs(o)
    except Exception as ex:
        print("%-24s FAIL %s" % (tag, str(ex)[:60]))
        return
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
    d = "-"
    if len(mine) == len(orig):
        d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
    print("%-24s %3dB diff=%-4s %s" % (tag, len(mine), d, " | ".join(mm[1:6])))


print("%-24s  92B diff=0    %s" % ("ROM", " | ".join(OM[1:6])))

run("w1_copyafter",
    "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
    "    int n = index;\n", "n")

run("w2_copymid",
    "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int n = index;\n"
    "    int *slot = (int *)(tbl + index * 0x44);\n", "n")

run("w3_copyfirstuse",
    "    int *slot;\n    int n;\n\n"
    "    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
    "    n = index;\n", "n")

run("w4_twoslots",
    "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int off = index * 0x44;\n"
    "    int n = index;\n"
    "    int *slot = (int *)(tbl + off);\n", "n")

run("w5_declafter",
    "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n",
    "index")
