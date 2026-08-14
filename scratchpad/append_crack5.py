import io

P = ".claude/skills/khdays-decomp/references/codegen-cracks.md"
TEXT = u"""

## The TYPE of a whole-function value decides its register

Measured on func_ov002_0205bff4 after every structural axis had been exhausted.
A global struct pointer held in a local sits in r4. Hold the *same value* as an
integer instead, casting at each use, and it moves to r7 -- with byte-identical
size, because the casts cost nothing.

```c
Ov002PanelSession *s = g;        /* the value lands in r4 */
int s = (int)g;                  /* the same value lands in r7 */
...((Ov002PanelSession *)s)->field...
```

So an integer web and a pointer web are different objects to mwcc's allocator,
even when they hold the same bits and generate the same instructions. int,
unsigned int, long and unsigned long all behave alike; a union of pointer and
integer behaves as the pointer.

This is worth trying early on any residue that is purely a register choice for a
long-lived value, because it is one of the very few levers that moves the
assignment without changing a single emitted instruction. Everything else that
moves it -- pragmas that disable common-subexpression elimination or copy
propagation, a second load of the global -- either changes the code or is not
plausible as original source.

Its reach is limited, though, so do not expect it to solve a residue on its own.
Crossed with declaration position, index order and a const global (48 variants),
the value reached r4, r6 and r7 but never r8, which is where that particular
function's ROM keeps it.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
