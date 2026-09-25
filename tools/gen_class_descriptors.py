#!/usr/bin/env python3
"""Emit GameClassDescriptor data files for the InstantiateClass descriptors still unmatched.

    python tools/gen_class_descriptors.py [--dry] [module ...]

A class descriptor is the 20-byte record InstantiateClass (func_02023930 / func_02023960) builds a
task object from: u16 class id, u16 group id, the constructor (its return is the object's first
state function), the method slot, the size of the zero-filled auxiliary state block and the arena
reference. Candidates are the build/data_index.json symbols of exactly 20 bytes whose relocations
are the two function slots (+4, +8) and optionally the arena (+0x10); anything else is left alone.
One file per descriptor, src/overlays/<ov>/data/<ov>_class_<addr>.c (src/data/main_class_<addr>.c
for main), in the layout of the ov008 descriptors. Verify with tools/verify_data_all.py.
"""
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")
RECEIPTS = os.path.join(ROOT, "build", "data_receipts")

TEMPLATE = """/* {module} class descriptor {name}, 0x{start:08x}-0x{end:08x} ({section}).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor {ctor_short}, method {method_short}, 0x{aux:x}-byte state.
 */

typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {{
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
}} GameClassDescriptor;

extern void {ctor}(void);
extern void {method}(void);
{arena_decl}
{const}GameClassDescriptor {name} = {{
    {cid},  /* nClassId */
    {gid},  /* nGroupId */
    {ctor},  /* pfnCtor */
    {method},  /* pfnMethod */
    {aux_dec},  /* nAuxSize */
    {arena},  /* pArena */
}};
"""


def receipted():
    done = set()
    if os.path.isdir(RECEIPTS):
        for f in os.listdir(RECEIPTS):
            if f.endswith(".json"):
                done.add(f[:-5])
    return done


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    index = json.load(open(INDEX))
    done = receipted()
    out = []
    for name, e in sorted(index.items(), key=lambda kv: (kv[1].get("module") or "", kv[1].get("addr") or 0)):
        if e.get("ambiguous") or e.get("addr") is None or e["size"] != 20:
            continue
        if args and e["module"] not in args:
            continue
        if any(name in d for d in done):
            continue
        rel = {o: t for o, t in e["relocs"]}
        if sorted(rel) not in ([4, 8], [4, 8, 16]):
            continue
        if not (rel[4].startswith("func_") and rel[8].startswith("func_")):
            continue
        if any(v for v in (e.get("addends") or {}).values()):
            continue
        b = bytes.fromhex(e["hex"])
        cid, gid = struct.unpack("<HH", b[0:4])
        aux, arena_raw = struct.unpack("<ii", b[12:20])
        if 16 in rel:
            arena = "&" + rel[16]
            arena_decl = "extern int %s;\n" % rel[16]
        elif arena_raw == 0:
            arena = "0"
            arena_decl = ""
        else:
            continue
        module = e["module"]
        start = e["addr"]
        if module == "main":
            path = os.path.join(ROOT, "src", "data", "main_class_%08x.c" % start)
        else:
            path = os.path.join(ROOT, "src", "overlays", module, "data", "%s_class_%08x.c" % (module, start))
        text = TEMPLATE.format(
            module=module, name=name, start=start, end=start + 20, section="." + e["section"],
            ctor=rel[4], method=rel[8], ctor_short=rel[4].split("_")[-1], method_short=rel[8].split("_")[-1],
            aux=aux, aux_dec=aux, cid=cid, gid=gid, arena=arena, arena_decl=arena_decl,
            const="const " if e["section"] == "rodata" else "")
        out.append(path)
        if not dry:
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(text)
    for p in out:
        print(os.path.relpath(p, ROOT).replace(os.sep, "/"))
    print("%d descriptor file(s)%s" % (len(out), " (dry)" if dry else ""), file=sys.stderr)


if __name__ == "__main__":
    main()
