import sys
import os
import json

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

idx = json.load(open("build/func_index.json"))
e = idx["func_ov002_02051fc8"]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}

HEAD = """typedef struct {
    char pad0000[0x18];
    void *apBlocks[1];
    char pad001c[0x30];
    char *pTables;
    int nTableCount;
} Ov002TableOwner;

extern void func_0202a440(void *table);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov002_02051fc8(Ov002TableOwner *self) {
"""


def score(tag, body):
    s = HEAD + body + "}\n"
    p = "build/try/b1fc8_%s.c" % tag
    open(p, "w").write(s)
    try:
        o = compile_c(p, False)
        mine, mrel = text_relocs(o)
    except Exception as ex:
        print("%-22s FAIL %s" % (tag, str(ex).split("\n")[0][:45]))
        return 99
    if len(mine) != len(orig):
        print("%-22s SIZE %d" % (tag, len(mine)))
        return 99
    a = bytearray(orig)
    b = bytearray(mine)
    for off in set(orel) | set(mrel):
        for k in range(4):
            if off + k < len(a):
                a[off + k] = 0
                b[off + k] = 0
    nd = sum(1 for i in range(len(a)) if a[i] != b[i])
    print("%-22s bytes=%d%s" % (tag, nd, "   <<< MATCH" if nd == 0 else ""))
    if nd == 0:
        open("build/try/func_ov002_02051fc8.c", "w").write(s)
        print("PROMOTED")
    return nd


BODY = """        func_0202a440(self->pTables + off);
        NNSi_FndFreeFromDefaultHeap(self->apBlocks[i]);
"""

score("a_for_comma",
      "    int i;\n    int off;\n\n"
      "    if (self->nTableCount == 0) {\n        return;\n    }\n"
      "    for (i = 0, off = 0; i < self->nTableCount; i++, off += 0x24) {\n"
      + BODY + "    }\n"
      "    NNSi_FndFreeFromDefaultHeap(self->pTables);\n")

score("b_while",
      "    int i = 0;\n    int off = 0;\n\n"
      "    if (self->nTableCount == 0) {\n        return;\n    }\n"
      "    while (i < self->nTableCount) {\n" + BODY
      + "        i++;\n        off += 0x24;\n    }\n"
      "    NNSi_FndFreeFromDefaultHeap(self->pTables);\n")

score("c_i_first",
      "    int i = 0;\n    int off;\n\n"
      "    if (self->nTableCount == 0) {\n        return;\n    }\n"
      "    off = 0;\n"
      "    for (; i < self->nTableCount; i++) {\n" + BODY
      + "        off += 0x24;\n    }\n"
      "    NNSi_FndFreeFromDefaultHeap(self->pTables);\n")

score("d_offdecl_after",
      "    int i;\n\n"
      "    if (self->nTableCount == 0) {\n        return;\n    }\n"
      "    {\n        int off = 0;\n\n"
      "        for (i = 0; i < self->nTableCount; i++) {\n" + BODY
      + "            off += 0x24;\n        }\n    }\n"
      "    NNSi_FndFreeFromDefaultHeap(self->pTables);\n")

score("e_nested_guard",
      "    int i;\n    int off;\n\n"
      "    if (self->nTableCount == 0) {\n        return;\n    }\n"
      "    i = 0;\n"
      "    if (0 < self->nTableCount) {\n"
      "        off = 0;\n"
      "        do {\n" + BODY
      + "            i++;\n            off += 0x24;\n"
        "        } while (i < self->nTableCount);\n    }\n"
      "    NNSi_FndFreeFromDefaultHeap(self->pTables);\n")
