"""Find the smallest structural change that makes mwcc emit the pool load before
the parameter save. Probes only."""
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

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


def probe(tag, src):
    p = "build/try/ba14_probe4.c"
    with open(p, "w") as f:
        f.write(COMMON + src)
    try:
        o = compile_c(p, True)
        b, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex)[:60]))
        return
    txt = [i.mnemonic + " " + i.op_str for i in md.disasm(b, 0)]
    print("%-26s %s" % (tag, " | ".join(txt[:5])))


TAIL = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""

# G: the root pointer itself lives across a call (used again at the end)
probe("g_rootlive", "void f(int index) {\n"
      "    char *root = data_ov002_0207fa00;\n"
      "    int *slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n"
      + TAIL.replace("    if ((data_0204c240 & 4) == 0 && index == 0) {",
                     "    if (root != 0 && (data_0204c240 & 4) == 0 && index == 0) {"))

# H: an early return before anything else
probe("h_earlyret", "void f(int index) {\n"
      "    char *root = data_ov002_0207fa00;\n\n"
      "    if (root == 0) {\n        return;\n    }\n"
      "    {\n    int *slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n"
      + TAIL[:-2] + "    }\n}\n")

# I: no trailing uses of index, so no save is needed at all (control)
probe("i_nosave", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n}\n")

# J: index saved but the slot pointer is what lives across the calls
probe("j_slotlive", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n"
      "    slot[3] = func_ov022_02088254(0);\n"
      "    func_ov002_020726a0(func_ov022_02088474(0), 0, slot + 4);\n}\n")

# K: the global read is the only pool constant (offset folded into a small immediate)
probe("k_onepool", "void f(int index) {\n"
      "    char *root = data_ov002_0207fa00;\n"
      "    int *slot = (int *)(*(char **)root + index * 0x44);\n"
      + TAIL)

# L: two separate globals, the second read late
probe("l_twoglobals", "void f(int index) {\n"
      "    char *root = data_ov002_0207fa00;\n"
      "    int *slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n"
      + TAIL)
