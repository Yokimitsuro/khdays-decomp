"""Does a pool value used twice get hoisted above the parameter save?
Probes only; some of these are deliberately not the real semantics."""
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
    p = "build/try/ba14_cse.c"
    with open(p, "w") as f:
        f.write(COMMON + src)
    try:
        o = compile_c(p, True)
        b, _ = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex)[:60]))
        return
    txt = [i.mnemonic + " " + i.op_str for i in md.disasm(b, 0)]
    print("%-26s %3dB  %s" % (tag, len(b), " | ".join(txt[:5])))


TAIL = """    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
"""

# baseline
probe("a_base", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      + TAIL)

# the global address used a second time late
probe("b_globaltwice", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n"
      "    slot[3] = func_ov022_02088254(index);\n"
      "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
      "    if (data_ov002_0207fa00 != 0 && (data_0204c240 & 4) == 0 && index == 0) {\n"
      "        func_02035c60();\n    }\n}\n")

# the 0x8bd0 constant used a second time
probe("c_offtwice", "void f(int index) {\n"
      "    char *root = data_ov002_0207fa00;\n"
      "    int *slot = (int *)(*(char **)(root + 0x8bd0) + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n"
      "    slot[3] = func_ov022_02088254(index);\n"
      "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
      "    if (*(char **)(root + 0x8bd0) != 0 && (data_0204c240 & 4) == 0 && index == 0) {\n"
      "        func_02035c60();\n    }\n}\n")

# the table pointer bound and reused after the calls
probe("d_tblreuse", "void f(int index) {\n"
      "    char *tbl = *(char **)(data_ov002_0207fa00 + 0x8bd0);\n"
      "    int *slot = (int *)(tbl + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n"
      "    slot[3] = func_ov022_02088254(index);\n"
      "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
      "    if (tbl != 0 && (data_0204c240 & 4) == 0 && index == 0) {\n"
      "        func_02035c60();\n    }\n}\n")

# the index used as a load base somewhere, like func_ov000_02055b0c
probe("e_idxbase", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      "    SlotHeader *src = func_ov022_020881f8();\n\n"
      "    *(SlotHeader *)slot = *src;\n"
      "    slot[3] = func_ov022_02088254(index);\n"
      "    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);\n\n"
      "    if ((data_0204c240 & 4) == 0 && index == 0) {\n"
      "        func_02035c60();\n    }\n}\n")
