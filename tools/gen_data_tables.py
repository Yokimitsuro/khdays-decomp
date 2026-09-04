#!/usr/bin/env python3
"""Emit reconstructed C for small constant tables, one file per contiguous run.

For the tables that are neither strings nor pointers: pick the width the contents are
actually in and write them as a typed array. A word array where the values are small
integers, a halfword array where the size and address are only 2-aligned, a byte array
where the words are packed bytes.

    python tools/gen_data_tables.py ov002 rodata
    python tools/gen_data_tables.py ov002 data --dry

Only symbols WITHOUT relocations are handled: anything with a relocation needs the
pointer generator or a hand-written struct, and writing it as plain numbers would
silently drop the relocation.

The width is the recovered meaning here, along with the run's owner. Where a table has
a known consumer, put it in the header comment -- a wall of numbers with no reader
named is not a reconstruction.
"""
import argparse
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import data_survey  # noqa: E402
import gen_data_strings  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")
SHAPES = ("smallint", "ramp", "ratio", "mixed", "zero")


def runs_for(module, section, index, finished):
    syms = []
    for name, entry in index.items():
        if name in finished or entry.get("ambiguous") or entry["addr"] is None:
            continue
        if entry["module"] != module or entry["section"] != section:
            continue
        shape = data_survey.classify(entry)[0]
        ok = shape in SHAPES and not entry["relocs"]
        syms.append((entry["addr"], entry["size"], name, ok))
    syms.sort()

    out, current = [], []
    for addr, size, name, ok in syms:
        if not ok:
            if current:
                out.append(current)
            current = []
            continue
        if current and addr != current[-1][0] + current[-1][1]:
            out.append(current)
            current = []
        current.append((addr, size, name))
    if current:
        out.append(current)
    return [run for run in out if run]


def declare(addr, size, name, blob, const):
    """The array declaration in the width the contents are in."""
    if size % 4 == 0 and addr % 4 == 0:
        words = struct.unpack("<%dI" % (size // 4), blob)
        if all(value < 4096 for value in words):
            return "int", len(words), [str(v) for v in words]
    if size % 2 == 0 and addr % 2 == 0 and size % 4 != 0:
        half = struct.unpack("<%dH" % (size // 2), blob)
        return "u16", len(half), [str(v) for v in half]
    return "u8", size, [str(b) for b in blob]


def render(module, section, run, index):
    start = run[0][0]
    end = run[-1][0] + run[-1][1]
    const = "const " if section == "rodata" else ""
    out = [
        "/* %s .%s tables, 0x%08x-0x%08x.\n" % (module, section, start, end),
        " *\n",
        " * %d contiguous tables, each written in the width its contents are in:\n"
        % len(run),
        " * words where the values are small integers, bytes where the words are\n",
        " * packed bytes.\n",
        " */\n\n",
        "typedef unsigned char u8;\n",
        "typedef unsigned short u16;\n\n",
    ]
    for addr, size, name in run:
        blob = bytes.fromhex(index[name]["hex"])
        kind, count, cells = declare(addr, size, name, blob, const)
        out.append("%s%s %s[%d] = {\n" % (const, kind, name, count))
        per_line = 16 if kind == "u8" else 8
        for i in range(0, len(cells), per_line):
            out.append("    %s,\n" % ", ".join(cells[i:i + per_line]))
        out.append("};\n\n")
    return "".join(out).rstrip() + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("section", choices=["rodata", "data"])
    ap.add_argument("--dry", action="store_true")
    ap.add_argument("--min-bytes", type=int, default=8)
    args = ap.parse_args()

    with open(INDEX) as fh:
        index = json.load(fh)
    finished = data_survey.done_symbols()

    total = files = 0
    for run in runs_for(args.module, args.section, index, finished):
        size = sum(item[1] for item in run)
        if size < args.min_bytes:
            continue
        path = os.path.join(
            gen_data_strings.source_dir(args.module),
            "%s_tables_%08x.c" % (args.module, run[0][0]),
        )
        print("%-58s %5d bytes, %2d table(s)" % (
            os.path.relpath(path, ROOT).replace("\\", "/"), size, len(run)))
        total += size
        files += 1
        if args.dry:
            continue
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", newline="\n") as fh:
            fh.write(render(args.module, args.section, run, index))
    print("%d file(s), %d bytes" % (files, total))


if __name__ == "__main__":
    main()
