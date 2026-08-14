import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## The assignment pattern flips at a callee-saved demand threshold

Measured on a synthetic reproduction, so it generalises. Take a function with two
int parameters, a global struct pointer live across the whole body, a classifier
call whose result drives a switch, and branch-local temporaries. Then scale how
many temporaries are live at the same time inside one case, which is what sets
the number of callee-saved registers the function needs.

Below the threshold -- four callee-saved registers or fewer -- the classifier
result takes **r4** and the long-lived pointer sits **above** it. From five
registers up the assignment **inverts**: the pointer drops to r4 and the
classifier moves up. The transition sits between two and three simultaneously
live temporaries in a case.

Two consequences worth carrying into other functions.

First, when a residue is a register permutation involving a whole-function
pointer, check which side of that threshold the function sits on before forming
any hypothesis. The intuition built on small functions -- "the long-lived value
gets a high register" -- is exactly backwards above the threshold.

Second, this is a property of the whole function, not of the statement you are
editing. Rewriting the case that holds the residue will not move it. Only
something that changes the peak number of simultaneously live values can, and if
the emitted instructions are fixed, that peak is fixed too.

Measured negative worth recording so it is not repeated: at seven to nine pushed
registers, thirty-two configurations combining five independent axes -- the
number of wide temporaries, whether the pointer is used inside the wide case,
whether the classifier survives calls before the dispatch, whether a branch-local
value is present, and where the wide case sits -- all produced the same
assignment. Above the threshold the structure of the branches does not move the
whole-function set at all.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
