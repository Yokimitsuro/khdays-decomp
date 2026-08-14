import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

### Second correction, and the accurate form of the rule

The two sections above landed on "integer webs and pointer webs are different
objects". Measured once more against the type of the GLOBAL rather than the
local, that is still wrong, and the real rule is simpler.

Declaring the global as `void *` or as `u8 *` -- both pointers -- moves the value
to r7 exactly as declaring it `int` does. Every type except the one that makes
the initialiser cast-free lands on r7; only the exact matching pointer type lands
on r4. So the lever is not the type at all:

> A conversion in the initialiser of a local that caches a global moves that
> local's register. `T *p = g;` and `T *p = (T *)g;` are different to the
> allocator even when `g` already has type `T *` in the first form and the cast
> is a no-op in the second.

The lever has exactly two positions, r4 without a conversion and r7 with one, so
it is a coin flip rather than a dial: useful when the target sits on one of those
two registers, useless otherwise. On func_ov002_0205bff4 the target is r8 and
neither position reaches it.

Worth stating plainly because the first two readings of this measurement were
both wrong in a way that would have sent someone down the wrong path: retyping
things at random looked productive for two rounds before the controlled version
of the experiment showed the type was never the variable.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
