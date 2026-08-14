import sys, os, json
sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

ROOT = os.getcwd()
NAME = "func_ov002_0206ba78"
idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
orig = bytes.fromhex(idx[NAME]["hex"])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)


def dis(b):
    return [i.mnemonic + " " + i.op_str for i in md.disasm(b, 0)]


om = dis(orig)
verbose = os.environ.get("V", "") != ""
for path in sys.argv[1:]:
    try:
        o = compile_c(path, True)
        mine, _ = text_relocs(o)
    except Exception as e:
        print("%-42s COMPILE-FAIL %s" % (os.path.basename(path), str(e)[:90]))
        continue
    if len(mine) != len(orig):
        print("%-42s SIZE %d != %d" % (os.path.basename(path), len(mine), len(orig)))
        continue
    mm = dis(mine)
    d = [i for i in range(min(len(om), len(mm))) if om[i] != mm[i]]
    print("%-42s diff=%d" % (os.path.basename(path), len(d)))
    if verbose and d:
        for i in d[:14]:
            print("   %2d  %-34s | %s" % (i, om[i], mm[i]))
