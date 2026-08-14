"""Split declaration from assignment for the header source, and vary which local
is declared first. Small unexplored corner of the shape space."""
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

TAIL = """    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""

DECLS = {
    "src": "    SlotHeader *src;\n",
    "slot": "    int *slot;\n",
    "n": "    int n;\n",
}
ASSIGN = {
    "src": "    src = func_ov022_020881f8();\n",
    "slot": "    slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0)"
            " + index * 0x44);\n",
}


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


best = (99, None)
sigs = {}
n = 0
tmp = "build/try/ba14_srcsplit.c"
for dorder in itertools.permutations(["src", "slot"]):
    for aorder in itertools.permutations(["src", "slot"]):
        for extra in (0, 1):
            decls = "".join(DECLS[k] for k in dorder)
            if extra:
                decls = DECLS["n"] + decls
            body = decls + "\n" + "".join(ASSIGN[k] for k in aorder) + "\n"
            src = HEAD + body + TAIL
            with open(tmp, "w") as f:
                f.write(src)
            try:
                o = compile_c(tmp, True)
                mine, _ = text_relocs(o)
            except Exception:
                continue
            n += 1
            if len(mine) != len(orig):
                print("  %-28s SIZE %d" % (str((dorder, aorder, extra)), len(mine)))
                continue
            mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
            d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
            sig = prosig(mm)
            sigs.setdefault(sig, d)
            print("  decl=%-16s assign=%-16s extra=%d diff=%-3d sig=%s"
                  % (str(dorder), str(aorder), extra, d, sig))
            if d < best[0]:
                best = (d, src)
print("\ncompiled %d, ROM sig=%s, best diff=%d" % (n, prosig(OM), best[0]))
