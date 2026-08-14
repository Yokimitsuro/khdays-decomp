"""The staged source MATCHes but contains `register int nTag asm("r7")`, an
explicit register binding. The contract bars asm from integrated C, so the whole
question is whether that binding is load-bearing. Try removing it and the
plausible replacements that keep it real C.
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
SRC = open("staging/ov002/func_ov002_0205bff4.c").read()
OLD = '    register int nTag asm("r7");'
assert OLD in SRC


def score(src):
    p = "build/try/b5bff4_da.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, mrel = text_relocs(o)
    except Exception as ex:
        return None, None, "?", str(ex).split("\n")[0][:60]
    n = None
    if len(code) == len(ORIG):
        a = bytearray(ORIG)
        b = bytearray(code)
        for off in set(OREL) | set(mrel):
            for k in range(4):
                if off + k < len(a):
                    a[off + k] = 0
                    b[off + k] = 0
        n = sum(1 for i in range(len(a)) if a[i] != b[i])
    sr = "?"
    for i in md.disasm(bytes(code), 0):
        m = re.match(r"^ldr (r\w+), \[r\d+\]$", i.mnemonic + " " + i.op_str)
        if m:
            sr = m.group(1)
            break
    return len(code), n, sr, None


VAR = {
    "as staged (asm r7)": OLD,
    "plain int": "    int nTag;",
    "register int": "    register int nTag;",
    "declared after s": None,
    "moved into the state struct": None,
}

print("%-40s %-6s %-6s %s" % ("variant", "size", "bytes", "s"))
for tag in ("as staged (asm r7)", "plain int", "register int"):
    src = SRC.replace(OLD, VAR[tag])
    size, n, sr, err = score(src)
    if err:
        print("%-40s FAIL %s" % (tag, err))
        continue
    print("%-40s %-6d %-6s s=%s%s"
          % (tag, size, n, sr, "   MATCH" if n == 0 else ""))

# nTag declared last among the locals, without any binding
s2 = SRC.replace(OLD + "\n", "")
s2 = s2.replace("    Ov002PanelMoveState state;",
                "    Ov002PanelMoveState state;\n    int nTag;")
size, n, sr, err = score(s2)
print("%-40s %-6s %-6s s=%s%s" % ("plain int declared last", size, n, sr,
                                  "   MATCH" if n == 0 else ""))

# nTag as a further field of the state aggregate
s3 = SRC.replace(OLD + "\n", "")
s3 = s3.replace("    int nTagOrder;\n", "    int nTagOrder;\n    int nTag;\n")
s3 = s3.replace("#define nClass state.nClass",
                "#define nClass state.nClass\n#define nTag state.nTag")
size, n, sr, err = score(s3)
print("%-40s %-6s %-6s s=%s%s" % ("nTag as a state field", size, n, sr,
                                  "   MATCH" if n == 0 else ""))
if n == 0:
    open("build/try/%s_noasm.c" % SYM, "w").write(s3)
    print("saved build/try/%s_noasm.c" % SYM)
