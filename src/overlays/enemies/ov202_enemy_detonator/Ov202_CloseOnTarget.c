/*
 * Close on the target, steering the step by how well it is already aimed (x2: ov202/ov203).
 *
 * The ov188 shape with one idea added. Re-acquire the target (020cab14); none -> state 2 and
 * advance. Take the owner->target vector (target+0x190 minus owner+0xb0), FLATTEN it (y = 0),
 * normalise for the distance, and store the heading (atan2) in state[3]. The gap is that distance
 * minus BOTH radii together -- `len - (target[0x80] + owner[0x80])`, parenthesised, which is what
 * the ROM's `add r2,r3,r2 ; sub r5,r0,r2` says and not the `(len - a) - b` of its ov188 sibling.
 *
 * The step is where it differs: the node's own heading becomes a sin/cos direction, and that
 * direction is DOTTED with the (normalised) aim vector. The absolute value of that dot -- 0x1000
 * when already facing the target, 0 when perpendicular -- scales the step via FX_Mul(dot, 0x300).
 * So it accelerates as it lines up. Then: gap at or past the owner's reach (owner+0x2d8) -> give
 * up (state 2); inside 0x1000 -> fire attack 9 (020c9264) and advance WITH a callback
 * (020cd4a0); otherwise keep closing.
 *
 * MATCHED ON THE FIRST COMPILE, and that is the point worth recording: nothing here was
 * discovered. The VEC_Set fingerprint sweep found it, and every piece was a lookup --
 *  - VEC_Set(&v, sin, 0, cos) for the direction (the fingerprint itself);
 *  - the Q12 radians->sin/cos conversion, catalogued, verbatim;
 *  - FX_Mul as the SDK inline: `((s64)v1 * v2 + 0x800) >> 12` is exactly the ROM's
 *    umull/mla/adds #0x800/lsr #12/orr chain;
 *  - `gap > 0x1000`, NOT Ghidra's `gap < 0x1001` -- 0x1001 is not an ARM immediate and would
 *    have come out of the pool (catalogued two commits ago, and it has now bitten in three
 *    consecutive functions);
 *  - `d` declared before `v` so the frame lays out sp+0xc / sp+0 as the ROM has it.
 * The relocs even carry VEC_Subtract and VEC_DotProduct by name -- the index knew what these
 * were all along.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

static inline void VEC_Set(VecFx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline int FX_Mul(int v1, int v2) {
    return (int)(((long long)v1 * v2 + 0x800LL) >> 12);
}

extern int Ov107_FindNearestObject(int a, int b);
extern void SetIndexedSlot(int self, int idx, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int VEC_Normalize(void *a, void *d);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(void *a, void *b);
extern void ScaleVec3Fx12(int s, void *v, void *d);
extern void Ov202_AdvanceNodeWhenGateClear(void);
extern short data_0203d210[];

void Ov202_CloseOnTarget(int self) {
    int *state = *(int **)(self + 4);
    VecFx32 d;
    VecFx32 v;
    int owner;
    int target;
    int len;
    int gap;
    int idx;
    int dot;

    state[1] = Ov107_FindNearestObject(*state, 0);
    if (state[1] == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x190), (void *)(*state + 0xb0), &d);
    d.y = 0;
    owner = state[0];
    target = state[1];
    len = VEC_Normalize(&d, &d);
    gap = len - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    state[3] = FX_Atan2(d.x, d.z);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[2] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    VEC_Set(&v, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    dot = VEC_DotProduct(&v, &d);
    if (dot < 0) { dot = -dot; }
    ScaleVec3Fx12(FX_Mul(dot, 0x300), &v, (void *)(state + 5));
    if (gap >= *(int *)(*state + 0x2d8)) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (gap > 0x1000) { return; }
    Ov107_PostTagUpdate((Actor *)(*state), 9, 0);
    SetIndexedSlot(self, *(signed char *)(self + 0x20), Ov202_AdvanceNodeWhenGateClear);
}
