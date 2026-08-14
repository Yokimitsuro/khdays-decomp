import sys
import os
import json
import re

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

extern unsigned char data_0204c240;
extern SlotHeader *func_ov022_020881f8(void);
extern int func_ov022_02088254(int index);
extern int func_ov022_02088474(int index);
extern void func_ov002_020726a0(int id, int *unused, void *out);
extern void func_02035c60(void);
"""

TAIL = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""


def run(tag, decl, body):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(COMMON + decl + "\nvoid func_ov002_02069b14(int index) {\n"
                + body + TAIL)
    try:
        o = compile_c(p, True)
        mine, _ = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex)[:60]))
        return
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
    if len(mine) != len(orig):
        print("%-22s SIZE %d  %s" % (tag, len(mine), " | ".join(mm[1:5])))
        return
    d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
    pr = sum(1 for k in range(1, 9) if OM[k] != mm[k])
    print("%-22s diff=%-3d pro=%d  %s" % (tag, d, pr, " | ".join(mm[1:6])))


print("%-22s          %s" % ("ROM", " | ".join(OM[1:6])))

run("x1_typedroot", "extern char *data_ov002_0207fa00;",
    "    char *root = data_ov002_0207fa00;\n"
    "    int *slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n")

run("x2_typedroot_tbl", "extern char *data_ov002_0207fa00;",
    "    char *root = data_ov002_0207fa00;\n"
    "    char *tbl = *(char **)(root + 0x8bd0);\n"
    "    int *slot = (int *)(tbl + index * 0x44);\n")

run("x3_structroot",
    "typedef struct { char pad[0x8bd0]; SlotHeader *pSlots; } Root;\n"
    "extern Root *data_ov002_0207fa00;",
    "    Root *root = data_ov002_0207fa00;\n"
    "    int *slot = (int *)((char *)root->pSlots + index * 0x44);\n")

run("x4_structroot_tbl",
    "typedef struct { char pad[0x8bd0]; SlotHeader *pSlots; } Root;\n"
    "extern Root *data_ov002_0207fa00;",
    "    Root *root = data_ov002_0207fa00;\n"
    "    SlotHeader *tbl = root->pSlots;\n"
    "    int *slot = (int *)((char *)tbl + index * 0x44);\n")

run("x5_ptrptr", "extern char **data_ov002_0207fa00;",
    "    char **root = data_ov002_0207fa00;\n"
    "    int *slot = (int *)(*(char **)((char *)root + 0x8bd0) + index * 0x44);\n")

run("x6_rootonly", "extern char *data_ov002_0207fa00;",
    "    char *root = data_ov002_0207fa00;\n"
    "    int *slot;\n\n"
    "    slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n")
