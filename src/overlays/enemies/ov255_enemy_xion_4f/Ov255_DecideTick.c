/* Decide tick of an ov255 state: the nearest target (020cab14) becomes +0x5c; without one nothing
 * happens. The +0x40 rate follows the frame rate, the +0x2c orientation faces the target and the
 * gap is measured (centres less both +0x80 radii). For the first 3.0 of +0x70 the clock runs and the
 * +0x54 cooldown is re-rolled. Then: a +0x6c-armed enemy under 30% HP flees (0xb); 30.0 on the
 * +0x58 clock forces 0xc; with the cooldown out a pending +0x74 request picks 8, a far target
 * picks 0xc (30%) or, with the +0x3ec partner active and within 8.0, 9, a near one 8 (70%) or 9
 * with the partner active. Otherwise a target 8.0 away brings 4, and within 2.0 a 1-in-11 chance
 * picks one of 5, 6 and 7. */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int w[4]; } Quat;
struct Bits5c { int b0 : 1, b1 : 1; };

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int func_02020400(int num, int den);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02042264;

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + RandNextScaled(d + 1);
}

#define PARTNER_ACTIVE(owner) \
    (((struct Bits5c *)(*(int *)(*(int *)((owner) + 0x3ec) + 0x40) + 0x5c))->b1)

void Ov255_DecideTick(int *node)
{
    int gap;
    int roll;
    int owner;
    int target;
    int *state = (int *)node[1];
    VecFx32 d;

    target = state[0x17] = Ov107_FindNearestObject(*state, 0);
    if (target == 0) {
        return;
    }
    {
        owner = *state;
        state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 30;
        VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), &d);
        QuatFromAxisAngle((Quat *)(state + 0xb), &data_02042264, FX_Atan2(d.x, d.z));
        gap = VEC_Normalize(&d, &d) - *(int *)(owner + 0x80) - *(int *)(target + 0x80);
    }
    if (state[0x1c] < 0x3000) {
        state[0x1c] += *(int *)(node[0] + 0x2c);
        state[0x15] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        return;
    }
    if (state[0x1b] != 0) {
        int owner = *state;

        if (func_02020400(*(short *)(owner + 0x21a) << 12, *(short *)(owner + 0x218)) <= 0x4cc) {
            *(signed char *)(owner + 0x1c7) = 0xb;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[0x16] >= 0x1e000) {
        *(signed char *)(*state + 0x1c7) = 0xc;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x15] <= 0) {
        if (state[0x1d] != 0) {
            state[0x1d] = 0;
            *(signed char *)(*state + 0x1c7) = 8;
        } else if (gap > 0x6000) {
            roll = RandRange(0, 100);
            if (roll < 0x1e || !PARTNER_ACTIVE(*state)) {
                *(signed char *)(*state + 0x1c7) = 0xc;
            } else if (gap < 0x8000) {
                *(signed char *)(*state + 0x1c7) = 9;
            }
        } else {
            roll = RandRange(0, 100);
            if (roll < 0x46 || !PARTNER_ACTIVE(*state)) {
                *(signed char *)(*state + 0x1c7) = 8;
            } else {
                *(signed char *)(*state + 0x1c7) = 9;
            }
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (gap >= 0x8000) {
        *(signed char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap > 0x2000) {
        return;
    }
    if (RandRange(0, 10) != 0) {
        return;
    }
    roll = RandRange(0, 2);
    if (roll == 0) {
        *(signed char *)(*state + 0x1c7) = 5;
    } else if (roll == 1) {
        *(signed char *)(*state + 0x1c7) = 6;
    } else if (roll == 2) {
        *(signed char *)(*state + 0x1c7) = 7;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
