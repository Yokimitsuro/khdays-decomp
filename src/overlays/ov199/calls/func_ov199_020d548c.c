/*
 * Face the target and drop to idle when close enough (x4).
 *
 * Aim vector owner->target, hand it to BuildHeadingRotation (020d0764) to point the node at the
 * target, then normalise the aim for the distance: if the distance minus the owner radius
 * (owner+0x80) is under 0x2000, the target is in reach -> state 2 and advance.
 *
 * MATCHED. Two catalogued spellings, both about how a vector crosses the ABI:
 *  - ★ `ldm`-ARG COALESCING: the aim vector is passed to BuildHeadingRotation as a STRUCT BY VALUE
 *    (`struct Vec3` -> three register args), which makes mwcc load the three words with a single
 *    `ldm` -- exactly the ROM's `ldm r1,{r1,r2,r3}`. Passing them as three separate `int` args
 *    (`f(state, aim[0], aim[1], aim[2], 0)`) emits three `ldr`s instead and is one instruction
 *    off. This is the deferred-ties "ldm-args coalescing" entry, and struct-by-value is the crack
 *    for it -- the callee still receives three register args, same ABI.
 *  - `owner = *state` is loaded BEFORE the normalise call, so it survives in a callee-saved
 *    register (r6, hence `push {r4,r5,r6,lr}`), and the state-2 store RE-READS *state fresh. Read
 *    after the call instead, mwcc keeps one copy and drops the reload (128 B) -- but the ROM
 *    holds owner across the call and re-reads, so the C must too.
 */
struct Vec3 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern void func_ov199_020d43a4(int *state, struct Vec3 v, int flag);
extern int func_01ff8d18(void *a, void *d);
extern void func_0203c634(int self, int idx, int cb);

void func_ov199_020d548c(int self) {
    int *state = *(int **)(self + 4);
    struct Vec3 aim;
    int dist;
    int owner;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[3], &aim);
    func_ov199_020d43a4(state, aim, 0);
    owner = *state;
    dist = func_01ff8d18(&aim, &aim);
    if (dist - *(int *)(owner + 0x80) < 0x2000) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}
