/*
 * func_ov214_020ce928 -- UNFINISHED. 244/244 bytes, 61/61 instructions.
 * x5 family (worth 5). Semantically complete; the shape is exact bar ONE reordered load.
 *
 * WHAT IT DOES: aim from the owner (*state+0x190) to a cached point (state[4]); store the heading
 * (atan2 of the UNFLATTENED x,z) in state[0x13]; normalise the aim for the distance and subtract
 * the owner radius (owner+0x80). Turn the node's own heading (state[0x11]) into a sin/cos pair,
 * write it as a vector at state+0x20 (VEC_Set), scale it by 0x200 (the per-frame step), and if the
 * distance is under 0x2000 drop to state 2. Note it does NOT flatten y before atan2 -- unlike its
 * ov188 cousin.
 *
 * Matched to the byte on the FIRST compile except for the VEC_Set schedule. Two things got it
 * that far, both worth keeping:
 *  - `int owner = *state;` extracted as a local, computed BEFORE the normalise call, so the owner
 *    pointer is live in a register across it (ROM `ldr r5,[r4]` before the bl). Used for the
 *    radius only -- the state-2 path re-reads `*state` (ROM `ldr r0,[r4]` again), so owner must
 *    NOT be reused there or it saves an instruction (240 B).
 *  - the distance subtraction `dist - owner+0x80` interleaves into the Q12 sin/cos conversion in
 *    the ROM; the statement order does not control that (mwcc schedules it), but the `owner`
 *    local is what makes the interleave legal.
 *
 * THE GAP: the VEC_Set at state+0x20 loads cos BEFORE storing sin; mwcc stores sin first, then
 * loads cos.
 *      ROM:   ldrsh r7(sin) ; ldrsh r3(cos) ; mov ip,#0 ; str r7 ; str ip ; ... str cos
 *      mine:  ldrsh r7(sin) ; mov ip,#0 ; str r7 ; ... ldrsh r3(cos) ; str cos
 * ★ WHY, and it is the useful finding: this is the SAME VEC_Set that matched byte-exact in
 * func_ov188_020cf344 -- but THERE the destination vector was on the STACK (&v, sp+0), and HERE
 * it is in persistent memory (state+0x20). mwcc will hoist the cos load above a store to the
 * stack (no aliasing possible with the global sin/cos table), but NOT above a store through a
 * heap pointer, because it cannot prove state+0x20 and data_0203d210 do not overlap. So the exact
 * same source construct schedules differently by destination class. Confirmed: VEC_Set inline,
 * open-coded `state[8]=..`, and precomputed sin/cos temps all produce the identical diff.
 *
 * ★ PATTERN for the SDK vein (three parked this session): the BIG members with real control flow
 * (ov188/ov202/ov239, branches and dispatch) matched, because the branches absorb the schedule;
 * the SMALL straight-line ones (ov162, ov142, this) hit a register/schedule tie at near-exact
 * size. When triaging the vein, prefer the ones with a switch or multiple exits.
 *
 * NEXT STEP: find a source form that lets mwcc treat state+0x20 as non-aliasing with the table
 * (a local VecFx32 built then block-copied would, but changes the instruction count). Belongs
 * with the scheduling/aliasing residue class. Worth 5.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int s, void *v, void *d);
extern void func_0203c634(int self, int idx, int cb);
extern short data_0203d210[];

void func_ov214_020ce928(int self) {
    int *state = *(int **)(self + 4);
    struct Vecx32 aim;
    int dist;
    int idx;
    int owner;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[4], &aim);
    state[0x13] = func_020050b4(aim.x, aim.z);
    owner = *state;
    dist = func_01ff8d18(&aim, &aim);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[0x11] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    dist = dist - *(int *)(owner + 0x80);
    VEC_Set((struct Vecx32 *)(state + 8), (int)data_0203d210[idx * 2], 0,
            (int)data_0203d210[idx * 2 + 1]);
    func_01ffa724(0x200, (void *)(state + 8), (void *)(state + 8));
    if (dist < 0x2000) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}
