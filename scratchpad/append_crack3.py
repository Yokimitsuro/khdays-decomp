import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## Calls with stack arguments are a register-allocation lever

A call with more than four arguments spills the rest to the outgoing argument
area, which forces a `sub sp` reservation and `stm sp` / `str [sp,#N]` stores.
That is not just extra instructions: it changes which register the allocator
gives to a whole-function pointer.

Measured on the reproduction for func_ov002_0205bff4. Before adding
eight-argument calls, 313 configurations across every structural axis tried --
declaration order, struct shape, branch-local counts, inlining, control-flow
shape, register demand from four to nine pushed registers -- all put the
long-lived pointer in r4 and none could move it. Adding a single eight-argument
call moved it to r6 or r7 in 24 of 36 configurations.

So when a residue is a register permutation and the function makes calls with
more than four arguments, treat those calls as part of the allocation problem.
Do not model them as ordinary calls that merely cost a few stores.

The lever came with a coupling worth knowing about. In that reproduction the
pointer's register and the parameter registers flipped together and could not be
set independently: the configurations with the parameters in the expected place
kept the pointer in r4, and the configurations that moved the pointer put the
parameters elsewhere. When two properties move together like that, stop scaling
the knob by eye and go count the exact number of values live *across* the call
in the target, then reproduce that count rather than the instruction sequence.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
