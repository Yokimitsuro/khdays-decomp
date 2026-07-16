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

Usage:  python tools/dumpdispatch.py func_ovNNN_ADDR
"""
import json, os, re, sys
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
name = sys.argv[1]
d = json.load(open(os.path.join(ROOT, "build", "func_index.json")))[name]
h = bytes.fromhex(d["hex"])
rel = dict((o, s) for o, s in d["relocs"])
ins = list(Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(h, 0))
at = {i.address: i for i in ins}

# 1. the jump table: `cmp rN,#K` immediately before `addls pc,pc,rN,lsl #2`
tbl = None
for i in ins:
    if i.mnemonic == "addls" and "pc, pc" in i.op_str:
        tbl = i.address
        break
if tbl is None:
    print("no jump table found -- not a dense-switch dispatcher")
    sys.exit(1)
kmax = int(at[tbl - 4].op_str.split("#")[1], 0)
base = tbl + 8
print("%s: %d bytes, cases 0..%d, default -> 0x%x" % (name, d["size"], kmax, base - 4))

# 2. each table slot is `b <body>`; resolve the body's pool load to the handler symbol
case_body, body_handler = {}, {}
for k in range(kmax + 1):
    e = at[base + k * 4]
    tgt = int(e.op_str.lstrip("#"), 0)
    case_body[k] = tgt
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
print("\ncases in SOURCE order (= body order -- emit them exactly like this):")
for body in sorted(set(case_body.values())):
    if body == deflt:
        continue
    ks = [k for k in case_body if case_body[k] == body]
    print("        case %-2s: func_0203c634(self, 1, %s); break;"
          % (",".join(str(k) for k in ks), body_handler.get(body, "??")))
gaps = [k for k in case_body if case_body[k] == deflt]
if gaps:
    print("\n(cases %s point at the default -- they are ABSENT from the switch)"
          % ",".join(str(k) for k in gaps))

print("\nreset block (everything before the table):")
for i in ins:
    if i.address >= tbl - 4:
        break
    note = "   ; " + rel[i.address] if i.address in rel else ""
    print("  %03x  %s %s%s" % (i.address, i.mnemonic, i.op_str, note))
