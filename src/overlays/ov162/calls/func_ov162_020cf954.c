/*
 * Face the target and hold a strafing heading; when the timer expires, roll the next reaction (x5).
 *
 * Re-acquire the target (020cab14); none -> state 2 and advance. Aim vector owner->target
 * (target+0x190 minus owner+0xb0), flatten Y, normalise; the gap is the magnitude minus both radii.
 * Store the heading (atan2) in state[4]. Build a facing direction from state[3] via the fixed-point
 * angle divide + the shared sin/cos table (data_0203d210), cross it with the vertical axis
 * {0, sbyte[0x5c]<<12, 0} to get a perpendicular drift, and scale that by state[0xf] into the step
 * at state+0x18. Then: if the timer state[0xd] is still positive, only bail to state 2 when the gap
 * has grown past 0x5000; otherwise reset the timer to a random span in [owner+0x224, owner+0x228]
 * and roll a d100 -- over 0x50 picks reaction 7, else 6 -- and advance.
 *
 * MATCHED. Idioms copied from the matched siblings func_ov120_020ccd90 (the divide-to-angle and
 * the owner/target-held-across-normalise scheme) and func_ov169_020cda08 (the RNG copy artifact):
 *  - owner (*state) and target (state[2]) are read into locals AFTER VEC_Subtract but BEFORE the
 *    normalise, so they live across it in callee-saved registers.
 *  - the gap sums both radii FIRST: `mag - (tgt->r + own->r)`, matching the ROM's `add; sub` rather
 *    than the two-subtract form.
 *  - the angle index is the reciprocal-multiply divide of state[3] (0x28be60db9391), exactly the
 *    form proven in func_ov120_020ccd90.
 *  - the second RandNextScaled needs its result copied before the compare (ROM `add r0,r0,#0`);
 *    spelled `+ (span - span)` with span live across the call, per func_ov169_020cda08. The first
 *    call is consumed directly by an add and needs no copy.
 *  - the grown-gap bail is `if (gap < 0x5000) return;` so the state-2 block is the out-of-line arm,
 *    matching the ROM's `cmp; addlt/ldmialt` inline early return.
 *  - ★ own/tgt must be scoped in a NESTED BLOCK (own declared first, sum `tgt->r + own->r`), copied
 *    from the matched sibling func_ov131_020cd334. With them as function-level locals mwcc puts
 *    state[2] in r5 and *state in r7; the ROM wants the reverse, and NO function-level form flips
 *    it (sum order, assignment order, declaration order, compound-assign -- all leave a 2-byte
 *    pre-load swap). Block-scoping the two pointers is the only thing that reassigns them.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *d);
extern void func_01ffa724(int s, void *v, void *d);
extern int func_02023eb4();
extern short data_0203d210[];

void func_ov162_020cf954(int *self) {
    int *state = (int *)self[1];
    struct Vecx32 aim;
    struct Vecx32 dir;
    struct Vecx32 axis;
    int gap;
    int idx;
    int span;

    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[2] + 0x190), (void *)(*state + 0xb0), &aim);
    aim.y = 0;
    {
        int *o = (int *)*state;
        int *h = (int *)state[2];
        gap = func_01ff8d18(&aim, &aim) -
              (*(int *)((char *)h + 0x80) + *(int *)((char *)o + 0x80));
    }
    state[4] = func_020050b4(aim.x, aim.z);

    axis.y = (int)*(signed char *)((int)state + 0x5c) << 12;
    axis.x = 0;
    axis.z = 0;
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[3] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    dir.y = 0;
    dir.x = (int)data_0203d210[idx * 2];
    dir.z = (int)data_0203d210[idx * 2 + 1];
    VEC_CrossProduct(&dir, &axis, &dir);
    func_01ffa724(state[0xf], &dir, (void *)(state + 6));

    if (state[0xd] <= 0) {
        int lo = *(int *)(*state + 0x224);
        span = *(int *)(*state + 0x228) - lo;
        if (span < 0) {
            span = -span;
        }
        state[0xd] = lo + func_02023eb4(span + 1);
        if (func_02023eb4(0x65) + (span - span) <= 0x50) {
            *(char *)(*state + 0x1c7) = 6;
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 7;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }

    if (gap < 0x5000) {
        return;
    }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
