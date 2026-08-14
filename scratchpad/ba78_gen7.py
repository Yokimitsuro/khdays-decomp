import os
import sys
import json
import itertools

sys.path.insert(0, os.path.join(os.getcwd(), "tools"))
from match import compile_c, text_relocs
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

NAME = "func_ov002_0206ba78"
idx = json.load(open(os.path.join("build", "func_index.json")))
orig = bytes.fromhex(idx[NAME]["hex"])
md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
OM = [i.mnemonic + " " + i.op_str for i in md.disasm(orig, 0)]

TYPES = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

extern char *data_ov002_0207fa00;

"""

# base holding the table block, spelled two ways
BASES = [
    ("    char *base = data_ov002_0207fa00 + 0x8bcc;\n",
     "(int)*(char **)(base + 4) + off"),
    ("    int base = (int)data_ov002_0207fa00 + 0x8bcc;\n",
     "*(int *)(base + 4) + off"),
]

# how the fallback source arm names the entry
FROMS = [
    "(Ov002Vec3 *)entry",
    "(Ov002Vec3 *)(entry + 0)",
]


def build(basei, entry_scope, from_scope, order, fromi, tail):
    bdecl, bexpr = BASES[basei]
    decl = {
        "base": bdecl,
        "off": "    int off = 0;\n",
        "i": "    int i = 0;\n",
        "entry": "    int entry;\n",
        "from": "    Ov002Vec3 *from;\n",
    }
    outer = "".join(decl[n] for n in order)
    body = []
    if entry_scope == "in":
        body.append("        int entry;\n")
    if from_scope == "in":
        body.append("        Ov002Vec3 *from;\n")
    if body:
        body.append("\n")
    body.append("        entry = %s;\n" % bexpr)
    body.append("        if (src == 0) {\n"
                "            from = %s;\n"
                "        } else {\n"
                "            from = src;\n"
                "        }\n" % FROMS[fromi])
    body.append("        *(Ov002Vec3 *)(entry + 0x34) = *from;\n")
    body.append("        if (value == -1) {\n"
                "            *(int *)(entry + 0x40) = *(int *)(entry + 0xc);\n"
                "        } else {\n"
                "            *(int *)(entry + 0x40) = value;\n"
                "        }\n")
    body.append("        i++;\n        off += 0x44;\n" if tail == 0
                else "        off += 0x44;\n        i++;\n")
    return (TYPES + "void %s(Ov002Vec3 *src, int value) {\n" % NAME + outer
            + "\n    do {\n" + "".join(body) + "    } while (i < 4);\n}\n")


def main():
    tmp = os.path.join("build", "try", "ba78", "_matrix3.c")
    results = []
    seen = set()
    for basei in range(len(BASES)):
        for entry_scope in ("in", "out"):
            for from_scope in ("in", "out"):
                names = ["base", "off", "i"]
                if entry_scope == "out":
                    names.append("entry")
                if from_scope == "out":
                    names.append("from")
                for order in itertools.permutations(names):
                    for fromi in range(len(FROMS)):
                        for tail in (0, 1):
                            t = build(basei, entry_scope, from_scope, order,
                                      fromi, tail)
                            if t in seen:
                                continue
                            seen.add(t)
                            with open(tmp, "w") as f:
                                f.write(t)
                            try:
                                o = compile_c(tmp, True)
                                mine, _ = text_relocs(o)
                            except Exception:
                                continue
                            if len(mine) != len(orig):
                                continue
                            mm = [i.mnemonic + " " + i.op_str
                                  for i in md.disasm(mine, 0)]
                            d = sum(1 for k in range(min(len(OM), len(mm)))
                                    if OM[k] != mm[k])
                            results.append((d, t, (basei, entry_scope,
                                                   from_scope, order, fromi,
                                                   tail)))
    results.sort(key=lambda x: x[0])
    print("compiled %d unique variants" % len(seen))
    for d, t, key in results[:8]:
        print("  diff=%d  %s" % (d, key))
    if results:
        with open(os.path.join("build", "try", "ba78", "_best3.c"), "w") as f:
            f.write(results[0][1])
        print("best diff=%d -> build/try/ba78/_best3.c" % results[0][0])


main()
