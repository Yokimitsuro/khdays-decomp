"""Full combinatorial sweep of the source shape for func_ov002_02069b14.
Mirrors the matrix that cracked the previous function: enumerate decomposition,
scope, declaration order, types and tail spelling, and report the prologue
signature of every 92-byte build."""
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
orig = bytes.fromhex(idx[NAME]["hex"])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(orig, 0)]

TYPES = """typedef struct {
    int a;
    int b;
    int c;
} SlotHeader;

"""
EXTERNS = """extern unsigned char data_0204c240;
extern SlotHeader *func_ov022_020881f8(void);
extern int func_ov022_02088254(int index);
extern int func_ov022_02088474(int index);
extern void func_ov002_020726a0(int id, int *unused, void *out);
extern void func_02035c60(void);
"""

# how the global is declared and how the root value is spelled
GLOBALS = [
    ("extern char *data_ov002_0207fa00;\n", "data_ov002_0207fa00"),
    ("extern int data_ov002_0207fa00;\n", "(char *)data_ov002_0207fa00"),
    ("extern int *data_ov002_0207fa00;\n", "(char *)data_ov002_0207fa00"),
]

# how the table pointer is obtained from the root
TBL = [
    "*(char **)(%s + 0x8bd0)",
    "*(char **)((char *)%s + 0x8bd0)",
]

# how the slot address is formed
SLOT = [
    "(int *)(%s + index * 0x44)",
    "(int *)(index * 0x44 + %s)",
    "(int *)(%s + 0x44 * index)",
]

# decomposition: which intermediate values get their own statement
#   0 = all inline, 1 = table bound, 2 = root and table bound
DECOMP = [0, 1, 2]

# where the header-source call sits relative to the slot statement
CALLPOS = ["after", "before"]

# tail spellings
TAILS = [
    """    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""",
    """    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, (char *)slot + 0x10);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
""",
]


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        if pool is None and re.match(r"^ldr (r\d), \[pc", t):
            pool = (k, re.match(r"^ldr (r\d), \[pc", t).group(1))
    return save, pool


def main():
    tmp = "build/try/ba14_matrix.c"
    seen = set()
    sigs = {}
    best = (99, None)
    n = 0
    for gi, (gdecl, groot) in enumerate(GLOBALS):
        for tbl in TBL:
            for slotf in SLOT:
                for decomp in DECOMP:
                    for callpos in CALLPOS:
                        for taili, tail in enumerate(TAILS):
                            for gfirst in (0, 1):
                                body = []
                                if decomp == 0:
                                    slotexpr = slotf % (tbl % groot)
                                    stmts = ["    int *slot = %s;\n" % slotexpr]
                                elif decomp == 1:
                                    stmts = ["    char *tbl = %s;\n" % (tbl % groot),
                                             "    int *slot = %s;\n" % (slotf % "tbl")]
                                else:
                                    stmts = ["    char *root = %s;\n" % groot,
                                             "    char *tbl = %s;\n" % (tbl % "root"),
                                             "    int *slot = %s;\n" % (slotf % "tbl")]
                                call = "    SlotHeader *src = func_ov022_020881f8();\n"
                                if callpos == "before":
                                    body = [call] + stmts
                                else:
                                    body = stmts + [call]
                                head = (TYPES
                                        + (gdecl + EXTERNS if gfirst else EXTERNS + gdecl)
                                        + "\nvoid %s(int index) {\n" % NAME)
                                src = head + "".join(body) + "\n" + tail
                                if src in seen:
                                    continue
                                seen.add(src)
                                with open(tmp, "w") as f:
                                    f.write(src)
                                try:
                                    o = compile_c(tmp, True)
                                    mine, _ = text_relocs(o)
                                except Exception:
                                    continue
                                n += 1
                                if len(mine) != len(orig):
                                    continue
                                mm = [i.mnemonic + " " + i.op_str
                                      for i in md.disasm(mine, 0)]
                                d = sum(1 for k in range(min(len(OM), len(mm)))
                                        if OM[k] != mm[k])
                                sig = prosig(mm)
                                sigs.setdefault(sig, d)
                                if d < sigs[sig]:
                                    sigs[sig] = d
                                if d < best[0]:
                                    best = (d, src)
    print("compiled %d variants" % n)
    print("ROM prologue signature: save=%s pool=%s" % prosig(OM))
    print("signatures reached (save index, pool index+reg) -> best diff:")
    for sig, d in sorted(sigs.items(), key=lambda x: x[1]):
        print("   save=%-4s pool=%-10s best diff=%d" % (sig[0], sig[1], d))
    print("best overall diff=%d" % best[0])
    if best[1]:
        with open("build/try/ba14_matrixbest.c", "w") as f:
            f.write(best[1])


main()
