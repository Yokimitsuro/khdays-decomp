"""Array-indexing forms and entry-block pressure variants."""
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

typedef struct {
    char pad0000[0x44];
} SlotRec;

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


def run(tag, body):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(BASE + "void func_ov002_02069b14(int index) {\n" + body + TAIL)
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

run("r1_arrayidx",
    "    SlotRec *tbl = *(SlotRec **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int *slot = (int *)&tbl[index];\n")

run("r2_arrayidx_inline",
    "    int *slot = (int *)&(*(SlotRec **)(data_ov002_0207fa00 + 0x8bd0))[index];\n")

run("r3_arrayidx_ptradd",
    "    SlotRec *tbl = *(SlotRec **)(data_ov002_0207fa00 + 0x8bd0);\n"
    "    int *slot = (int *)(tbl + index);\n")

run("r4_sizeof",
    "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0)\n"
    "                        + index * sizeof(SlotRec));\n")

run("r5_arrayidx_hdr",
    "    SlotHeader *slot = (SlotHeader *)&(*(SlotRec **)(data_ov002_0207fa00 + 0x8bd0))[index];\n")
