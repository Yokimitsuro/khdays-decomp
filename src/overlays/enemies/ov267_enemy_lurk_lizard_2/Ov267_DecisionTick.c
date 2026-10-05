/* Decision tick of the ov266 enemy. With the +0x60 low bit set the reaction cue runs; the target
 * is re-acquired (020cab14) into +0x5a8 -- none queues sub-state 2 -- and the flat unit direction
 * from the actor's +0x508 point, the gap beyond both radii and the heading (atan2 into +0x3c)
 * are computed; the +0x34 heading gives the forward vector and the +0x4c delay counts down. A
 * grabbing actor (020cf42c) backs off along the forward at the +0x578 speed inside 3.0, else
 * strafes along the up x direction, flipping the +0x60 sense on a +0x17a bit-1 contact.
 * Otherwise it closes in beyond 9.5, backs off inside 3.0, or -- with the +4 item idle and neither
 * the 020cffbc nor the 020cfb00 check firing -- queues sub-state 2. An idle item with the cfb00
 * check quiet plays animation 5. When a sub-state was queued animation 0x10 plays, the sub-state
 * is remembered at +0x5d and cleared, and the tick hands off to 020d1124. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

struct Hw60 { unsigned short lo : 8, hi : 8; };
struct b2 { unsigned char b0 : 1, b1 : 1; };

extern void Ov267_ReactionCueTick(int *node, int actor, void *at);
extern int Ov107_FindNearestObject(int actor, int mode);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int Ov267_IsState6cActive(int *state, int a);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int Ov267_IsTargetOutsideCone(int *node);
extern int Ov267_ChooseMove(int *node, int gap);
extern const short data_0203d210[];
extern const VecFx32 data_02042264;
extern void Ov267_AiQueueStoredOnAnimEnd(int *node);

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void Ov267_DecisionTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 aim;
    VecFx32 fwd;
    VecFx32 side;
    int gap;
    int len;
    int target;
    unsigned short idx;

    if ((((struct Hw60 *)(*state + 0x60))->lo & 1) != 0) {
        Ov267_ReactionCueTick(node, *state, (void *)state[2]);
    }
    *(int *)(*state + 0x5a8) = Ov107_FindNearestObject(*state, 0);
    target = *(int *)(*state + 0x5a8);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(target + 0x190), (VecFx32 *)(*state + 0x108 + 0x400), &aim);
    aim.y = 0;
    len = VEC_Normalize(&aim, &aim);
    gap = len - *(int *)(*(int *)(*state + 0x5a8) + 0x80) - *(int *)(*state + 0x80);
    state[0xf] = FX_Atan2(aim.x, aim.z);
    idx = FX_RadToIdx(state[0xd]);
    fwd.y = 0;
    fwd.x = data_0203d210[(idx >> 4) * 2];
    fwd.z = data_0203d210[(idx >> 4) * 2 + 1];
    state[0x13] -= *(int *)(node[0] + 0x2c);
    if (state[0x13] <= 0) {
        state[0x13] = 0;
    }
    if (Ov267_IsState6cActive(state, 1) != 0) {
        if (gap < 0x3000) {
            ScaleVec3Fx12(-*(int *)(*state + 0x578), &fwd, (VecFx32 *)(state + 4));
        } else {
            if (((struct b2 *)(*state + 0x17a))->b1 != 0) {
                state[0x18] ^= 1;
            }
            VEC_CrossProduct(&data_02042264, &aim, &side);
            VEC_Normalize(&side, &side);
            ScaleVec3Fx12(state[0x18] == 0 ? *(int *)(*state + 0x578) : -*(int *)(*state + 0x578), &side, (VecFx32 *)(state + 4));
        }
    } else {
        if (gap > 0x9800) {
            ScaleVec3Fx12(*(int *)(*state + 0x578), &fwd, (VecFx32 *)(state + 4));
        } else if (gap < 0x3000) {
            ScaleVec3Fx12(-*(int *)(*state + 0x578), &fwd, (VecFx32 *)(state + 4));
        } else if (*(unsigned char *)(state[1] + 0xad) == 0 && Ov267_IsTargetOutsideCone(node) == 0
                   && Ov267_ChooseMove(node, gap) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0 && Ov267_ChooseMove(node, gap) == 0) {
        Ov107_PostTagUpdate((Actor *)(*state), 5, 0);
    }
    if (*(signed char *)(*state + 0x1c7) == -1) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x10, 0);
    *(unsigned char *)((char *)state + 0x5d) = *(signed char *)(*state + 0x1c7);
    *(signed char *)(*state + 0x1c7) = -1;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov267_AiQueueStoredOnAnimEnd);
}
