/* Charge-in tick: refreshes the +4 target (none: pose request 9), measures the surface gap
 * (root of the squared distance minus both +0x80 radii), counts the +0x3c timer down, heads for
 * the target (+0x30 = atan2 of the flattened, normalised offset, +8 velocity = the gap capped
 * at 0.5 along it, then dropped by 0x400 in y). Once the +0x24 child's byte clears the cue at
 * data_ov278_020d639c entry 6 goes through the +0x24 hook, the actor's +0x54 becomes 3.0, the
 * +0x14 word clears and the node moves to 020d29b8. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern unsigned short data_ov278_020d639c[];
extern void Ov278_PublishPounceLanding(void);

void Ov278_ChargeInTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    int dist;
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    int actor;
    int target;

    target = state[1] = Ov107_FindNearestObject(*state, &dist);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[0xf] -= *(int *)(*node + 0x2c);
    VEC_Subtract((VecFx32 *)(state[1] + 0x74), (VecFx32 *)(*state + 0x74), &d);
    d.y = 0;
    {
        int actor = state[0];
        int target = state[1];
        dist = VEC_Normalize(&d, &d) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    state[0xc] = FX_Atan2(d.x, d.z);
    ScaleVec3Fx12(dist >= 0x800 ? 0x800 : dist, &d, (VecFx32 *)(state + 2));
    state[3] -= 0x400;
    if (*(unsigned char *)state[9] != 0) {
        return;
    }
    pp = pair;
    pp[1] = data_ov278_020d639c[13];
    pp[0] = data_ov278_020d639c[12];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    *(int *)(*state + 0x54) = 0x3000;
    state[5] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov278_PublishPounceLanding);
}
