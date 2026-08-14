import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## Dead stores in a local aggregate order the allocator's webs

This is the crack that closed func_ov002_0205bff4, and it retires the claim two
sections above that r8 was unreachable there. **That claim was wrong.** The
reachability sweep behind it enumerated declaration order, qualifiers, types,
struct shape, callee prototypes, control-flow shape and initialiser conversions,
and concluded from 190-odd size-correct variants that the target register could
not be produced. The sweep was sound; its axes were simply the wrong ones.

The technique. Scalarize the function's whole-function locals into one local
aggregate, and give that aggregate an extra field that is **written once and
never read**:

```c
typedef struct {
    int nFrom;
    int nTo;
    int nClass;
    int nTagOrder;      /* written once, never read */
    int bSpecialEnabled;
} Ov002PanelMoveState;
...
state.nTagOrder = 0;    /* emits nothing */
```

The store is dead and emits no instruction, but it exists when the webs are
built, and its position in the aggregate changes the order in which they are
created. On that function it moved the persistent session pointer to r8 while
leaving the parameters on r6 and r5 -- an assignment no other axis could reach.

The same trick closes branch-local cycles: a dead `pNewEntry = 0` before a
lookup, a dead `nOld = 0` before the real index calculation, and moving a flag's
initialisation to after the call it is compared against. All emit nothing.

When to reach for it: a residue that is purely register choice, where the
instruction stream already matches and every ordinary axis measures inert. That
is exactly the signature that made the earlier sweeps look conclusive, so treat
"I have enumerated everything and the target is unreachable" as a sign that the
dead-store axis has not been tried yet, not as a result.

Two supporting details from the same function. Both `#pragma opt_common_subs
off` and `#pragma opt_dead_assignments off` were load-bearing -- removing either
broke the match, and the second is what keeps the dead stores alive long enough
to matter. And an explicit `register ... asm("r7")` binding in the source was
**not** load-bearing: mwcc parses it and ignores it, so it can be dropped, which
matters because integrated C may not contain asm.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
