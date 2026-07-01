#!/usr/bin/env python3
"""Rewrite `asm void` blocks whose ARM code is written as `dcd 0xNNNNNNNN`.

mwccarm places a `$d` (data) mapping symbol at the start of any block
that begins with `dcd`. mwld then treats the whole block as data. When
a caller resolves an extern in that block across an ARM/THUMB boundary
mwld inserts an interworking veneer (shifting bytes), and when the same
BL from a THUMB caller lands in an "unknown-mode" block, mwld picks BL
instead of BLX and skips the mode switch entirely — both breaking
byte-exactness.

Rewriting each `dcd 0xNNNNNNNN` line whose value decodes to a valid ARM
instruction as the actual mnemonic puts `$a` at 0 and `$d` only where
real data (typically the trailing pointer table) begins, matching the
delink baseline.

Uses capstone to check that a word actually disassembles to something.
"""
import re
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

ROOT = Path(__file__).resolve().parents[1]

MD_ARM = Cs(CS_ARCH_ARM, CS_MODE_ARM)

DCD_HEX = re.compile(r"^(?P<indent>\s+)dcd\s+0x(?P<hex>[0-9a-fA-F]{8})\s*$")

# mwccarm's inline assembler doesn't accept every mnemonic capstone emits;
# in particular `push`/`pop` are Thumb-only in the assembler, while ARM
# code must use `stmdb`/`ldmia`. Restrict rewrites to mnemonics the
# assembler is known to accept; anything else stays as `dcd`.
SAFE_MNEMONICS = {
    "mov", "movs", "mvn", "mvns",
    "add", "adds", "sub", "subs", "rsb", "rsbs", "adc", "adcs", "sbc", "sbcs",
    "and", "ands", "orr", "orrs", "eor", "eors", "bic", "bics",
    "cmp", "cmn", "tst", "teq",
    "ldr", "ldrb", "ldrh", "ldrsb", "ldrsh",
    "str", "strb", "strh",
    # Register-only bx/blx are safe; the immediate forms would need a label
    # that we can't reconstruct from a raw address, so leave those as dcd.
    "bx",
    "mul", "muls", "mla", "mlas", "umull", "smull", "umlal", "smlal",
    "clz", "swp",
    "mrs", "msr",
    # Multiple load/store — capstone emits these instead of push/pop.
    "stmdb", "ldmia", "stm", "ldm", "stmda", "ldmda", "stmib", "ldmib",
}

# capstone emits `lsl r0, r1, #2` for what mwccarm wants written as
# `mov r0, r1, lsl #2`. Same for lsr/asr/ror/rrx.
_SHIFT_RE = re.compile(
    r"^(?P<sh>lsl|lsr|asr|ror|rrx)(?P<cc>[a-z]{0,2})\s+"
    r"(?P<dst>\S+),\s*(?P<src>\S+),\s*(?P<amt>.+)$"
)


def rewrite_shift(mnem_and_op):
    m = _SHIFT_RE.match(mnem_and_op)
    if not m:
        return mnem_and_op
    return f"mov{m.group('cc')} {m.group('dst')}, {m.group('src')}, {m.group('sh')} {m.group('amt')}"


# capstone emits `bl #0xADDR` / `b #0xADDR` for immediate branches. mwccarm
# needs a label; leaving these as dcd keeps the code valid but loses one
# rewrite opportunity — acceptable trade-off.
_IMM_BRANCH_RE = re.compile(r"^(b|bl|blx)(?:[a-z]{0,2})\s+#0x")


PUSH_POP_RE = re.compile(r"^(?P<mnem>push|pop)(?P<cc>[a-z]{0,2})\s+(?P<regs>\{[^}]*\})$")


def rewrite_push_pop(mnem_and_op):
    """Convert `push {..}` / `pop {..}` to the ARM stmdb/ldmia form
    mwccarm accepts."""
    m = PUSH_POP_RE.match(mnem_and_op)
    if not m:
        return mnem_and_op
    cc = m.group("cc") or ""
    regs = m.group("regs")
    if m.group("mnem") == "push":
        return f"stmdb{cc} sp!, {regs}"
    return f"ldmia{cc} sp!, {regs}"


_LDM_STM_RE = re.compile(r"^(ldm|stm)(?P<cc>[a-z]{0,2})\s")


def rewrite_ldm_stm(mnem_and_op):
    """Convert `ldm`/`stm` (default IA) to explicit `ldmia`/`stmia`."""
    m = _LDM_STM_RE.match(mnem_and_op)
    if not m:
        return mnem_and_op
    rest = mnem_and_op[len(m.group(0)) - 1:]  # keep the trailing space
    return f"{m.group(1)}ia{m.group('cc')}{rest}"


def convert_regs(op_str):
    """mwccarm's assembler doesn't recognize APCS register aliases like
    `sb`/`sl`/`fp` (r9/r10/r11) and dislikes `r13/r14/r15`. Rewrite the
    aliases to the numeric forms it accepts."""
    result = op_str
    # Numbers first so we don't accidentally rewrite r9 -> sb -> ...
    result = re.sub(r"\br13\b", "sp", result)
    result = re.sub(r"\br14\b", "lr", result)
    result = re.sub(r"\br15\b", "pc", result)
    result = re.sub(r"\bsb\b", "r9", result)
    result = re.sub(r"\bsl\b", "r10", result)
    result = re.sub(r"\bfp\b", "r11", result)
    return result


