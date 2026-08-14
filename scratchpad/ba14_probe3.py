"""Isolate what forces the parameter save to instruction 1: probes only, the
semantics are deliberately wrong in some of them."""
import sys
import os
import json

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
    p = "build/try/ba14_probe3.c"
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

# A: the real shape (multiply present)
probe("a_mul", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x44);\n"
      + TAIL)

# B: no multiply, index added raw
probe("b_nomul", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index);\n"
      + TAIL)

# C: index not used in the slot expression at all
probe("c_noidx", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0));\n"
      + TAIL)

# D: multiply by a power of two (shift instead of muls)
probe("d_shift", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + index * 0x40);\n"
      + TAIL)

# E: single pool constant, offset small enough to be an immediate
probe("e_smalloff", "void f(int index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x10) + index * 0x44);\n"
      + TAIL)

# F: parameter typed as a pointer, cast where the arithmetic needs a number
probe("f_ptrparam", "void f(char *index) {\n"
      "    int *slot = (int *)(*(char **)(data_ov002_0207fa00 + 0x8bd0) + (int)index * 0x44);\n"
      + TAIL.replace("(index)", "((int)index)").replace("&& index == 0",
                                                        "&& index == 0"))
