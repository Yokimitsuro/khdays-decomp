#!/usr/bin/env python3
"""Decode a c634 move dispatcher: print its reset block and, crucially, the case -> handler map in
SOURCE order.

The ov228/ov231/ov210 dispatchers all have the same shape -- test ctx[0]+0x1c7 against -1, reset
some flags, copy the id to +0x1c6, then a dense jump table whose every arm is
`func_0203c634(self, 1, handler)`. They match first try once the mapping is right, and getting the
mapping right by hand means resolving a `ldr rN,[pc,#imm]` per case against the literal pool.

The catch this automates: the jump TABLE is index-ordered but the case BODIES are laid out in
source order, and the source order is observable (every dispatcher so far has case 3 out of place).
So the cases must be emitted in body order, which is what this prints.

READ THE WHOLE OUTPUT and paste from it -- do not write the C from memory or from a summary. On
ov255 020cd134 the trailing `case 3` was dropped from an abbreviated recollection of this output
and cost two iterations to rediscover; the tool had printed it correctly.

Usage:  python tools/dumpdispatch.py func_ovNNN_ADDR
Import: from dumpdispatch import decode   ->  dict (used by clonedispatch.py)
"""
import json
import os
import sys

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def decode(name):
    d = json.load(open(os.path.join(ROOT, "build", "func_index.json")))[name]
    h = bytes.fromhex(d["hex"])
    rel = dict((o, s) for o, s in d["relocs"])
    ins = list(Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(h, 0))
    at = {i.address: i for i in ins}

    # 1. Find the jump table. A function can have MORE THAN ONE -- ov259 020cdef8 has a small
    # `switch (move) { case 0xa ... case 0x11 }` before the real move dispatcher, and taking the
    # first one produced complete nonsense (every case pointing at one body, handler unresolved).
    # So collect them all and pick the one whose arms actually call func_0203c634.
    #
    # Also note the case values are not always 0-based: mwcc range-optimises a switch over 0xa..0x11
    # into `sub rN,rN,#0xa ; cmp rN,#7`, so the `sub` carries the base and has to be added back.
    tables = [i.address for i in ins if i.mnemonic == "addls" and "pc, pc" in i.op_str]
    if not tables:
        raise SystemExit("no jump table found -- not a dense-switch dispatcher")

    def arms_call_c634(tbl):
        base = tbl + 8
        kmax = int(at[tbl - 4].op_str.split("#")[1], 0)
        hits = 0
        for k in range(kmax + 1):
            e = at.get(base + k * 4)
            if e is None or e.mnemonic != "b":
                continue
            body = int(e.op_str.lstrip("#"), 0)
            for a in range(body, body + 0x18, 4):
                if rel.get(a) == "func_0203c634":
                    hits += 1
                    break
        return hits

    scored = sorted(((arms_call_c634(t), t) for t in tables), reverse=True)
    tbl = scored[0][1]

    kmax = int(at[tbl - 4].op_str.split("#")[1], 0)
    kbase = 0
    prev = at.get(tbl - 8)
    if prev is not None and prev.mnemonic == "sub" and "#" in prev.op_str:
        kbase = int(prev.op_str.split("#")[1], 0)
    base = tbl + 8

    # 2. each table slot is `b <body>`; resolve the body's pool load to the handler symbol
    case_body, body_handler = {}, {}
    for k in range(kmax + 1):
        case_body[k] = int(at[base + k * 4].op_str.lstrip("#"), 0)
    for k, body in case_body.items():
        for a in range(body, body + 0x10, 4):
            i = at.get(a)
            if i is None:
                break
            if i.mnemonic == "ldr" and "pc," in i.op_str:
                p = ((a + 8) & ~3) + int(i.op_str.split("#")[1].rstrip("]"), 0)
                body_handler[body] = rel.get(p, "0x%03x?" % p)
                break

    deflt = int(at[base - 4].op_str.lstrip("#"), 0)
    bodies = sorted(b for b in set(case_body.values()) if b != deflt)

    # A plain arm is `ldr r2,[pc] ; [mov r0,rN ;] mov r1,#1 ; bl c634 ; b <tail>` -- 16 bytes, or 20
    # when the function keeps self in a callee-saved register and has to restore r0. So there is no
    # fixed "normal" size: take the MODE across this function's own bodies and flag only the
    # outliers. (Flagging everything that is not 16 cried wolf on 14 of ov256's 15 arms.)
    sizes = [bodies[n + 1] - bodies[n] for n in range(len(bodies) - 1)]
    normal = max(set(sizes), key=sizes.count) if sizes else 0x10

    cases = []
    for n, body in enumerate(bodies):
        ks = [k + kbase for k in case_body if case_body[k] == body]
        # An outlier body carries EXTRA code and/or is fallen INTO by a later case -- ov213 020cd35c
        # has `case 2:` store 5 into +0x1c7 and fall into `case 5:`, which reading only the handler
        # hides completely (the pool load is found either way).
        nxt = bodies[n + 1] if n + 1 < len(bodies) else None
        size = nxt - body if nxt is not None else None
        cases.append({"ks": ks, "handler": body_handler.get(body, "??"), "body": body,
                      "outlier": size is not None and size != normal, "size": size})

    reset = [(i.mnemonic, i.op_str) for i in ins if i.address < tbl - 4]
    return {"name": name, "size": d["size"], "kbase": kbase, "kmax": kmax, "tbl": tbl,
            "deflt": deflt, "cases": cases, "normal": normal, "reset": reset,
            "tables": len(tables), "ins": ins, "rel": rel,
            "gaps": [k + kbase for k in case_body if case_body[k] == deflt]}


def main():
    r = decode(sys.argv[1])
    if r["tables"] > 1:
        print("note: %d jump tables in this function; using the one at 0x%x"
              % (r["tables"], r["tbl"]))
    print("%s: %d bytes, cases %d..%d, default -> 0x%x"
          % (r["name"], r["size"], r["kbase"], r["kbase"] + r["kmax"], r["tbl"] + 4))

    print("\ncases in SOURCE order (= body order -- emit them exactly like this):")
    for c in r["cases"]:
        note = ""
        if c["outlier"]:
            note = ("   <-- %d bytes, not the usual %d: EXTRA CODE and/or a fall-through."
                    "  DISASSEMBLE IT." % (c["size"], r["normal"]))
        print("        case %-2s: func_0203c634(self, 1, %s); break;%s"
              % (",".join(str(k) for k in c["ks"]), c["handler"], note))
    if r["gaps"]:
        print("\n(cases %s point at the default -- they are ABSENT from the switch)"
              % ",".join(str(k) for k in r["gaps"]))

    print("\nreset block (everything before the table):")
    for i in r["ins"]:
        if i.address >= r["tbl"] - 4:
            break
        note = "   ; " + r["rel"][i.address] if i.address in r["rel"] else ""
        print("  %03x  %s %s%s" % (i.address, i.mnemonic, i.op_str, note))


if __name__ == "__main__":
    main()
