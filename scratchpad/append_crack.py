import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## The callee-saved assignment rule, measured directly

Measured on synthetic probes rather than inferred from a residue, so it is
reusable. Compile a function with N long-lived locals each defined by its own
call, then vary how often each is referenced.

The result: mwcc assigns callee-saved registers **descending from the top of the
range it decides to use, in order of first definition**. Reference counts are
irrelevant. A probe whose four locals are referenced 8, 4, 2 and 1 times and a
probe whose four locals are referenced 1, 2, 4 and 8 times produce the *same*
mapping, first-defined to r7 and last-defined to r4. Parameters take part in the
same sequence ahead of the locals.

This matters because it kills a whole class of hypothesis on sight. When a
residue is a register permutation, do not go looking for a variable that is
"used more" in the original, and do not reorder declarations hoping to reorder
registers: neither input feeds the decision. The declaration-order lever works
only when it changes the order of first *definition* in the emitted code.

The rule above describes straight-line code. Once values are defined inside
branches the assignment stops being a simple sequence, because the allocator is
colouring an interference graph: the highest-degree node, typically a pointer
live across the whole function, is coloured **last** and therefore receives
whatever colour is left over rather than the first one. A residue in which a
long-lived pointer sits in the lowest register in your build and a high one in
the ROM is therefore evidence that your IR has *fewer or smaller webs*, so the
pointer's node is no longer the highest-degree one. Attack the web structure,
not the pointer.

## Declare the second index first when two indices share a case

A case that computes two parallel indices from the same parts, the classic

```c
int nOld = nFrom + nColumn * 6;
int nNew = nTo + nColumn * 6;
```

is emitted with the two values in adjacent callee-saved registers, and which one
lands in the lower register follows the order of the *declarations*, not the
order of use. When the ROM puts the second index in the lower register, swap the
declarations. The emitted instructions are identical either way, so this costs
nothing and is worth trying before any deeper hypothesis. Measured on
func_ov002_0205bff4, where it moved the residue from 69 bytes to 67 and brought
the second index onto the ROM's register.

Note the asymmetry with the previous section: this lever works precisely because
swapping the declarations also swaps the order of first definition. Reordering
declarations whose initialisers are evaluated in a fixed order does nothing.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
