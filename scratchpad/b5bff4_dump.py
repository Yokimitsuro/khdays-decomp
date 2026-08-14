import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
sys.path.insert(0, os.path.join(os.getcwd(), "scratchpad"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM
from b5bff4_repro import HDR, BODY

md = Cs(CS_ARCH_ARM, CS_MODE_ARM)


def dump(tag, src, n=14):
    p = "build/try/b5bff4_dp.c"
    open(p, "w").write(src)
    try:
        o = compile_c(p, False)
        code, _ = text_relocs(o)
    except Exception as ex:
        print("%s FAIL %s" % (tag, str(ex).split("\n")[0][:70]))
        return
    print("--- %s (%d bytes)" % (tag, len(code)))
    for k, i in enumerate(md.disasm(bytes(code), 0)):
        if k >= n:
            break
        print("    %2d %s %s" % (k, i.mnemonic, i.op_str))


dump("cls_no_ptr_s_after", HDR + BODY.replace(
    "    Sess *s = gp;\n    int nClass = cls(&nColumn, s->bMode);",
    "    int nClass = cls(&nColumn, nFrom);\n    Sess *s = gp;"))

dump("cls_no_ptr", HDR + BODY.replace(
    "int nClass = cls(&nColumn, s->bMode);", "int nClass = cls(&nColumn, nFrom);"))

# the classifier reads the field through the global expression instead of the
# variable, and the variable is bound afterwards
dump("glob_read_s_after", HDR + BODY.replace(
    "    Sess *s = gp;\n    int nClass = cls(&nColumn, s->bMode);",
    "    int nClass = cls(&nColumn, gp->bMode);\n    Sess *s = gp;"))
