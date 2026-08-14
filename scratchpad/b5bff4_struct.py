"""Last untried input class: the declared shape of the session struct. The
emitted instructions are the same for every shape here, but the IR mwcc builds
for a field access differs between an array member that decays, a named
sub-struct whose address is taken, and raw offset arithmetic. That is an input
to web construction that no previous sweep varied.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
SYM = "func_ov002_0205bff4"
_e = json.load(open("build/func_index.json"))[SYM]
ORIG = bytearray.fromhex(_e["hex"])
OREL = {o: s for o, s in _e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()


def sess(code):
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r2\]$", i.mnemonic + " " + i.op_str)
        if m:
            return m.group(1)
    return "?"


def report(tag, src):
    p = "build/try/b5bff4_st.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        print("%-26s FAIL %s" % (tag, str(ex).split("\n")[0][:50]))
        return
    n = "-"
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-26s size=%-5d bytes=%-4s s=%s%s"
          % (tag, len(code), n, sess(code), "   MATCH" if n == 0 else ""))
    if n == 0:
        open("build/try/%s.c" % SYM, "w").write(src)
        print("PROMOTED " + tag)


report("base", BASE)

# 1. the two list members become named sub-structs whose address is taken
S1 = BASE.replace("""    u8 listItems[0x18];     /* +0x480 */
    u8 listEntries[0xc];    /* +0x498 */""",
                  """    NNSFndList listItems;   /* +0x480 */
    NNSFndList listEntries; /* +0x498 */""")
S1 = S1.replace("typedef struct {\n    u8 bKind;",
                "typedef struct {\n    u8 b[0x18];\n} NNSFndList;\n\n"
                "typedef struct {\n    u8 bKind;")
S1 = S1.replace("s->listItems", "&s->listItems").replace(
    "s->listEntries", "&s->listEntries")
report("named_sublists", S1)

# 2. the padding expressed as one blob rather than several named runs
S2 = BASE.replace("""    u8 pad0005[2];
    u8 bDefaultKind;        /* +7 */
    u8 pad0008[4];
    int nField000c;         /* +0xc */
    u8 pad0010[4];
    u16 wField0014;         /* +0x14 */
    u8 pad0016[0x1c];
    u8 aBitIndex[0x44e];    /* +0x32 */""",
                  """    u8 pad0005[2];
    u8 bDefaultKind;        /* +7 */
    int pad0008;
    int nField000c;         /* +0xc */
    int pad0010;
    u16 wField0014;         /* +0x14 */
    u16 pad0016[0xe];
    u8 aBitIndex[0x44e];    /* +0x32 */""")
report("padding_reshaped", S2)

# 3. the cached entry typed as u16* so case 5 stops casting
S3 = BASE.replace("    void *pCachedEntry;     /* +0x4a4 */",
                  "    u16 *pCachedEntry;      /* +0x4a4 */")
S3 = S3.replace("u16 nKey = *(u16 *)s->pCachedEntry;", "u16 nKey = *s->pCachedEntry;")
S3 = S3.replace("*(int *)((u8 *)s->pCachedEntry + 4) != 0",
                "*(int *)(s->pCachedEntry + 2) != 0")
report("cached_typed", S3)

# 4. the session reached through a typedef'd pointer type
S4 = BASE.replace("extern Ov002PanelSession *data_ov002_0207f620;",
                  "typedef Ov002PanelSession *Ov002PanelSessionPtr;\n"
                  "extern Ov002PanelSessionPtr data_ov002_0207f620;")
S4 = S4.replace("    Ov002PanelSession *s = data_ov002_0207f620;",
                "    Ov002PanelSessionPtr s = data_ov002_0207f620;")
report("typedef_ptr", S4)

# 5. the struct declared with a tag rather than as an anonymous typedef
S5 = BASE.replace("typedef struct {\n    u8 bKind;", "struct Ov002PanelSession_ {\n    u8 bKind;")
S5 = S5.replace("} Ov002PanelSession;",
                "};\ntypedef struct Ov002PanelSession_ Ov002PanelSession;")
report("tagged_struct", S5)
