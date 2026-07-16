#!/usr/bin/env python3
"""Generate the C for a plain c634 move dispatcher straight from the machine code.

`dumpdispatch.py` gets the case->handler mapping right; the remaining hand work is reading the
reset block's constants off the disassembly and typing ~90 lines of boilerplate. Both are error
-prone in the same way: on ov255 020cd134 a case was lost writing the switch by hand, and the reset
constants (which hw60 mask, which +0x1ae bits, which sub-object offset) are easy to transpose
between near-identical overlays.

So this PARSES the reset block instead. Each block below is a shape the family actually uses; if
anything in the reset does not match one of them, the tool REFUSES rather than guessing -- an
unrecognised reset means this dispatcher is not plain and its C must be written by hand.

    python tools/genmove.py func_ovNNN_ADDR [-w]

It prints what it derived (read that -- it is the whole point) and the C. Verify as always:
    python tools/verify_idx.py src/overlays/ovNNN/calls/func_ovNNN_ADDR.c func_ovNNN_ADDR
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

from dumpdispatch import decode  # noqa: E402

HW60_AND = [("ldrh", r"r\d+, \[r\d+, #0x60\]"), ("lsl", r"r\d+, r\d+, #0x10"),
            ("lsr", r"r\d+, r\d+, #0x18"), ("bic", r"r\d+, r\d+, #(0x[0-9a-f]+|\d+)"),
            ("lsl", r"r\d+, r\d+, #0x10"), ("lsr", r"r\d+, r\d+, #0x10"),
            ("bic", r"r\d+, r\d+, #0xff00"), ("lsl", r"r\d+, r\d+, #0x18"),
            ("orr", r"r\d+, r\d+, r\d+, lsr #16"), ("strh", r"r\d+, \[r\d+, #0x60\]")]

HW60_OR = [("ldrh", r"r\d+, \[r\d+, #0x60\]"), ("lsl", r"r\d+, r\d+, #0x10"),
           ("lsr", r"r\d+, r\d+, #0x18"), ("orr", r"r\d+, r\d+, #(0x[0-9a-f]+|\d+)"),
           ("bic", r"r\d+, r\d+, #0xff00"), ("lsl", r"r\d+, r\d+, #0x18"),
           ("orr", r"r\d+, r\d+, r\d+, lsr #16"), ("strh", r"r\d+, \[r\d+, #0x60\]")]

# The +0x1ae write usually reloads ctx[0] and re-adds 0x100, but when the -1 guard's own
# `add rN,rN,#0x100` is still live it goes straight to the ldrh (ov244 020cfa04, ov277 020cf99c).
AE_BASE = [("ldr", r"r\d+, \[r4\]"), ("add", r"r\d+, r\d+, #0x100")]
AE_CORE = [("ldrh", r"r\d+, \[r\d+, #0xae\]"), ("bic", r"r\d+, r\d+, #(0x[0-9a-f]+|\d+)"),
           ("strh", r"r\d+, \[r\d+, #0xae\]")]
AE = AE_BASE + AE_CORE

# `*(u16 *)(ctx[0] + 0x1b0) = *(u8 *)((char *)ctx + 0x56)` -- a byte widened into a halfword slot
# (ov137 020ccc50 and its twins).
COPY56 = [("ldr", r"r\d+, \[r4\]"), ("ldrb", r"r\d+, \[r4, #0x56\]"),
          ("add", r"r\d+, r\d+, #0x100"), ("strh", r"r\d+, \[r\d+, #0xb0\]")]

SUB = [("ldr", r"r\d+, \[r4\]"), ("ldr", r"r\d+, \[r\d+, #(0x[0-9a-f]+)\]"),
       ("ldr", r"r\d+, \[r\d+, #8\]"), ("lsl", r"r\d+, r\d+, #0x18"),
       ("lsr", r"r\d+, r\d+, #0x18"), ("(orr|bic)", r"r\d+, r\d+, #(0x[0-9a-f]+|\d+)"),
       ("bic", r"r\d+, r\d+, #0xff"), ("and", r"r\d+, r\d+, #0xff"),
       ("orr", r"r\d+, r\d+, r\d+"), ("str", r"r\d+, \[r\d+, #8\]")]

COPY_LATE = [("ldr", r"r\d+, \[r4\]"), ("add", r"r\d+, r\d+, #0x100"),
             ("ldrsb", r"r\d+, \[r\d+, #0xc7\]"), ("strb", r"r\d+, \[r\d+, #0x1c6\]")]


RELOAD = [("ldr", r"r\d+, \[r4\]")]


def eat_reload(rs, pos, shape):
    """Like eat(), but the block may be preceded by a reload of ctx[0] (`ldr rN,[r4]`).

    Every block reloads ctx[0] EXCEPT when it can reuse the register the -1 guard already loaded it
    into -- ov119's first hw60 write does that, ov245's does not. Same C either way (`ctx[0]` is a
    common subexpression mwcc reloads or not as it pleases), so both spellings must be accepted.
    """
    c, q = eat(rs, pos, RELOAD + shape)
    if c is not None:
        return c, q
    return eat(rs, pos, shape)


def eat(rs, pos, shape):
    """Match `shape` at rs[pos]; return (captures, newpos) or (None, pos)."""
    caps = []
    for n, (mn, ops) in enumerate(shape):
        if pos + n >= len(rs):
            return None, pos
        m, o = rs[pos + n]
        if not re.fullmatch(mn, m) or not re.fullmatch(ops, o):
            return None, pos
        g = re.fullmatch(ops, o).groups()
        caps.extend([x for x in g if x is not None])
        if re.fullmatch(mn, m).groups():
            caps.append(m)
    return caps, pos + len(shape)


def parse_reset(rs):
    """Return a list of ('kind', args) steps, or raise on anything unrecognised."""
    steps = []
    p = 0
    # prologue + the -1 guard
    head = [("push", r"\{r4, lr\}"), ("ldr", r"r4, \[r0, #4\]"), ("mvn", r"r\d+, #0"),
            ("ldr", r"r\d+, \[r4\]"), ("add", r"r\d+, r\d+, #0x100"),
            ("ldrsb", r"r\d+, \[r\d+, #0xc7\]"), ("cmp", r"r\d+, r\d+")]
    c, p = eat(rs, p, head)
    if c is None:
        raise SystemExit("REFUSING: prologue/guard is not the plain family shape")
    if rs[p][0] == "beq":
        steps.append(("guard", "beq"))
    elif rs[p][0] == "popeq":
        steps.append(("guard", "popeq"))
    else:
        raise SystemExit("REFUSING: guard is %s, expected beq/popeq" % rs[p][0])
    p += 1

    while p < len(rs):
        m, o = rs[p]
        if m == "strb" and re.fullmatch(r"r\d+, \[r\d+, #0x1c6\]", o):
            steps.append(("copy_early", None)); p += 1; continue
        if m == "mov" and re.fullmatch(r"r\d+, #0", o):
            c, q = eat(rs, p + 1, [("strb", r"r\d+, \[r4, #0x64\]"), ("str", r"r\d+, \[r4, #0x4c\]")])
            if c is None:
                raise SystemExit("REFUSING: unrecognised `mov #0` block at %d" % p)
            steps.append(("clear64_4c", None)); p = q; continue
        c, q = eat_reload(rs, p, HW60_AND)
        if c is not None:
            steps.append(("hw60_and", int(c[0], 0))); p = q; continue
        c, q = eat_reload(rs, p, HW60_OR)
        if c is not None:
            steps.append(("hw60_or", int(c[0], 0))); p = q; continue
        c, q = eat(rs, p, AE)
        if c is None:
            c, q = eat(rs, p, AE_CORE)
        if c is not None:
            steps.append(("ae", int(c[0], 0))); p = q; continue
        c, q = eat(rs, p, COPY56)
        if c is not None:
            steps.append(("copy56", None)); p = q; continue
        c, q = eat(rs, p, SUB)
        if c is not None:
            off, val, op = int(c[0], 0), int(c[1], 0), c[2]
            steps.append(("sub_or" if op == "orr" else "sub_and", (off, val))); p = q; continue
        c, q = eat(rs, p, COPY_LATE)
        if c is not None:
            steps.append(("copy_late", None)); p = q; continue
        # the switch's own read closes the reset
        c, q = eat(rs, p, [("ldr", r"r\d+, \[r4\]"), ("add", r"r\d+, r\d+, #0x100"),
                           ("ldrsb", r"r\d+, \[r\d+, #0xc6\]")])
        if c is not None and q >= len(rs):
            return steps
        c, q = eat(rs, p, [("ldrsb", r"r\d+, \[r\d+, #0xc6\]")])
        if c is not None and q >= len(rs):
            return steps
        raise SystemExit("REFUSING: unrecognised reset instruction at %d: %s %s" % (p, m, o))
    return steps


def emit(name, r, steps):
    ov = re.match(r"func_(ov\d+)_", name).group(1)
    hs = [c["handler"] for c in r["cases"]]
    guard = dict(steps).get("guard")
    kinds = [k for k, _ in steps]

    L = []
    L.append("/* %s -- %s's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means" % (name, ov))
    L.append(" * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is")
    L.append(" * cleared on every path." + ("" if guard == "beq" else
             "\n *\n * The \"nothing queued\" case RETURNS outright (a predicated `popeq`)."))
    order = [c["ks"][0] for c in r["cases"]]
    if order != sorted(order):
        L.append(" *\n * Source case order: %s.\n"
                 " * That is the body order, and it is what the switch has to say."
                 % ", ".join(str(k) for k in order))
    L.append(" *\n * Generated by tools/genmove.py from the machine code and verified byte-exact. */")
    L.append("")
    if "hw60_and" in kinds or "hw60_or" in kinds:
        L += ["typedef struct {", "    unsigned short lo : 8;", "    unsigned short hi : 8;",
              "} Hw60;", ""]
    if "sub_or" in kinds or "sub_and" in kinds:
        L += ["typedef struct {", "    unsigned f : 8;", "} B8;", ""]
    L.append("extern void func_0203c634(int self, int slot, void (*cb)(void));")
    L += ["extern void %s(void);" % h for h in hs]
    L += ["", "void %s(int self) {" % name, "    int *ctx;"]
    if "hw60_or" in kinds:
        L.append("    unsigned short v;")
    L += ["", "    ctx = *(int **)(self + 4);"]

    ind = "    "
    if guard == "beq":
        L.append("    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {")
        ind = "        "
    else:
        L += ["    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {", "        return;", "    }", ""]

    for k, a in steps:
        if k == "guard":
            continue
        if k == "copy_early" or k == "copy_late":
            L.append(ind + "*(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);")
        elif k == "clear64_4c":
            L += [ind + "*(unsigned char *)((char *)ctx + 0x64) = 0;", ind + "ctx[0x13] = 0;"]
        elif k == "hw60_and":
            L.append(ind + "((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x%x;" % a)
        elif k == "hw60_or":
            L += [ind + "v = *(unsigned short *)(ctx[0] + 0x60);",
                  ind + "*(unsigned short *)(ctx[0] + 0x60) =",
                  ind + "    (unsigned short)((v & ~0xff00)",
                  ind + "                     | (((((unsigned int)v << 0x10) >> 0x18 | 0x%x) << 0x18) >> 0x10));" % a]
        elif k == "copy56":
            L.append(ind + "*(unsigned short *)(ctx[0] + 0x1b0) = *(unsigned char *)((char *)ctx + 0x56);")
        elif k == "ae":
            L.append(ind + "*(unsigned short *)(ctx[0] + 0x1ae) &= ~%d;" % a)
        elif k == "sub_or":
            L.append(ind + "((B8 *)(*(int *)(ctx[0] + 0x%x) + 8))->f |= %d;" % a)
        elif k == "sub_and":
            L.append(ind + "((B8 *)(*(int *)(ctx[0] + 0x%x) + 8))->f &= ~%d;" % a)

    L += ["", ind + "switch (*(signed char *)(ctx[0] + 0x1c6)) {"]
    for c in r["cases"]:
        for k in c["ks"]:
            L.append(ind + "case %d:" % k)
        L += [ind + "    func_0203c634(self, 1, %s);" % c["handler"], ind + "    break;"]
    L.append(ind + "}")
    if guard == "beq":
        L.append("    }")
    L += ["", "    *(signed char *)(ctx[0] + 0x1c7) = -1;", "}", ""]
    return "\n".join(L)


def main():
    name = sys.argv[1]
    r = decode(name)
    if any(c["outlier"] for c in r["cases"]):
        raise SystemExit("REFUSING: %d outlier arm(s) -- this one carries extra code, "
                         "disassemble and write it by hand" % sum(c["outlier"] for c in r["cases"]))
    steps = parse_reset(r["reset"])
    print("derived reset: " + " | ".join(
        k if a is None else "%s=%s" % (k, a) for k, a in steps))
    print("case order   : " + ", ".join(str(c["ks"][0]) for c in r["cases"]))
    src = emit(name, r, steps)
    if "-w" in sys.argv:
        ov = re.match(r"func_(ov\d+)_", name).group(1)
        out = os.path.join(ROOT, "src", "overlays", ov, "calls", "%s.c" % name)
        os.makedirs(os.path.dirname(out), exist_ok=True)
        io.open(out, "w", encoding="utf-8", newline="\n").write(src)
        print("\nwrote " + out)
    else:
        print("\n" + src)


if __name__ == "__main__":
    main()
