/* Approach tick of the ov146 actor. With a partner guard (+0x58) it looks for the nearest target
 * (020cab14, into the actor's +0x3b4); one closer than 6.0 is circled: the +0x30 heading points at it,
 * the +0x38 radius is its distance plus 8.0, +0x34 clears, a random direction (+0x4c = +/-1) is chosen
 * and the node moves on to 020cd3b4. Otherwise it walks toward its partner (+8) at up to 0.0234 along
 * the ground-plane heading (+0x2c); within reach (both radii plus 0.0234) the next move is 5, and once
 * the +0x44 timer is out it is 6. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov146_SwoopTick(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov146_ApproachTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 unit;
    VecFx32 to;
    VecFx32 dir;
    int dist;
    int reach;
    int flat;

    if (state[0x16] != 0) {
        *(int *)(*state + 0x3b4) = Ov107_FindNearestObject(*state, 0);
        if (*(int *)(*state + 0x3b4) == 0) {
            return;
        }
        VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x3b4) + 0x190), (VecFx32 *)(*state + 0xb0), &d);
        {
            int range = VEC_Normalize(&d, &d);

            if (range >= 0x6000) {
                return;
            }
            state[0xc] = FX_Atan2(d.x, d.z);
            state[0xe] = range + 0x8000;
        }
        state[0xd] = 0;
        state[0x13] = RandNextScaled(2) != 0 ? 1 : -1;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov146_SwoopTick);
        return;
    }
    reach = *(int *)(state[2] + 0x80) + 0x60 + *(int *)(*state + 0x80);
    VEC_Subtract((VecFx32 *)(state[2] + 0xb0), (VecFx32 *)(*state + 0xb0), &to);
    dist = VEC_Normalize(&to, &unit);
    to.y = 0;
    flat = VEC_Normalize(&to, &to);
    state[0xb] = FX_Atan2(to.x, to.z);
    {
        int idx = ANG2IDX(state[0xb]) * 2;

        dir.x = data_0203d210[idx];
        dir.y = 0;
        dir.z = data_0203d210[idx + 1];
    }
    if (flat >= 0x60) {
        flat = 0x60;
    }
    ScaleVec3Fx12(flat, &dir, (VecFx32 *)(state + 4));
    if (dist < reach) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x11] > 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 6;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
