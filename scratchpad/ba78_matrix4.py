"""Sweep the ARRAY-INDEX form, which already reproduces the ROM's exact instruction
schedule, hunting for the register map off=r3 entry=r2 cursor=r4."""
import sys
import os
import re
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

TBL = "(*(Ov002PoseEntry **)(base + 4))"
ENTRY_EXPRS = ["&%s[i]" % TBL, "%s + i" % TBL]
DSTS = [None,
        ("Ov002Vec3 *", "&entry->vecOut", "*dst = *from;"),
        ("Ov002PoseEntry *", "(Ov002PoseEntry *)((char *)entry + 0x34)",
         "*(Ov002Vec3 *)dst = *from;")]
COPIES = ["entry->vecOut = *from;",
          "*(Ov002Vec3 *)((char *)entry + 0x34) = *from;"]


def mapof(txt):
    e = c = o = None
    for t in txt:
        m = re.match(r"^str r\d, \[(r\d), #0x40\]$", t)
        if m and e is None:
            e = m.group(1)
        m = re.match(r"^stm (r\d)!", t)
        if m and c is None:
            c = m.group(1)
        m = re.match(r"^adds (r\d), #0x44$", t)
        if m and o is None:
            o = m.group(1)
    return o, e, c


def build(eexpr, escope, fscope, dst, dplace, order, loopform, copyi):
    dtype = dst[0] if dst else None
    decl = {
        "base": "    char *base = data_ov002_0207fa00 + 0x8bcc;\n",
        "i": "    int i = 0;\n" if loopform == 0 else "    int i;\n",
        "entry": "    Ov002PoseEntry *entry;\n",
        "from": "    Ov002Vec3 *from;\n",
        "dst": "    %sdst;\n" % dtype if dtype else "",
    }
    outer = "".join(decl[n] for n in order)
    body = []
    if escope == "in":
        body.append("        Ov002PoseEntry *entry;\n")
    if fscope == "in":
        body.append("        Ov002Vec3 *from;\n")
    if dst and dplace[0] == "in":
        body.append("        %sdst;\n" % dtype)
    if body:
        body.append("\n")
    body.append("        entry = %s;\n" % eexpr)
    ds = "        dst = %s;\n" % dst[1] if dst else ""
    if dst and dplace[1] == "before":
        body.append(ds)
    body.append("        if (src == 0) {\n"
                "            from = &entry->vecIn;\n"
                "        } else {\n"
                "            from = src;\n"
                "        }\n")
    if dst and dplace[1] == "after":
        body.append(ds)
    body.append("        " + (dst[2] if dst else COPIES[copyi]) + "\n")
    body.append("        if (value == -1) {\n"
                "            entry->nValue = entry->nField0c;\n"
                "        } else {\n"
                "            entry->nValue = value;\n"
                "        }\n")
    if loopform == 0:
        head, tail = "\n    do {\n", "        i++;\n    } while (i < 4);\n}\n"
    else:
        head, tail = "\n    for (i = 0; i < 4; i++) {\n", "    }\n}\n"
    return (TYPES + "void %s(Ov002Vec3 *src, int value) {\n" % NAME + outer
            + head + "".join(body) + tail)


def main():
    tmp = os.path.join("build", "try", "ba78", "_m4.c")
    seen = set()
    results = []
    hits = []
    for eexpr in ENTRY_EXPRS:
        for escope in ("in", "out"):
            for fscope in ("in", "out"):
                for dst in DSTS:
                    places = [("in", "before"), ("in", "after"),
                              ("out", "before"), ("out", "after")] if dst else [(None, None)]
                    for dplace in places:
                        for loopform in (0, 1):
                            for copyi in range(len(COPIES)):
                                if dst and copyi:
                                    continue
                                names = ["base", "i"]
                                if escope == "out":
                                    names.append("entry")
                                if fscope == "out":
                                    names.append("from")
                                if dst and dplace[0] == "out":
                                    names.append("dst")
                                for order in itertools.permutations(names):
                                    t = build(eexpr, escope, fscope, dst,
                                              dplace, order, loopform, copyi)
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
                                    mp = mapof(mm)
                                    results.append((d, mp, t))
                                    if mp == ("r3", "r2", "r4"):
                                        hits.append((d, t))
    results.sort(key=lambda x: x[0])
    print("compiled %d unique 88-byte variants" % len(results))
    seenmaps = {}
    for d, mp, t in results:
        seenmaps.setdefault(mp, d)
    print("register maps reached (map -> best diff):")
    for mp, d in sorted(seenmaps.items(), key=lambda x: x[1]):
        print("   off=%s entry=%s cursor=%s  best diff=%d" % (mp + (d,)))
    print("best overall diff=%d" % results[0][0])
    if hits:
        hits.sort(key=lambda x: x[0])
        with open(os.path.join("build", "try", "ba78", "_m4_hit.c"), "w") as f:
            f.write(hits[0][1])
        print("TARGET MAP REACHED, best diff=%d -> _m4_hit.c" % hits[0][0])
    with open(os.path.join("build", "try", "ba78", "_m4_best.c"), "w") as f:
        f.write(results[0][2])


main()
