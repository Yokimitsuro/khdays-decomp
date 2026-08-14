"""Second matrix: sweep the BODY shape, which fixes the lifetimes that drive the
entry-block allocation."""
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

SLOTDECL = [
    ("int *", "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0)"
              " + index * 0x44);\n"),
    ("char *", "    char *slot = *(char **)(data_ov002_0207fa00 + 0x8bd0)"
               " + index * 0x44;\n"),
    ("SlotHeader *", "    SlotHeader *slot = (SlotHeader *)"
                     "(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"),
]

# copy spelling, keyed by slot type
COPY = {
    "int *": ["    *(SlotHeader *)slot = *src;\n",
              "    *(SlotHeader *)slot = src[0];\n"],
    "char *": ["    *(SlotHeader *)slot = *src;\n",
               "    *(SlotHeader *)slot = src[0];\n"],
    "SlotHeader *": ["    *slot = *src;\n", "    slot[0] = src[0];\n"],
}

VALSTORE = {
    "int *": ["    slot[3] = func_ov022_02088254(index);\n",
              "    *(int *)((char *)slot + 0xc) = func_ov022_02088254(index);\n"],
    "char *": ["    *(int *)(slot + 0xc) = func_ov022_02088254(index);\n"],
    "SlotHeader *": ["    *(int *)((char *)slot + 0xc) = func_ov022_02088254(index);\n"],
}

OUTARG = {
    "int *": ["slot + 4", "(char *)slot + 0x10", "(void *)((char *)slot + 0x10)"],
    "char *": ["slot + 0x10", "(void *)(slot + 0x10)"],
    "SlotHeader *": ["(char *)slot + 0x10", "(void *)((char *)slot + 0x10)"],
}

FILLCALL = [
    "    func_ov002_020726a0(func_ov022_02088474(index), 0, %s);\n",
    "    {\n        int id = func_ov022_02088474(index);\n"
    "        func_ov002_020726a0(id, 0, %s);\n    }\n",
]

GUARD = [
    "    if ((data_0204c240 & 4) == 0 && index == 0) {\n"
    "        func_02035c60();\n    }\n",
    "    if ((data_0204c240 & 4) == 0) {\n        if (index == 0) {\n"
    "            func_02035c60();\n        }\n    }\n",
    "    if (index == 0 && (data_0204c240 & 4) == 0) {\n"
    "        func_02035c60();\n    }\n",
]

SRCPOS = ["after", "before"]


def prosig(txt):
    save = pool = None
    for k, t in enumerate(txt[:8]):
        if save is None and re.match(r"^adds r\d, r0, #0$", t):
            save = k
        m = re.match(r"^ldr (r\d), \[pc", t)
        if pool is None and m:
            pool = (k, m.group(1))
    return save, pool


def main():
    tmp = "build/try/ba14_bodymatrix.c"
    seen = set()
    sigs = {}
    best = (99, None)
    n = 0
    for stype, sdecl in SLOTDECL:
        for copy in COPY[stype]:
            for valst in VALSTORE[stype]:
                for outarg in OUTARG[stype]:
                    for fill in FILLCALL:
                        for guard in GUARD:
                            for srcpos in SRCPOS:
                                call = "    SlotHeader *src = func_ov022_020881f8();\n"
                                if srcpos == "before":
                                    body = call + sdecl
                                else:
                                    body = sdecl + call
                                src = (HEAD + body + "\n" + copy + valst
                                       + (fill % outarg) + "\n" + guard + "}\n")
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
                                if sig not in sigs or d < sigs[sig]:
                                    sigs[sig] = d
                                if d < best[0]:
                                    best = (d, src)
    print("compiled %d body variants" % n)
    print("ROM prologue signature: save=%s pool=%s" % prosig(OM))
    for sig, d in sorted(sigs.items(), key=lambda x: x[1]):
        print("   save=%-4s pool=%-10s best diff=%d" % (sig[0], sig[1], d))
    print("best overall diff=%d" % best[0])
    if best[1]:
        with open("build/try/ba14_bodybest.c", "w") as f:
            f.write(best[1])


main()
