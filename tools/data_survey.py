#!/usr/bin/env python3
"""Classify every unreconstructed DATA symbol so the queue can be worked by shape.

Reading 4757 symbols one at a time is the wrong order of work. This sorts them into
shapes that each have a known attack, and ranks by bytes, so a pass can take the whole
of one shape at once instead of rediscovering the method per symbol.

    python tools/data_survey.py                 # summary by shape
    python tools/data_survey.py --shape ramp    # list one shape, largest first
    python tools/data_survey.py --module ov008  # restrict to a module
    python tools/data_survey.py --limit 40

Shapes, in the order they are tested:

  zero        all bytes zero -- trivial, but check it is really .data and not BSS
  pointers    every word is a relocation; write the symbol names, nothing else
  strings     printable ASCII with NUL terminators
  identity    a u8 map that is mostly i -> i, like the case-folding tables
  ramp        strictly monotonic u8/u16/s16; a formula table, fit it
  ratio       monotonic with a near-constant successive ratio; exponential, note the ratio
  smallint    a handful of distinct small values; a class or index table, needs its reader
  mixed       none of the above; needs the consumer before anything can be recovered

Already-reconstructed symbols are skipped: a receipt whose source still exists means the
symbol is done, so the survey only ever shows what is left.
"""
import argparse
import json
import os
import struct
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")
RECEIPTS = os.path.join(ROOT, "build", "data_receipts")

SHAPES = ["zero", "pointers", "strings", "identity", "ramp", "ratio", "smallint", "mixed"]


def done_symbols():
    out = set()
    if not os.path.isdir(RECEIPTS):
        return out
    for name in os.listdir(RECEIPTS):
        if not name.endswith(".json"):
            continue
        with open(os.path.join(RECEIPTS, name)) as fh:
            receipt = json.load(fh)
        if os.path.isfile(os.path.join(ROOT, receipt.get("source", ""))):
            out.add(receipt["symbol"])
    return out


def as_words(blob, size, signed=False):
    count = len(blob) // size
    if count < 4:
        return None
    code = {1: "b", 2: "h", 4: "i"}[size]
    if not signed:
        code = code.upper()
    return struct.unpack("<%d%s" % (count, code), blob[:count * size])


def monotonic(seq):
    return all(b >= a for a, b in zip(seq, seq[1:])) and seq[-1] > seq[0]


def classify(entry):
    blob = bytes.fromhex(entry["hex"])
    size = entry["size"]

    if not any(blob):
        return "zero", ""
    if entry["relocs"] and size == 4 * len(entry["relocs"]):
        return "pointers", "%d pointers" % len(entry["relocs"])
    if entry["relocs"]:
        return "mixed", "%d relocs" % len(entry["relocs"])

    # Printable-and-NUL alone calls a u32 array of small values a string: 34, 35, 36 ...
    # reads as '"...#...$...'. What separates them is that a u32 ramp leaves every non-NUL
    # byte isolated, while even a two-letter string has them adjacent. So: all printable,
    # NUL-terminated, a run of at least two, and content that looks like a name or a path.
    printable = sum(1 for b in blob if 32 <= b < 127 or b in (0, 9, 10, 13))
    runs = [len(part) for part in blob.split(b"\0") if part]
    if printable == len(blob) and blob and blob[-1] == 0 and runs and max(runs) >= 2:
        body = blob.replace(b"\0", b"")
        good = sum(1 for c in body
                   if chr(c).isalnum() or chr(c) in "/_-.&% +:,'()[]!?")
        if good * 2 >= len(body):
            head = blob.split(b"\0")[0].decode("ascii", "replace")
            return "strings", repr(head[:28])

    if size in (128, 256) and max(blob) < size:
        off = sum(1 for i, b in enumerate(blob) if b != i)
        if off * 4 < size:
            return "identity", "%d entries differ from i -> i" % off

    for width, signed in ((2, False), (2, True), (1, False), (4, False)):
        seq = as_words(blob, width, signed)
        if seq is None or len(seq) < 8:
            continue
        body = seq[:-1] if seq[-1] == 0 and seq[-2] != 0 else seq
        if len(body) < 8 or not monotonic(body):
            continue
        unit = "u%d" % (width * 8) if not signed else "s%d" % (width * 8)
        positive = [x for x in body if x > 0]
        if len(positive) > 6:
            ratios = [b / float(a) for a, b in zip(positive, positive[1:]) if a]
            tail = ratios[len(ratios) // 2:]
            if tail and max(tail) - min(tail) < 0.02 and sum(tail) / len(tail) > 1.02:
                return "ratio", "%s x%.4f/step, %d..%d" % (
                    unit, sum(tail) / len(tail), body[0], body[-1])
        return "ramp", "%s %d entries, %d..%d" % (unit, len(body), body[0], body[-1])

    distinct = len(set(blob))
    if distinct <= 12:
        return "smallint", "%d distinct byte values" % distinct
    return "mixed", "%d distinct byte values" % distinct


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--shape", choices=SHAPES)
    ap.add_argument("--module")
    ap.add_argument("--limit", type=int, default=25)
    args = ap.parse_args()

    with open(INDEX) as fh:
        index = json.load(fh)
    finished = done_symbols()

    rows = []
    for name, entry in index.items():
        if name in finished or entry.get("ambiguous"):
            continue
        if args.module and entry["module"] != args.module:
            continue
        shape, note = classify(entry)
        rows.append((entry["size"], shape, name, entry["module"], entry["section"], note))

    if args.shape:
        rows = [r for r in rows if r[1] == args.shape]
    rows.sort(reverse=True)

    counts = Counter(r[1] for r in rows)
    total = Counter()
    for size, shape, _n, _m, _s, _note in rows:
        total[shape] += size
    print("%d symbols left, %d bytes" % (len(rows), sum(r[0] for r in rows)))
    for shape in SHAPES:
        if counts[shape]:
            print("  %-9s %5d symbols  %7d bytes" % (shape, counts[shape], total[shape]))
    print()
    for size, shape, name, module, section, note in rows[:args.limit]:
        print("%7d  %-9s %-28s %-7s .%-7s %s" % (size, shape, name, module, section, note))


if __name__ == "__main__":
    main()