def disassemble_word(val):
    """Return an ARM mnemonic string mwccarm will accept, or None if
    the word isn't a known mnemonic or isn't in the safe list."""
    b = val.to_bytes(4, "little")
    for i in MD_ARM.disasm(b, 0):
        mnem = i.mnemonic
        if not mnem or mnem.startswith("."):
            return None
        # Convert capstone-style `push`/`pop` -> `stmdb`/`ldmia`; barrel
        # shifts to `mov` with shifter operand; bare `ldm`/`stm` to the
        # explicit IA direction mwccarm expects.
        candidate = f"{mnem} {i.op_str}".strip()
        candidate = rewrite_push_pop(candidate)
        candidate = rewrite_shift(candidate)
        candidate = rewrite_ldm_stm(candidate)
        if _IMM_BRANCH_RE.match(candidate):
            return None
        # capstone sometimes emits `#N, #M` rotated-immediate operands
        # (e.g. `andeq r4, sp, #72, #14`) that mwccarm rejects. Leave as dcd.
        if re.search(r"#-?\d+,\s*#-?\d+", candidate):
            return None
        mnem2 = candidate.split(" ", 1)[0]
        base = mnem2
        # Strip a trailing condition code so the safelist can match. Skip
        # compound mnemonics (`ldrb`, `ldrh`, `strb`, `strh`, `ldrsb`,
        # `ldrsh`) because mwccarm wants `ldreqh` not `ldrheq` — writing
        # the general reordering is fiddly, and `dcd` is a safe fallback.
        cc = None
        for suffix in ("eq", "ne", "cs", "hs", "cc", "lo", "mi", "pl",
                       "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "al"):
            if base.endswith(suffix) and len(base) > len(suffix):
                base = base[:-len(suffix)]
                cc = suffix
                break
        if cc and base in ("ldrb", "ldrh", "strb", "strh", "ldrsb", "ldrsh"):
            return None
        # mwccarm rejects `mvnseq`-style ordering (condition after the
        # S flag). Skip S-form mnemonics carrying a condition suffix.
        if cc and base in ("movs", "mvns", "adds", "subs", "ands", "orrs",
                           "eors", "bics", "adcs", "sbcs", "rsbs",
                           "muls", "mlas"):
            return None
        # Same for block-transfer mnemonics: mwccarm wants `ldmeqia`, not
        # `ldmiaeq`.
        if cc and base in ("ldmia", "stmdb", "ldm", "stm",
                           "ldmda", "stmda", "ldmib", "stmib"):
            return None
        if base not in SAFE_MNEMONICS:
            return None
        # Reassemble with capstone's op_str hygiene.
        return f"{mnem2} {convert_regs(candidate.split(' ', 1)[1] if ' ' in candidate else '')}".rstrip()
    return None


def rewrite(text):
    lines = text.splitlines(keepends=True)
    out = []
    changed = False
    # Only rewrite dcd lines that appear inside an `asm void` block.
    # The block may be `asm void NAME(void) {` on one line, or `asm void
    # NAME(void)` followed by a `{` on the next line.
    in_asm = False
    pending_asm = False
    for line in lines:
        stripped = line.strip()
        if stripped.startswith("asm ") and "(" in stripped:
            if stripped.endswith("{"):
                in_asm = True
            else:
                pending_asm = True
        elif pending_asm and stripped == "{":
            in_asm = True
            pending_asm = False
        elif in_asm and stripped == "}":
            in_asm = False
        m = DCD_HEX.match(line.rstrip("\n"))
        if in_asm and m:
            val = int(m.group("hex"), 16)
            mnem = disassemble_word(val)
            if mnem is not None:
                out.append(f"{m.group('indent')}{mnem}\n")
                changed = True
                continue
        out.append(line)
    return "".join(out), changed


def load_file_modes():
    p = ROOT / "build" / "file_modes.json"
    if not p.exists():
        return {}
    import json
    return json.loads(p.read_text(encoding="utf-8"))


def main():
    modes = load_file_modes()
    fixed = 0
    for c_file in list((ROOT / "libs").rglob("*.c")) + list((ROOT / "src").rglob("*.c")):
        # Thumb files often have a literal pool of `dcd` after the function
        # body; rewriting those as ARM `andeq` etc. would produce THUMB
        # compile errors. Skip.
        rel = c_file.resolve().relative_to(ROOT).as_posix()
        if modes.get(rel) == "thumb":
            continue
        text = c_file.read_text(encoding="utf-8", errors="replace")
        new_text, changed = rewrite(text)
        if changed:
            c_file.write_text(new_text, encoding="utf-8", newline="\n")
            fixed += 1
    print(f"rewrote {fixed} files (skipped thumb files)")


if __name__ == "__main__":
    main()
