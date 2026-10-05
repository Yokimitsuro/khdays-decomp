/* Flight tick of the ov218 enemy (the ov220 d2c0c flight with its state one word further): the +0x28
 * velocity starts as (speed +0x58 times the sine of the +0x50 phase, 0, 1.0), mirrored on x by
 * +0x5c, turned by the +0x4c yaw, normalised and scaled by +0x1c plus 0x300 plus a bob taken from the
 * sine of the phase (0x600 / 2, folded to fixed point). A wall contact (bit 1 of the actor's +0x17a)
 * reflects the facing of the +0xc yaw about the +0x114 contact normal: the reflected direction gives
 * the new +0x4c yaw and redirects the velocity at its current length, and +0x60 latches. A negative
 * distance to the target ends the state, a finished idle countdown (020cc7f8) just returns; otherwise
 * the +0xc/+0x10 yaws follow the velocity and the phase advances by the +0x54 rate, handing off to the
 * circle state (and running it) once it reaches 0x8000. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char bit0 : 1, bit1 : 1; };

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const VecFx32 *v, Mtx33 *m, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern int VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern int Ov218_DistanceToTarget(int *node);
extern int Ov218_WalkDecide(int *node, int dist);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov218_CircleTick(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov218_FlightTick(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    VecFx32 n;
    VecFx32 back;
    VecFx32 refl;
    int bob;
    int dist;
    int len;
    unsigned int idx;

    state[0xa] = state[0x16] * data_0203d210[(state[0x14] >> 4) * 2] / 0x1000;
    state[0xb] = 0;
    state[0xc] = 0x1000;
    if (*(unsigned char *)(state + 0x17) != 0) {
        state[0xa] *= -1;
    }
    idx = ANG2IDX(state[0x13]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((VecFx32 *)(state + 0xa), &mtx, (VecFx32 *)(state + 0xa));
    VEC_Normalize((VecFx32 *)(state + 0xa), (VecFx32 *)(state + 0xa));
    bob = data_0203d210[(state[0x14] >> 4) * 2] * 0x600 / 2;
    if (bob < 0) {
        bob = -bob;
    }
    ScaleVec3Fx12(bob / 0x1000 + 0x300 + state[7], (VecFx32 *)(state + 0xa), (VecFx32 *)(state + 0xa));
    if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
        n = *(VecFx32 *)(*state + 0x114);
        idx = ANG2IDX(state[3]);
        back.x = -data_0203d210[idx * 2];
        back.y = 0;
        back.z = -data_0203d210[idx * 2 + 1];
        ScaleVec3Fx12(VEC_DotProduct(&back, &n) << 1, &n, &refl);
        VEC_Subtract(&refl, &back, &refl);
        VEC_Normalize(&refl, &refl);
        state[0x13] = FX_Atan2(refl.x, refl.z);
        len = VEC_Normalize((VecFx32 *)(state + 0xa), (VecFx32 *)(state + 0xa));
        ScaleVec3Fx12(len, &refl, (VecFx32 *)(state + 0xa));
        state[0x18] = 1;
    }
    dist = Ov218_DistanceToTarget(node);
    if (dist < 0) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (Ov218_WalkDecide(node, dist) != 0) {
        return;
    }
    state[4] = state[3] = FX_Atan2(state[0xa], state[0xc]);
    state[0x14] += *(int *)(*node + 0x2c) * state[0x15] / 0x1000;
    if (state[0x14] < 0x8000) {
        return;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov218_CircleTick);
    Ov218_CircleTick(node);
}
