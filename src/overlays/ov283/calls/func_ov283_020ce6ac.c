/* Reset the state's timer at +0x50 and pick the next sub-state for the owner: a 30%-or-less
 * roll (0..100) picks action 10, otherwise action 7, written to the owner's action byte at
 * +0x1c7.
 *
 * The roll goes through the inlined RandRange(lo, hi) wrapper that ov114's callers spell out
 * by hand (`lo + func_02023eb4(|hi - lo| + 1)`). With lo == 0 the inliner leaves `0 + roll`
 * behind, which is the ROM's bare `add r0, r0, #0` between the call and the compare. */
extern unsigned int func_02023eb4(unsigned int range);

static inline int RandRange(int lo, int hi)
{
    int span = hi - lo;

    if (span < 0)
        span = -span;
    return lo + func_02023eb4(span + 1);
}

void func_ov283_020ce6ac(int *node)
{
    int *state = (int *)node[1];

    *(int *)((char *)state + 0x50) = 0;
    *(char *)(*state + 0x1c7) = (RandRange(0, 100) > 30) ? 7 : 10;
}
