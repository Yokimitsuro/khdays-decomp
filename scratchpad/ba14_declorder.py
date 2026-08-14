"""Sweep the order of the extern declarations, a dominant lever in this tree."""
import sys
import os
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

DECLS = {
    "glob": "extern char *data_ov002_0207fa00;\n",
    "flag": "extern unsigned char data_0204c240;\n",
    "hdr":  "extern SlotHeader *func_ov022_020881f8(void);\n",
    "val":  "extern int func_ov022_02088254(int index);\n",
    "id":   "extern int func_ov022_02088474(int index);\n",
    "fill": "extern void func_ov002_020726a0(int id, int *unused, void *out);\n",
    "draw": "extern void func_02035c60(void);\n",
}

BODY = """
void func_ov002_02069b14(int index) {
    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""

keys = list(DECLS.keys())
best = (99, None, None)
seen = set()
count = 0
tmp = "build/try/ba14_declorder.c"
# full permutation of 7 declarations is 5040; sample every order of the two data
# symbols against every order of the five functions is enough to see the axis
for dataperm in itertools.permutations(["glob", "flag"]):
    for funcperm in itertools.permutations(["hdr", "val", "id", "fill", "draw"]):
        for interleave in (0, 1):
            if interleave:
                order = list(dataperm) + list(funcperm)
            else:
                order = list(funcperm) + list(dataperm)
            key = tuple(order)
            if key in seen:
                continue
            seen.add(key)
            src = TYPES + "".join(DECLS[n] for n in order) + BODY
            with open(tmp, "w") as f:
                f.write(src)
            try:
                o = compile_c(tmp, True)
                mine, _ = text_relocs(o)
            except Exception:
                continue
            count += 1
            if len(mine) != len(orig):
                continue
            mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
            d = sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k])
            if d < best[0]:
                best = (d, src, key)
print("compiled %d declaration orders" % count)
print("best diff=%d order=%s" % (best[0], best[2]))
if best[1]:
    with open("build/try/ba14_declbest.c", "w") as f:
        f.write(best[1])
