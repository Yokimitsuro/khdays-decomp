"""The tail decides how long index and slot must live, which is what fixes the
entry-block allocation. Sweep tail spellings."""
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
    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);
"""


def run(tag, tail):
    p = "build/try/ba14_%s.c" % tag
    with open(p, "w") as f:
        f.write(COMMON + tail)
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

BASE = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""
run("t0_base", BASE)

run("t1_idtemp", """    SlotHeader *src = func_ov022_020881f8();
    int id;

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    id = func_ov022_02088474(index);
    func_ov002_020726a0(id, 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

run("t2_charout", """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, (char *)slot + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

run("t3_flagfirst", """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if (index == 0 && (data_0204c240 & 4) == 0) {
        func_02035c60();
    }
}
""")

run("t4_nested_guard", """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0) {
        if (index == 0) {
            func_02035c60();
        }
    }
}
""")

run("t5_srcinline", """    *(SlotHeader *)slot = *func_ov022_020881f8();
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

run("t6_hdrcopy_ptr", """    SlotHeader *src = func_ov022_020881f8();
    SlotHeader *dst = (SlotHeader *)slot;

    *dst = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")
