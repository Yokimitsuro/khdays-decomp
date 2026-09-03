#!/usr/bin/env python3
"""Emit reconstructed C for pointer tables, one file per contiguous run.

A pointer table is all zero in the ROM image -- the target comes from the relocation --
so these read as empty space until the relocations are taken into account. Writing them
is mechanical: list the symbols, put 0 where the entry is null.

    python tools/gen_data_pointers.py ov002 data
    python tools/gen_data_pointers.py ov002 rodata --dry

A table whose targets are all functions becomes an array of function pointers; a mixed
one becomes void * so both kinds fit. const follows the section, because that is what
decides where the object lands.
"""
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import data_survey  # noqa: E402
import gen_data_strings  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")


def runs_for(module, section, index, finished):
    syms = []
    for name, entry in index.items():
        if name in finished or entry.get("ambiguous") or entry["addr"] is None:
            continue
        if entry["module"] != module or entry["section"] != section:
            continue
        syms.append((entry["addr"], entry["size"], name, data_survey.classify(entry)[0]))
    syms.sort()

    out, current = [], []
    for addr, size, name, shape in syms:
        if shape != "pointers":
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


def render(module, section, run, index):
    start = run[0][0]
    end = run[-1][0] + run[-1][1]
    const = "const " if section == "rodata" else ""

    targets = set()
    for _addr, _size, name in run:
        for _off, sym in index[name]["relocs"]:
            targets.add(sym)
    funcs = sorted(t for t in targets if t.startswith("func"))
    datas = sorted(t for t in targets if not t.startswith("func"))
    all_functions = not datas

    head = [
        "/* %s .%s pointer tables, 0x%08x-0x%08x.\n" % (module, section, start, end),
        " *\n",
        " * %d table%s, all zero in the ROM image because every entry is a relocation;\n"
        % (len(run), "" if len(run) == 1 else "s"),
        " * a zero word is a null entry.\n",
        " */\n\n",
    ]
    if all_functions:
        head.append("typedef void (*Ov_Fn)(void);\n\n")
    for sym in funcs:
        head.append("extern void %s(void);\n" % sym)
    for sym in datas:
        head.append("extern int %s;\n" % sym)
    head.append("\n")

    body = []
    for _addr, size, name in run:
        entry = index[name]
        rel = {off: sym for off, sym in entry["relocs"]}
        count = size // 4
        kind = "Ov_Fn" if all_functions else "void *"
        joiner = "" if kind.endswith("*") else " "
        body.append("%s%s%s%s[%d] = {\n" % (const, kind, joiner, name, count))
        for i in range(count):
            sym = rel.get(i * 4)
            if sym is None:
                cell = "0"
            elif all_functions:
                cell = sym
            elif sym.startswith("func"):
                cell = "(void *)%s" % sym
            else:
                cell = "&%s" % sym
            body.append("    %s,\n" % cell)
        body.append("};\n")
    return "".join(head) + "\n".join(body)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("section", choices=["rodata", "data"])
    ap.add_argument("--dry", action="store_true")
    args = ap.parse_args()

    with open(INDEX) as fh:
        index = json.load(fh)
    finished = data_survey.done_symbols()

    total = 0
    files = 0
    for run in runs_for(args.module, args.section, index, finished):
        size = sum(item[1] for item in run)
        path = os.path.join(
            gen_data_strings.source_dir(args.module),
            "%s_pointers_%08x.c" % (args.module, run[0][0]),
        )
        print("%-58s %4d bytes, %2d table(s)" % (
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
