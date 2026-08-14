"""Combinatorial search for the source shape that puts the entry pointer in r2 and
the struct-copy cursor in r4, the way the ROM allocates func_ov002_0206ba78."""
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

ENTRY_EXPR = [
    "(Ov002PoseEntry *)(*(char **)(base + 4) + off)",
    "(Ov002PoseEntry *)((char *)*(Ov002PoseEntry **)(base + 4) + off)",
    "(Ov002PoseEntry *)(off + *(char **)(base + 4))",
]

DECLS = {
    "base": "    char *base = data_ov002_0207fa00 + 0x8bcc;\n",
    "off": "    int off = 0;\n",
    "i": "    int i = 0;\n",
    "entry": "    Ov002PoseEntry *entry;\n",
    "from": "    Ov002Vec3 *from;\n",
    "dst": "    Ov002Vec3 *dst;\n",
}


def build(entry_scope, from_scope, dst_mode, order, eexpr, copy_form,
          tail_order, entry_style):
    """entry_scope/from_scope/dst_mode: 'out' | 'in' | None.  order: tuple naming the
    outer declaration sequence.  copy_form: how the 12-byte assignment is spelled."""
    outer = []
    for n in order:
        if n in ("base", "off", "i"):
            outer.append(DECLS[n])
        elif n == "entry" and entry_scope == "out":
            outer.append(DECLS["entry"])
        elif n == "from" and from_scope == "out":
            outer.append(DECLS["from"])
        elif n == "dst" and dst_mode and dst_mode[0] == "out":
            outer.append(DECLS["dst"])

    body = []
    if entry_scope == "in":
        if entry_style == 0:
            body.append("        Ov002PoseEntry *entry = %s;\n" % eexpr)
        else:
            body.append("        Ov002PoseEntry *entry;\n")
    if from_scope == "in":
        body.append("        Ov002Vec3 *from;\n")
    if dst_mode and dst_mode[0] == "in":
        body.append("        Ov002Vec3 *dst;\n")
    if body:
        body.append("\n")
    if entry_scope == "out" or (entry_scope == "in" and entry_style == 1):
        body.append("        entry = %s;\n" % eexpr)

    dst_stmt = "        dst = &entry->vecOut;\n" if dst_mode else ""
    if dst_mode and dst_mode[1] == "before":
        body.append(dst_stmt)

    body.append("        if (src == 0) {\n"
                "            from = &entry->vecIn;\n"
                "        } else {\n"
                "            from = src;\n"
                "        }\n")

    if dst_mode and dst_mode[1] == "after":
        body.append(dst_stmt)

    if copy_form == 0 and not dst_mode:
        body.append("        entry->vecOut = *from;\n")
    elif copy_form == 1 and not dst_mode:
        body.append("        *(Ov002Vec3 *)((char *)entry + 0x34) = *from;\n")
    elif dst_mode:
        body.append("        *dst = *from;\n")
    else:
        return None

    body.append("        if (value == -1) {\n"
                "            entry->nValue = entry->nField0c;\n"
                "        } else {\n"
                "            entry->nValue = value;\n"
                "        }\n")
    if tail_order == 0:
        body.append("        i++;\n        off += 0x44;\n")
    else:
        body.append("        off += 0x44;\n        i++;\n")

    return (TYPES + "void %s(Ov002Vec3 *src, int value) {\n" % NAME
            + "".join(outer) + "\n    do {\n" + "".join(body)
            + "    } while (i < 4);\n}\n")


def score(text, path):
    with open(path, "w") as f:
        f.write(text)
    try:
        o = compile_c(path, True)
        mine, _ = text_relocs(o)
    except Exception:
        return None
    if len(mine) != len(orig):
        return ("size", len(mine))
    mm = [i.mnemonic + " " + i.op_str for i in md.disasm(mine, 0)]
    return ("diff", sum(1 for k in range(min(len(OM), len(mm))) if OM[k] != mm[k]))


def main():
    tmp = os.path.join("build", "try", "ba78", "_matrix.c")
    best = []
    seen = set()
    n = 0
    dst_modes = [None, ("in", "before"), ("in", "after"),
                 ("out", "before"), ("out", "after")]
    for entry_scope in ("in", "out"):
        for from_scope in ("in", "out"):
            for dst_mode in dst_modes:
                names = ["base", "off", "i"]
                if entry_scope == "out":
                    names.append("entry")
                if from_scope == "out":
                    names.append("from")
                if dst_mode and dst_mode[0] == "out":
                    names.append("dst")
                perms = list(itertools.permutations(names))
                if len(perms) > 120:
                    perms = perms[:120]
                for order in perms:
                    for eexpr in ENTRY_EXPR[:1]:
                        for copy_form in (0, 1):
                            for tail_order in (0, 1):
                                for entry_style in (0, 1):
                                    if entry_scope == "out" and entry_style == 1:
                                        continue
                                    t = build(entry_scope, from_scope, dst_mode,
                                              order, eexpr, copy_form,
                                              tail_order, entry_style)
                                    if t is None or t in seen:
                                        continue
                                    seen.add(t)
                                    n += 1
                                    r = score(t, tmp)
                                    if r and r[0] == "diff":
                                        best.append((r[1], t, (entry_scope,
                                                    from_scope, dst_mode, order,
                                                    copy_form, tail_order,
                                                    entry_style)))
    best.sort(key=lambda x: x[0])
    print("compiled %d unique variants" % n)
    for d, t, key in best[:6]:
        print("  diff=%d  %s" % (d, key))
    if best and best[0][0] == 0:
        with open(os.path.join("build", "try", "ba78", "_WINNER.c"), "w") as f:
            f.write(best[0][1])
        print("WINNER written")


main()
