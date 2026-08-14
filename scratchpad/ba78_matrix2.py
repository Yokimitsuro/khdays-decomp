"""Second sweep: the register allocation is already right in f1_best8.c; what is left
is the schedule of the destination-cursor setup.  Enumerate destination-pointer types,
defining expressions, placements and copy spellings looking for diff < 8."""
import sys
import os
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

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002Vec3 vecOut;
    int nValue;
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

"""

IFELSE = ("        if (src == 0) {\n"
          "            from = &entry->vecIn;\n"
          "        } else {\n"
          "            from = src;\n"
          "        }\n")
VALUE = ("        if (value == -1) {\n"
         "            entry->nValue = entry->nField0c;\n"
         "        } else {\n"
         "            entry->nValue = value;\n"
         "        }\n")

# (declared type, defining expression, copy statement)
DSTS = [
    ("Ov002Vec3 *", "&entry->vecOut", "*dst = *from;"),
    ("Ov002PoseEntry *", "entry", "dst->vecOut = *from;"),
    ("char *", "(char *)entry", "*(Ov002Vec3 *)(dst + 0x34) = *from;"),
    ("Ov002Vec3 *", "(Ov002Vec3 *)entry", "dst[13] = *from;"),
    ("Ov002Vec3 *", "&entry->vecIn", "*(Ov002Vec3 *)((char *)dst + 0x34) = *from;"),
    ("Ov002PoseEntry *", "(Ov002PoseEntry *)((char *)entry + 0x34)",
     "*(Ov002Vec3 *)dst = *from;"),
    ("int *", "(int *)entry", "*(Ov002Vec3 *)(dst + 13) = *from;"),
]

ENTRY_EXPR = "(Ov002PoseEntry *)(*(char **)(base + 4) + off)"


def build(entry_scope, dst_scope, dst_place, dsti, order, from_scope):
    dtype, dexpr, dcopy = DSTS[dsti]
    decl = {
        "base": "    char *base = data_ov002_0207fa00 + 0x8bcc;\n",
        "off": "    int off = 0;\n",
        "i": "    int i = 0;\n",
        "entry": "    Ov002PoseEntry *entry;\n",
        "from": "    Ov002Vec3 *from;\n",
        "dst": "    %sdst;\n" % dtype,
    }
    outer = "".join(decl[n] for n in order)
    body = []
    if entry_scope == "in":
        body.append("        Ov002PoseEntry *entry;\n")
    if from_scope == "in":
        body.append("        Ov002Vec3 *from;\n")
    if dst_scope == "in":
        body.append("        %sdst;\n" % dtype)
    if body:
        body.append("\n")
    body.append("        entry = %s;\n" % ENTRY_EXPR)
    dstmt = "        dst = %s;\n" % dexpr
    if dst_place == "before":
        body.append(dstmt)
    body.append(IFELSE)
    if dst_place == "after":
        body.append(dstmt)
    body.append("        " + dcopy + "\n")
    body.append(VALUE)
    body.append("        i++;\n        off += 0x44;\n")
    return (TYPES + "void %s(Ov002Vec3 *src, int value) {\n" % NAME + outer
            + "\n    do {\n" + "".join(body) + "    } while (i < 4);\n}\n")


def main():
    tmp = os.path.join("build", "try", "ba78", "_matrix2.c")
    results = []
    seen = set()
    for entry_scope in ("in", "out"):
        for from_scope in ("in", "out"):
            for dst_scope in ("in", "out"):
                for dst_place in ("before", "after"):
                    for dsti in range(len(DSTS)):
                        names = ["base", "off", "i"]
                        if entry_scope == "out":
                            names.append("entry")
                        if from_scope == "out":
                            names.append("from")
                        if dst_scope == "out":
                            names.append("dst")
                        for order in itertools.permutations(names):
                            t = build(entry_scope, dst_scope, dst_place, dsti,
                                      order, from_scope)
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
                            results.append((d, t, (entry_scope, from_scope,
                                                   dst_scope, dst_place, dsti,
                                                   order)))
    results.sort(key=lambda x: x[0])
    print("compiled %d unique variants" % len(seen))
    for d, t, key in results[:10]:
        print("  diff=%d  %s" % (d, key))
    if results:
        best = results[0]
        with open(os.path.join("build", "try", "ba78", "_best2.c"), "w") as f:
            f.write(best[1])
        print("best diff=%d written to build/try/ba78/_best2.c" % best[0])


main()
