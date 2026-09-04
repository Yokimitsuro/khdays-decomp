#!/usr/bin/env python3
"""Find an already-matched function whose bytes are identical to a pending one.

The game links several copies of the same actor into different overlays. The
copies are compiled from the same source, so a pending function is very often
byte-for-byte the matched one in a sibling overlay once the relocated words are
masked out -- only the overlay-local symbols differ, and those differ by the
constant gap between the two overlays' load addresses.

When that is the case the pending function does not have to be decompiled at
all: take the sibling's source, rewrite `func_ovNNN_XXXXXXXX` / `data_ovNNN_...`
by that gap, and it verifies first try.

    python tools/find_sibling.py func_ov141_020cbfc4     # one function
    python tools/find_sibling.py ov141                   # every pending one

A hit prints the substitution to apply. `--apply <out.c>` writes it for you.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = os.path.join(ROOT, "build", "func_index.json")


def carved():
    """Every function name that has real C under a calls/ or auto/ directory."""
    have = {}
    for base in ("src", "libs"):
        for dirpath, _dirs, files in os.walk(os.path.join(ROOT, base)):
            parts = dirpath.replace(os.sep, "/").split("/")
            if parts[-1] not in ("calls", "auto") or "asm_stubs" in parts:
                continue
            for f in files:
                if f.endswith(".c"):
                    have[f[:-2]] = os.path.join(dirpath, f)
    return have


def masked(entry):
    """The function's bytes with every relocated word zeroed."""
    b = bytearray.fromhex(entry["hex"])
    for off, _sym in entry["relocs"]:
        for k in range(4):
            if off + k < len(b):
                b[off + k] = 0
    return bytes(b)


def siblings(idx, have, name):
    me = idx[name]
    key = masked(me)
    out = []
    for other, e in idx.items():
        if other == name or other not in have or e["size"] != me["size"]:
            continue
        if masked(e) == key and len(e["relocs"]) == len(me["relocs"]):
            out.append(other)
    return out


def gap(idx, name, other):
    """Constant address gap between the two overlays, or None if inconsistent."""
    mine = {o: s for o, s in idx[name]["relocs"]}
    theirs = {o: s for o, s in idx[other]["relocs"]}
    addr = symbol_addresses()
    gaps = set()
    for off, sym in mine.items():
        peer = theirs.get(off)
        if peer is None or peer == sym:
            continue
        a, b = addr.get(sym), addr.get(peer)
        if a is None or b is None:
            return None
        gaps.add(a - b)
    if len(gaps) > 1:
        return None
    return gaps.pop() if gaps else 0


_ADDR = None


def symbol_addresses():
    global _ADDR
    if _ADDR is not None:
        return _ADDR
    _ADDR = {}
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "config")):
        if "symbols.txt" not in files:
            continue
        with open(os.path.join(dirpath, "symbols.txt"), encoding="utf-8",
                  errors="replace") as fh:
            for line in fh:
                parts = line.split()
                if len(parts) < 2:
                    continue
                for tok in parts[1:]:
                    if tok.startswith("addr:"):
                        try:
                            _ADDR[parts[0]] = int(tok[5:], 16)
                        except ValueError:
                            pass
    return _ADDR


def rewrite(text, delta):
    return re.sub(
        r"(func|data)_ov\d+_([0-9a-f]{8})",
        lambda m: "%s_ov%%s_%08x" % (m.group(1), int(m.group(2), 16) + delta),
        text)


def report(idx, have, name, apply_to=None):
    if name not in idx:
        print("%s: not in func_index" % name)
        return
    if name in have:
        print("%s: already carved at %s" % (name, have[name]))
        return
    hits = siblings(idx, have, name)
    if not hits:
        print("%s: no matched sibling (%d bytes)" % (name, idx[name]["size"]))
        return
    for other in hits:
        d = gap(idx, name, other)
        if d is None:
            print("%s <- %s: identical bytes but the symbol gap is not constant"
                  % (name, other))
            continue
        print("%s <- %s  (%d bytes, gap +0x%x)  %s"
              % (name, other, idx[name]["size"], d, have[other]))
        if apply_to:
            src = open(have[other], newline="").read()
            ovnum = re.match(r"func_(ov\d+)_", name).group(1)
            peer = re.match(r"func_(ov\d+)_", other).group(1)

            def shift(m):
                """Only the sibling's OWN symbols move.

                A linked copy calls the same shared code its peer does, so a
                symbol tagged with another overlay -- ov107's actor helpers, in
                practice -- names one object both copies reach and must survive
                the rewrite untouched.
                """
                kind, tag, addr = m.group(1), m.group(2), m.group(3)
                if tag != peer:
                    return m.group(0)
                return "%s_%s_%08x" % (kind, ovnum, int(addr, 16) + d)

            out = re.sub(r"(func|data)_(ov\d+)_([0-9a-f]{8})", shift, src)
            out = out.replace(peer.capitalize(), ovnum.capitalize())
            with open(apply_to, "w", newline="\n") as fh:
                fh.write(out)
            print("   wrote %s" % apply_to)
        return


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    idx = json.load(open(IDX))
    have = carved()
    target = sys.argv[1]
    apply_to = None
    if "--apply" in sys.argv:
        apply_to = sys.argv[sys.argv.index("--apply") + 1]
    if re.fullmatch(r"ov\d+", target):
        names = sorted(n for n in idx
                       if n.startswith("func_%s_" % target) and n not in have)
        if not names:
            print("%s: nothing pending" % target)
        for n in names:
            report(idx, have, n)
    else:
        report(idx, have, target, apply_to)


if __name__ == "__main__":
    main()
