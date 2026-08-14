import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## Refinement: the top of the callee-saved range moves with demand

The earlier entry above says mwcc hands out callee-saved registers descending by
order of first definition. That is right, but it omits the part that makes the
rule usable: **the register it descends from is not fixed**. It is the top of the
range the function will end up needing, so adding one more long-lived value
shifts every earlier assignment up by one.

Measured on 24 synthetic probes varying the parameter count from one to four and
the long-lived local count from one to three, with and without an eight-argument
call:

- two parameters, one local: the function uses r4-r7, and gets p0=r7, p1=r6,
  pointer=r5;
- two parameters, two locals: it uses r4-r8, and gets p0=r8, p1=r7, pointer=r6;
- three parameters, one local: r4-r8, and p0=r8, p1=r7, p2=r6, pointer=r5.

So a residue where every register is "one off" is not a permutation to chase
value by value. It means your function needs a different number of callee-saved
registers than the target, or the compiler thinks it does. Count the pushed
registers first: if they match, the demand matches and the residue is elsewhere;
if the whole assignment is shifted, look for the missing or extra long-lived
value rather than rewriting the body.

The rule holds for values live across the whole function. Once branch-local
temporaries enter, they take the top of the range and the whole-function values
descend from below them, so read the two groups separately before concluding
anything.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
