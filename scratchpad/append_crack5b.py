import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

### Correction to the entry above: the lever is narrower than stated

The section above says the type of a whole-function value decides its register.
Measured more carefully straight afterwards, that is too broad. Retyping the
**classifier result** -- an ordinary int local defined by a call return -- from
int to a pointer changes nothing at all: the assignment stays exactly where it
was, in all four crossings of the two types.

Only the value **loaded from the global** responds. So the rule to carry forward
is narrower and more specific:

> Retyping a local that holds a value loaded from a global pointer changes which
> register it gets. Retyping a local that holds a call's return value does not.

That asymmetry is itself a clue about where the distinction lives: it is tied to
how the load is typed, not to the storage class or lifetime of the local. Try it
on residues involving a cached global; do not bother on residues involving a
call result.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
