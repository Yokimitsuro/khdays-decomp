#!/usr/bin/env python3
"""Emit reconstructed C for runs of string data, one file per contiguous run.

A string symbol is its own meaning, so these need no analysis beyond reading them --
what they need is to be written correctly and sized exactly. Each file covers one
contiguous run of symbols so it can own a single section range in delinks.txt.

    python tools/gen_data_strings.py ov023 data          # write the files
    python tools/gen_data_strings.py ov023 data --dry    # list what it would write

Sizing is the whole game: `const char sym[N] = "text"` pads with NUL to N, which is
exactly how the original blobs are laid out. Symbols holding several NUL-separated
strings are written as one literal with the separators escaped.
"""
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import data_survey  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX = os.path.join(ROOT, "build", "data_index.json")

ESCAPES = {0x5C: "\\\\", 0x22: '\\"', 0x0A: "\\n", 0x0D: "\\r", 0x09: "\\t"}


def literal(blob):
    """A C literal for blob with its trailing NULs dropped; the array size pads them back.

    An escaped NUL is followed by a literal break, because "\\0" then a digit would be
    read as one octal escape.
    """
    body = blob.rstrip(b"\0")
    out = ['"']
    for i, byte in enumerate(body):
        if byte == 0:
            out.append('\\0" "')
            continue
        if byte in ESCAPES:
            out.append(ESCAPES[byte])
        elif 32 <= byte < 127:
            out.append(chr(byte))
        else:
            out.append("\\x%02x" % byte)
            # a hex escape swallows following hex digits, so break the literal
            if i + 1 < len(body) and chr(body[i + 1]) in "0123456789abcdefABCDEF":
                out.append('" "')
    out.append('"')
    return "".join(out)


def runs_for(module, section, index, finished):
    syms = []
    for name, entry in index.items():
        if name in finished or entry.get("ambiguous") or entry["addr"] is None:
            continue
        if entry["module"] != module or entry["section"] != section:
            continue
        syms.append((entry["addr"], entry["size"], name, data_survey.classify(entry)[0]))
    syms.sort()

    out = []
    current = []
    for addr, size, name, shape in syms:
        if shape != "strings":
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


def source_dir(module):
    if module == "main":
        return os.path.join(ROOT, "src", "data")
    return os.path.join(ROOT, "src", "overlays", module, "data")


def render(module, section, run, index):
    start = run[0][0]
    end = run[-1][0] + run[-1][1]
    head = [
        "/* %s .%s strings, 0x%08x-0x%08x.\n" % (module, section, start, end),
        " *\n",
        " * %d symbols in one contiguous run. Each array is sized as the original is, so\n"
        % len(run),
        " * the literal supplies the text and the declared length pads the rest with NUL.\n",
        " */\n\n",
    ]
    # const decides the section, so it is not a style choice: .rodata needs const and
    # .data must not have it, or the symbol lands in the wrong section entirely.
    qualifier = "const char" if section == "rodata" else "char"
    body = []
    for _addr, size, name in run:
        blob = bytes.fromhex(index[name]["hex"])
        body.append("%s %s[%d] = %s;\n" % (qualifier, name, size, literal(blob)))
    return "".join(head) + "\n".join(body)


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

    written = 0
    total = 0
    for run in runs_for(args.module, args.section, index, finished):
        size = sum(item[1] for item in run)
        if size < args.min_bytes:
            continue
        path = os.path.join(
            source_dir(args.module),
            "%s_strings_%08x.c" % (args.module, run[0][0]),
        )
        rel = os.path.relpath(path, ROOT).replace("\\", "/")
        print("%-58s %4d bytes, %2d symbols" % (rel, size, len(run)))
        total += size
        written += 1
        if args.dry:
            continue
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", newline="\n") as fh:
            fh.write(render(args.module, args.section, run, index))
    print("%d file(s), %d bytes" % (written, total))


if __name__ == "__main__":
    main()
