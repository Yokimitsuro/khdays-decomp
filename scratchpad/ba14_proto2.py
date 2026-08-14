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

TAIL = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(%s);
    func_ov002_020726a0(func_ov022_02088474(%s), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && %s == 0) {
        func_02035c60();
    }
}
"""


def run(tag, body, idxname="index"):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(COMMON + body + (TAIL % (idxname, idxname, idxname)))
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

run("y1_root_then_n",
    "    char *root = data_ov002_0207fa00;\n"
    "    int n = index;\n"
    "    int *slot = (int *)(*(char **)(root + 0x8bd0) + n * 0x44);\n", "n")

run("y2_tbl_then_n",
    "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int n = index;\n"
    "    int *slot = (int *)(tbl + n * 0x44);\n", "n")

run("y3_decls_then_stmts",
    "    char *tbl;\n"
    "    int *slot;\n\n"
    "    tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    slot = (int *)(tbl + index * 0x44);\n")

run("y4_off_then_slot",
    "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int nOff = index * 0x44;\n"
    "    int *slot = (int *)(tbl + nOff);\n")

run("y5_n_last_use",
    "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int *slot = (int *)(tbl + index * 0x44);\n")

run("y6_root_tbl_n",
    "    char *root = data_ov002_0207fa00;\n"
    "    char *tbl = *(char **)(root + 0x8bd0);\n"
    "    int n = index;\n"
    "    int *slot = (int *)(tbl + n * 0x44);\n", "n")
