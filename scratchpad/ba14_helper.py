"""Mirror the argument-evaluation effect from the pd probe using an inline helper,
so the global chain is evaluated as argument one while index is still in r0."""
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


def run(tag, head, body):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(COMMON + head + "void func_ov002_02069b14(int index) {\n"
                + body + TAIL)
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

run("q1_helper_tbl_idx",
    "static inline int *SlotAt(char *tbl, int n) {\n"
    "    return (int *)(tbl + n * 0x44);\n}\n\n",
    "    int *slot = SlotAt(*(char **)(data_ov002_0207fa00 + 0x8bd0), index);\n")

run("q2_helper_root_idx",
    "static inline int *SlotAt(char *root, int n) {\n"
    "    return (int *)(*(char **)(root + 0x8bd0) + n * 0x44);\n}\n\n",
    "    int *slot = SlotAt(data_ov002_0207fa00, index);\n")

run("q3_helper_three",
    "static inline int *SlotAt(char *tbl, int n, int stride) {\n"
    "    return (int *)(tbl + n * stride);\n}\n\n",
    "    int *slot = SlotAt(*(char **)(data_ov002_0207fa00 + 0x8bd0), index, 0x44);\n")

run("q4_helper_idx_tbl",
    "static inline int *SlotAt(int n, char *tbl) {\n"
    "    return (int *)(tbl + n * 0x44);\n}\n\n",
    "    int *slot = SlotAt(index, *(char **)(data_ov002_0207fa00 + 0x8bd0));\n")

run("q5_helper_void",
    "static inline int *SlotAt(void *tbl, int n) {\n"
    "    return (int *)((char *)tbl + n * 0x44);\n}\n\n",
    "    int *slot = SlotAt(*(char **)(data_ov002_0207fa00 + 0x8bd0), index);\n")
