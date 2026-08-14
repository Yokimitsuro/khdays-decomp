"""Last cheap axis: the session's pointer type. A struct pointer and a byte
pointer with offsets can rank differently in mwcc's allocator.
"""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs

SYM = "func_ov002_0205bff4"
idx = json.load(open("build/func_index.json"))
e = idx[SYM]
orig = bytearray.fromhex(e["hex"])
orel = {o: s for o, s in e["relocs"]}
BASE = open("build/try/%s.c" % SYM).read()

FIELDS = {
    "s->bKind": "*(u8 *)(s + 0)",
    "s->bMode": "*(u8 *)(s + 1)",
    "s->bIndex": "*(u8 *)(s + 2)",
    "s->bListIndex": "*(u8 *)(s + 3)",
    "s->bKey": "*(u8 *)(s + 4)",
    "s->bDefaultKind": "*(u8 *)(s + 7)",
    "s->nField000c": "*(int *)(s + 0xc)",
    "s->wField0014": "*(u16 *)(s + 0x14)",
    "s->aBitIndex[0]": "*(u8 *)(s + 0x32)",
    "s->listItems": "(s + 0x480)",
    "s->listEntries": "(s + 0x498)",
    "s->pCachedEntry": "*(void **)(s + 0x4a4)",
}

s = BASE
s = s.replace("extern Ov002PanelSession *data_ov002_0207f620;",
              "extern char *data_ov002_0207f620;")
s = s.replace("    Ov002PanelSession *s = data_ov002_0207f620;",
              "    char *s = data_ov002_0207f620;")
for a, b in sorted(FIELDS.items(), key=lambda kv: -len(kv[0])):
    s = s.replace(a, b)

p = "build/try/b5bff4_ptr.c"
open(p, "w").write(s)
try:
    o = compile_c(p, False)
    mine, mrel = text_relocs(o)
    if len(mine) != len(orig):
        print("SIZE %+d" % (len(mine) - len(orig)))
    else:
        a = bytearray(orig)
        b = bytearray(mine)
        for off in set(orel) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
        print("bytes=%d%s" % (n, "   MATCH" if n == 0 else ""))
        if n == 0:
            open("build/try/%s.c" % SYM, "w").write(s)
            print("PROMOTED")
except Exception as ex:
    print("FAIL %s" % str(ex).split("\n")[0][:120])
