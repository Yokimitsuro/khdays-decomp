"""Make the chain from the pool load to the callee-saved register unbroken, which
is the trait every other member of this opening class has."""
import sys
import os
import re
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
orig = bytes.fromhex(idx[NAME]["hex"])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(orig, 0)]

TY = """typedef struct {
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


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


def run(tag, body):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(TY + body)
    try:
        o = compile_c(p, True)
        mine, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:55]))
        return
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
    d = "-"
    if len(mine) == len(orig):
        d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
    print("%-26s %3dB diff=%-4s sig=%s" % (tag, len(mine), d, prosig(mm)))


print("%-26s  92B diff=0    sig=%s" % ("ROM", prosig(OM)))

TAIL_SLOT = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""

# c1: slot bound directly, no intermediate named at all
run("c1_direct",
    "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
    + TAIL_SLOT)

# c2: the table is the surviving value, slot recomputed at each use
run("c2_tbl_survives", """    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)(tbl + index * 0x44) = *src;
    *(int *)(tbl + index * 0x44 + 0xc) = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, tbl + index * 0x44 + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# c3: the root is the surviving value, table and slot recomputed
run("c3_root_survives", """    char *root = data_ov002_0207fa00;
    SlotHeader *src = func_ov022_020881f8();
    char *slot = *(char **)(root + 0x8bd0) + index * 0x44;

    *(SlotHeader *)slot = *src;
    *(int *)(slot + 0xc) = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 0x10);

    if (root != 0 && (data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# c4: the global read twice, so the pool address itself is a live value
run("c4_globaltwice", """    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0,
                        *(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44 + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# c5: slot declared at function scope so its live range starts at entry
run("c5_slot_outer", """    int *slot;
    SlotHeader *src;

    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);
    src = func_ov022_020881f8();
    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")
