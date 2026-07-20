#!/usr/bin/env python3
"""Struct discovery by accessor sweep.

When a global has dozens of tiny users, most are one-field accessors of the shape
`*(g + D) -> +OFFSET`. Disassembling every small user and reading the offset out
of each gives the field map, each field's WIDTH, whether it is an array (and its
stride), and GET/SET pairs that corroborate each other -- with no Ghidra round
trip and without reading any function's logic.

    python tools/accsweep.py data_ov008_02090f04 [--max-size 40]

⚠ Two traps, both hit for real (see references/naming-hubs.md):

  Do NOT sum every immediate. The `ldr rX,[pc,#N]` pool load and the `[rX,#4]`
  global deref are not part of the field offset; adding them inflates every
  result by 8-0xc and the output still looks entirely plausible.

  It assumes ONE field per accessor. A setter that writes two fields comes out as
  the SUM of both bases, landing nowhere near either. The tell is an offset far
  outside the cluster the rest form -- and running the sweep on a twin unit does
  NOT catch it, since the twin produces the same bogus number.
"""
import json
import os
import re
import sys

import capstone

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDX = json.load(open(os.path.join(ROOT, "build", "func_index.json")))
LD = re.compile(r'^(ldr|ldrb|ldrh|ldrsh|ldrsb|str|strb|strh)$')
WIDTH = {'ldr': 4, 'str': 4, 'ldrh': 2, 'strh': 2, 'ldrsh': 2,
         'ldrb': 1, 'strb': 1, 'ldrsb': 1}

md_arm = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)
md_thm = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)


def sweep(glob, max_size=40):
    rows = []
    for name, e in IDX.items():
        if not any(s == glob for _o, s in e["relocs"]):
            continue
        if e["size"] > max_size:
            continue
        code = bytes.fromhex(e["hex"])
        ins = list(md_arm.disasm(code, 0))
        if not ins or all(i.mnemonic == 'andeq' for i in ins):
            ins = list(md_thm.disasm(code, 0))
        base = 0
        idx = None
        fin = None
        mn = None
        deref = False
        nloads = 0
        for i in ins:
            if i.mnemonic in ('add', 'adds') and re.match(r'^r\d+, r\d+, #', i.op_str):
                base += int(i.op_str.split('#')[1], 0)
            elif i.mnemonic in ('add', 'adds') and re.match(r'^r\d+, #', i.op_str):
                base += int(i.op_str.split('#')[1], 0)
            elif i.mnemonic in ('add', 'adds') and \
                    re.match(r'^r\d+, r\d+, r\d+(, lsl #\d+)?$', i.op_str):
                m = re.search(r'lsl #(\d+)', i.op_str)
                idx = 1 << int(m.group(1)) if m else 1
            elif LD.match(i.mnemonic):
                m = re.search(r'\[(r\d+|pc)(?:, #(0x[0-9a-f]+|\d+))?\]', i.op_str)
                if not m or m.group(1) == 'pc':
                    continue                       # the pool load is not a field
                disp = int(m.group(2), 0) if m.group(2) else 0
                if not deref and base == 0 and idx is None and disp in (0, 4):
                    deref = True                   # the global deref itself
                    continue
                nloads += 1
                fin = disp
                mn = i.mnemonic
        if fin is None:
            continue
        rows.append({"off": base + fin, "mn": mn, "w": WIDTH.get(mn, 4),
                     "idx": idx, "size": e["size"], "name": name,
                     "multi": nloads > 1})
    rows.sort(key=lambda r: r["off"])
    return rows


def main():
    glob = sys.argv[1]
    mx = 40
    if "--max-size" in sys.argv:
        mx = int(sys.argv[sys.argv.index("--max-size") + 1])
    rows = sweep(glob, mx)
    if not rows:
        print("no small accessors found for " + glob)
        return
    offs = [r["off"] for r in rows]
    mid = offs[len(offs) // 2]
    print("%s: %d accessors" % (glob, len(rows)))
    for r in rows:
        # flag anything wildly outside the cluster -- that is the multi-field tell
        odd = "  <-- SUSPECT (outside the cluster; multi-field setter?)" \
              if abs(r["off"] - mid) > 0x8000 or r["multi"] else ""
        print("  +0x%04x  %-6s w=%d %-10s %3dB  %s%s"
              % (r["off"], r["mn"], r["w"],
                 ("stride %d" % r["idx"]) if r["idx"] else "",
                 r["size"], r["name"], odd))


if __name__ == "__main__":
    main()
