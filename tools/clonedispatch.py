#!/usr/bin/env python3
"""Clone a matched move dispatcher onto a byte-identical twin in another overlay.

Many move dispatchers are the SAME function modulo the overlay's handler symbols: same reset block
instruction-for-instruction, same case order, same size. For those the C is a pure symbol swap, so
this reads the already-matched source, maps each handler positionally onto the target's own, and
writes the twin.

It REFUSES when the two are not actually twins -- if the sizes differ, or the reset blocks differ
once the pool-relative loads are ignored, the codegen is not the same and the C must be written by
hand. That check is the whole point: a clone that is not really a clone would otherwise produce a
plausible file that quietly fails to verify (or worse, verifies while its prose lies).

    python tools/clonedispatch.py <src_c> <src_func> <dst_func>

Then verify the result as usual -- this tool does not decide anything, it only saves the retyping.
"""
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

from dumpdispatch import decode  # noqa: E402


def ov_of(name):
    m = re.match(r"func_(ov\d+)_([0-9a-f]{8})$", name)
    if not m:
        raise SystemExit("not a func_ovNNN_ADDR name: " + name)
    return m.group(1), m.group(2)


def main():
    if len(sys.argv) != 4:
        raise SystemExit(__doc__)
    src_c, src_fn, dst_fn = sys.argv[1:4]
    sov, saddr = ov_of(src_fn)
    dov, daddr = ov_of(dst_fn)

    idx = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
    for n in (src_fn, dst_fn):
        if n not in idx:
            raise SystemExit("no en func_index: " + n)
    if idx[src_fn]["size"] != idx[dst_fn]["size"]:
        raise SystemExit("NOT twins: %d vs %d bytes -- write it by hand"
                         % (idx[src_fn]["size"], idx[dst_fn]["size"]))

    s = decode(src_fn)
    d = decode(dst_fn)
    if s["reset"] != d["reset"]:
        raise SystemExit("NOT twins: reset blocks differ -- write it by hand")
    if [c["ks"] for c in s["cases"]] != [c["ks"] for c in d["cases"]]:
        raise SystemExit("NOT twins: case order differs -- write it by hand")

    def addr_of(sym):
        m = re.match(r"func_ov\d+_([0-9a-f]{8})$", sym)
        if not m:
            raise SystemExit("unresolved handler in one of the twins: " + sym)
        return m.group(1)

    src = io.open(src_c, encoding="utf-8").read()
    pairs = [(saddr, daddr)] + [(addr_of(a["handler"]), addr_of(b["handler"]))
                                for a, b in zip(s["cases"], d["cases"])]
    for a, b in pairs:
        old = "func_%s_%s" % (sov, a)
        if old not in src:
            raise SystemExit("handler missing from source C: " + old)
        src = src.replace(old, "func_%s_@%s" % (dov, b))
    src = src.replace("func_%s_@" % dov, "func_%s_" % dov).replace(sov, dov)

    out = os.path.join(ROOT, "src", "overlays", dov, "calls", "%s.c" % dst_fn)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    io.open(out, "w", encoding="utf-8", newline="\n").write(src)
    print("wrote %s (twin of %s, %d handlers)" % (out, src_fn, len(pairs) - 1))
    print("now: python tools/verify_idx.py %s %s" % (out, dst_fn))


if __name__ == "__main__":
    main()
