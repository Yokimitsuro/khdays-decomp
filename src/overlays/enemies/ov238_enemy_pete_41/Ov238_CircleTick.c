/* Circling tick of the ov238 enemy: the +0x2c clock runs up at the owner's rate; before 0.83 the
 * target is the owner's partner's (+0x398) +0x3e4 actor, afterwards it is acquired (020cab14) into
 * +0x18 -- none requests sub-state 3. The unit direction from the +8 position to the target's +0x190
 * point goes to +0x40; the first time (+0x3c clear) the +0x24/+0x28 yaws take its heading and +0x40
 * turns 1.57 around. The +0x24 yaw then sweeps with the clock (x 1.57 / 0.166) and the overlay's
 * offset, turned by the +0x28 yaw, becomes the +0xc step. Within 1.0 of the target, on landing
 * (+0x17a bit 1) or after 1.5 the tick requests sub-state 3; otherwise +0x3c is latched unless the
 * target is still more than 1.5 away and at most 0.5 above the +8 position. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } Mtx33;
struct b2 { unsigned char b0 : 1, b1 : 1; };

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(VecFx32 *v, Mtx33 *m, VecFx32 *d);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const VecFx32 data_ov238_020d36e4;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov238_CircleTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 offset = data_ov238_020d36e4;
    Mtx33 mtx;
    int dist;
    unsigned int idx;

    state[0xb] += *(int *)(node[0] + 0x2c);
    if (state[0xb] < 0xd48) {
        state[6] = *(int *)(*(int *)(*state + 0x398) + 0x3e4);
    } else {
        state[6] = Ov107_FindNearestObject(*state, 0);
    }
    if (state[6] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 3;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[6] + 0x190), (void *)state[2], (VecFx32 *)(state + 0x10));
    dist = VEC_Normalize((VecFx32 *)(state + 0x10), (VecFx32 *)(state + 0x10));
    if (state[0xf] == 0) {
        state[10] = state[9] = FX_Atan2(state[0x10], state[0x12]);
        state[9] += 0x1922;
        idx = ANG2IDX(state[9]);
        state[0x10] = data_0203d210[idx * 2];
        state[0x11] = 0;
        state[0x12] = data_0203d210[idx * 2 + 1];
        VEC_Normalize((VecFx32 *)(state + 0x10), (VecFx32 *)(state + 0x10));
    }
    state[9] = state[0xb] * 0x1922 / 0x2a8;
    idx = ANG2IDX(state[10]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33(&offset, &mtx, (VecFx32 *)(state + 3));
    if (dist < 0x1000 || ((struct b2 *)(*state + 0x17a))->b1 != 0 || state[0xb] >= 0x1800) {
        *(unsigned char *)(*state + 0x1c7) = 3;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist >= 0x1800 && *(int *)(state[6] + 0x194) - *(int *)(state[2] + 4) <= 0x800) {
        return;
    }
    state[0xf] = 1;
}
