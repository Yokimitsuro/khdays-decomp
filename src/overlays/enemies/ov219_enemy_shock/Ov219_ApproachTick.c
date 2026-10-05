/* Approach tick of the ov219 enemy (and its byte-identical twin): a wall contact (bit 1 of the
 * actor's +0x17a) requests sub-state 5 and ends the state, as does a negative distance to the
 * target. Otherwise the +0x24 velocity is the forward vector turned by the +0x10 yaw plus 180
 * degrees offset by 77 degrees to the side chosen by +0x48, at speed +0x20 plus 0x200 plus a
 * bob taken from the sine of the +0x4c phase (0xc00 / 3, folded to fixed point); the phase
 * advances by 24 turns per second (wrapped to 16 bits), the +0xc/+0x10 yaws follow the velocity
 * and, after 0x1000 of the +0x14 clock, the tick hands off to the wander state and runs it. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } Mtx33;
struct Bits17a { unsigned char bit0 : 1, bit1 : 1; };

extern void SetIndexedSlot(int *node, int slot, void *cb);
extern int Ov219_DistanceToTarget(int *node);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const VecFx32 *v, Mtx33 *m, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void Ov219_WanderTick(int *node);
extern short data_0203d210[];
extern const VecFx32 data_02042258;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov219_ApproachTick(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    int deg;
    int angle;
    int bob;
    unsigned int idx;

    if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (Ov219_DistanceToTarget(node) < 0) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    deg = *(unsigned char *)(state + 0x12) != 0 ? -0x4d : 0x4d;
    angle = state[4];
    angle += (deg + 0xb4) * 0x3244 / 180;
    idx = ANG2IDX(angle);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33(&data_02042258, &mtx, (VecFx32 *)(state + 9));
    bob = data_0203d210[(state[0x13] >> 4) * 2] * 0xc00 / 3;
    if (bob < 0) {
        bob = -bob;
    }
    ScaleVec3Fx12(bob / 0x1000 + 0x200 + state[8], (VecFx32 *)(state + 9), (VecFx32 *)(state + 9));
    state[0x13] += *(int *)(*node + 0x2c) * 0x18000 / 0x1000;
    state[0x13] &= 0x7fff;
    state[4] = state[3] = FX_Atan2(state[9], state[0xb]);
    state[5] += *(int *)(*node + 0x2c);
    if (state[5] >= 0x1000) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov219_WanderTick);
        Ov219_WanderTick(node);
    }
}
