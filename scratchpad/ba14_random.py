"""Randomised search over a rich grammar of source shapes, looking for any build
whose prologue signature is the ROM's. Deterministic seed sequence, no Date/random
dependence on wall clock."""
import sys
import os
import re
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_02069b14"
idx = json.load(open("build/func_index.json"))
e = idx[NAME]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(orig), 0)]

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


# each value can be inline (folded into its user) or bound to a named local
ROOT_F = ["data_ov002_0207fa00", "(char *)data_ov002_0207fa00"]
TBL_F = ["*(char **)(%s + 0x8bd0)", "*(char **)((char *)%s + 0x8bd0)",
         "(char *)*(int *)(%s + 0x8bd0)"]
OFF_F = ["%s * 0x44", "0x44 * %s", "%s * 68"]
SLOT_F = ["(int *)(%s + %s)", "(int *)(%s + (%s))", "(int *)((char *)%s + %s)"]

LCG = 12345


def rnd(n):
    global LCG
    LCG = (LCG * 1103515245 + 12345) & 0x7FFFFFFF
    return LCG % n


def gen():
    bind_root = rnd(2)
    bind_tbl = rnd(2)
    bind_off = rnd(2)
    callpos = rnd(3)          # 0 after slot, 1 before slot, 2 between binds
    rootf = ROOT_F[rnd(len(ROOT_F))]
    tblf = TBL_F[rnd(len(TBL_F))]
    offf = OFF_F[rnd(len(OFF_F))]
    slotf = SLOT_F[rnd(len(SLOT_F))]
    outer = rnd(2)            # declare locals at top or inline with initialisers

    decls = []
    stmts = []
    rootx = rootf
    if bind_root:
        if outer:
            decls.append("    char *root;\n")
            stmts.append("    root = %s;\n" % rootx)
        else:
            stmts.append("    char *root = %s;\n" % rootx)
        rootx = "root"
    tblx = tblf % rootx
    if bind_tbl:
        if outer:
            decls.append("    char *tbl;\n")
            stmts.append("    tbl = %s;\n" % tblx)
        else:
            stmts.append("    char *tbl = %s;\n" % tblx)
        tblx = "tbl"
    offx = offf % "index"
    if bind_off:
        if outer:
            decls.append("    int off;\n")
            stmts.append("    int off = %s;\n" % offx if not outer
                         else "    off = %s;\n" % offx)
        else:
            stmts.append("    int off = %s;\n" % offx)
        offx = "off"
    slotx = slotf % (tblx, offx)
    if outer:
        decls.append("    int *slot;\n")
        slotstmt = "    slot = %s;\n" % slotx
    else:
        slotstmt = "    int *slot = %s;\n" % slotx
    call = "    SlotHeader *src = func_ov022_020881f8();\n"
    if outer:
        decls.append("    SlotHeader *src;\n")
        call = "    src = func_ov022_020881f8();\n"

    if callpos == 0:
        seq = stmts + [slotstmt, call]
    elif callpos == 1:
        seq = [call] + stmts + [slotstmt]
    else:
        half = len(stmts) // 2
        seq = stmts[:half] + [call] + stmts[half:] + [slotstmt]

    tail = ("\n    *(SlotHeader *)slot = *src;\n"
            "    slot[3] = func_ov022_02088254(index);\n"
            "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
            "    if ((data_0204c240 & 4) == 0 && index == 0) {\n"
            "        func_02035c60();\n    }\n}\n")
    return TY + "".join(decls) + ("\n" if decls else "") + "".join(seq) + tail


def main():
    tmp = "build/try/ba14_random.c"
    seen = set()
    sigs = {}
    best = (99, None)
    n = ok = 0
    for _ in range(4000):
        src = gen()
        if src in seen:
            continue
        seen.add(src)
        with open(tmp, "w") as f:
            f.write(src)
        try:
            o = compile_c(tmp, True)
            mine, mrel = text_relocs(o)
        except Exception:
            continue
        n += 1
        if len(mine) != len(orig):
            continue
        ok += 1
        a = bytearray(orig)
        b = bytearray(mine)
        for off in set(orel) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        nd = sum(1 for i in range(len(a)) if a[i] != b[i])
        mm = [i.mnemonic + " " + i.op_str for i in md.disasm(bytes(mine), 0)]
        sig = prosig(mm)
        if sig not in sigs or nd < sigs[sig]:
            sigs[sig] = nd
        if nd < best[0]:
            best = (nd, src)
        if nd == 0:
            with open("build/try/ba14_random_WIN.c", "w") as f:
                f.write(src)
            print("MATCH FOUND")
            print(src)
            return
    print("compiled %d unique, %d at the right size" % (n, ok))
    print("ROM signature: %s" % (prosig(OM),))
    for sig, nd in sorted(sigs.items(), key=lambda x: x[1]):
        print("   sig=%-18s best bytes=%d" % (str(sig), nd))
    print("best bytes=%d" % best[0])


main()
