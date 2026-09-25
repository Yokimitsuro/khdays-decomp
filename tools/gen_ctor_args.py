#!/usr/bin/env python3
"""Emit data files for the 20-byte constructor argument blocks still unmatched.

    python tools/gen_ctor_args.py [--dry] [module ...]

Many overlays hand InstantiateClass (func_02023930) a five-word argument block whose first word is
the resource path of the object's model/animation archive (a string symbol such as
"ba/ch/ro/w_d00.p.z") and the other four are small parameters (kind / variant / flags) the class
constructor reads. Candidates are build/data_index.json symbols of exactly 20 bytes with a single
relocation at +0 onto a string symbol; one file per block,
src/overlays/<ov>/data/<ov>_ctorargs_<addr>.c. Verify with tools/verify_data_all.py.
"""
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")
RECEIPTS = os.path.join(ROOT, "build", "data_receipts")
FUNC_INDEX = os.path.join(ROOT, "build", "func_index.json")

TEMPLATE = """/* {module} constructor argument block {name}, 0x{start:08x}-0x{end:08x} ({section}).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ({text!r}) and four parameters the constructor reads.  Used by {users}.
 */

typedef struct ClassCtorArgs {{
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
}} ClassCtorArgs;

extern char {target};  /* the path string */

{const}ClassCtorArgs {name} = {{
    &{target},
    {{ {p0}, {p1}, {p2}, {p3} }},
}};
"""


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    index = json.load(open(INDEX))
    done = set(f[:-5] for f in os.listdir(RECEIPTS)) if os.path.isdir(RECEIPTS) else set()
    funcs = json.load(open(FUNC_INDEX))
    users_of = {}
    for fn, e in funcs.items():
        for o, t in e["relocs"]:
            users_of.setdefault(t, set()).add(fn)
    out = []
    for name, e in sorted(index.items(), key=lambda kv: (kv[1].get("module") or "", kv[1].get("addr") or 0)):
        if e.get("ambiguous") or e.get("addr") is None or e["size"] != 20 or name in done:
            continue
        if args and e["module"] not in args:
            continue
        if [o for o, t in e["relocs"]] != [0] or any(v for v in (e.get("addends") or {}).values()):
            continue
        target = e["relocs"][0][1]
        te = index.get(target)
        if not te or not target.startswith("data_"):
            continue
        tb = bytes.fromhex(te["hex"])
        text = tb.split(b"\0")[0]
        if len(text) < 4 or any(c < 0x20 or c > 0x7e for c in text):
            continue
        b = bytes.fromhex(e["hex"])
        p = struct.unpack("<4i", b[4:20])
        module = e["module"]
        start = e["addr"]
        users = ", ".join(sorted(users_of.get(name, []))) or "no relocated reader"
        path = os.path.join(ROOT, "src", "overlays", module, "data", "%s_ctorargs_%08x.c" % (module, start))
        src = TEMPLATE.format(module=module, name=name, start=start, end=start + 20, section="." + e["section"],
                              text=text.decode("ascii"), users=users, target=target,
                              const="const " if e["section"] == "rodata" else "",
                              p0=p[0], p1=p[1], p2=p[2], p3=p[3])
        out.append(path)
        if not dry:
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", newline="\n") as f:
                f.write(src)
    for q in out:
        print(os.path.relpath(q, ROOT).replace(os.sep, "/"))
    print("%d file(s)%s" % (len(out), " (dry)" if dry else ""), file=sys.stderr)


if __name__ == "__main__":
    main()
