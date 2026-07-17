/*
 * Steer toward the target and hand off to the terrain/collision follow-up (x5).
 *
 * Re-acquire the target (020cab14); none -> state 2 and advance. Aim vector target->owner --
 * note the direction: it is the target position (target+0x190) minus the owner (*state+0xb0),
 * then NEGATED component-wise (x and z) and flattened (y=0), i.e. owner->target after the negate.
 * Normalise for the distance, store the heading (atan2) in state[0x13]. Turn the node's own
 * heading (state[0x11]) into a sin/cos direction, DOT it with the aim (result discarded here --
 * the ROM keeps the call), and scale that direction by the owner's speed field (*state+0x430)
 * into the step at state+0x20. Finally 020d0d28(self, dist) decides whether to advance.
 *
 * ★ CONFIRMS THE SDK-VEIN PATTERN (see the parked ov214/ov162/ov142 write-ups): this is the same
 * VEC_Set sin/cos construct that hit a scheduling tie in ov214 -- but here the direction vector
 * is a STACK local (`dir`, sp+0), not persistent memory, so mwcc hoists the cos load freely and
 * it matches. Big members with real control flow and stack vectors match; small straight-line
 * ones writing to heap tie. Matched at exact size on the first compile; only the frame layout and
 * one statement order needed adjusting.
 *
 * The adjustments, all catalogued:
 *  - `aim` before `dir` in declaration order so the frame is aim=sp+0xc, dir=sp+0 (the LAST
 *    declared vector gets the lowest slot -- the ov188 rule).
 *  - the flatten `aim.y = 0` is written BETWEEN the two negations (`aim.x=-aim.x; aim.y=0;
 *    aim.z=-aim.z;`), which is where the ROM schedules the `mov r3,#0`; written after both, the
 *    zero and the -z swap registers.
 *  - 020d0d28 takes TWO args (self, dist) -- Ghidra shows one; the ROM passes dist in r1 (the
 *    normalise result held in r4 across the whole body).
 *  - VEC_DotProduct's result is discarded, but mwcc keeps the call (it cannot prove it pure), so
 *    it is written as a bare statement.
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
extern int VEC_DotProduct(void *a, void *b);
extern void func_01ffa724(int s, void *v, void *d);
extern int func_ov217_020d0d38(int *self, int dist);
extern short data_0203d210[];

void func_ov217_020d14f8(int *self) {
    int *state = (int *)self[1];
    struct Vecx32 aim;
    struct Vecx32 dir;
    int target;
    int dist;
    int idx;

    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), &aim);
    aim.x = -aim.x;
    aim.y = 0;
    aim.z = -aim.z;
    dist = func_01ff8d18(&aim, &aim);
    state[0x13] = func_020050b4(aim.x, aim.z);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[0x11] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    VEC_Set(&dir, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    VEC_DotProduct(&dir, &aim);
    func_01ffa724(*(int *)(*state + 0x430), &dir, (void *)(state + 8));
    if (func_ov217_020d0d38(self, dist) != 0) {
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
