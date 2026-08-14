"""Never name the slot address: write it inline at each use and let common
subexpression elimination rebuild it. Different IR shape, not another spelling."""
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

HEAD = """typedef struct {
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
        f.write(HEAD + body)
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
    print("%-24s %3dB diff=%-4s sig=%s  %s"
          % (tag, len(mine), d, prosig(mm), " | ".join(mm[1:5])))


print("%-24s  92B diff=0    sig=%s  %s"
      % ("ROM", prosig(OM), " | ".join(OM[1:5])))

S = "(char *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44)"

# n1: slot never named, inline at all three uses
run("n1_inline_all", """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)%s = *src;
    *(int *)(%s + 0xc) = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, %s + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""" % (S, S, S))

# n2: table named, slot inline
run("n2_tbl_named", """    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)(tbl + index * 0x44) = *src;
    *(int *)(tbl + index * 0x44 + 0xc) = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, tbl + index * 0x44 + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# n3: byte offset named, table and slot inline
run("n3_off_named", """    int off = index * 0x44;
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + off) = *src;
    *(int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + off + 0xc) =
        func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0,
                        *(char **)(data_ov002_0207fa00 + 0x8bd0) + off + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# n4: slot named but reassigned as it advances, matching the in-place add
run("n4_advance", """    char *slot = *(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44;
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    *(int *)(slot + 0xc) = func_ov022_02088254(index);
    slot += 0x10;
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")

# n5: slot named, advanced, and the header source call first
run("n5_advance_callfirst", """    SlotHeader *src = func_ov022_020881f8();
    char *slot = *(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44;

    *(SlotHeader *)slot = *src;
    *(int *)(slot + 0xc) = func_ov022_02088254(index);
    slot += 0x10;
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""")
