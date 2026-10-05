/*
 * Ov121_ChargeTowardTarget_Step -- Ov121_ChargeTowardTarget_Step.
 *
 * One frame of the charge that follows the seed timer (the caller at 020ced28). Shared
 * byte-for-byte with ov120 and ov122; against ov120 even the relocations match.
 *
 * Re-acquire the target through the ov107 finder and keep it in the action state. With no
 * target, drop the owner into action state 2 and release the node's slot. Otherwise take the
 * aim vector owner->target, flatten it onto the ground plane, normalise it, and subtract both
 * radii to get the gap; the heading (atan2 of the flattened aim) goes to the state. A gap past
 * the owner's reach also gives up.
 *
 * Then build the facing direction from the sin/cos table indexed by the stored facing angle,
 * project the aim onto it (clamped at zero) and store that projection scaled by 0x300 as the
 * charge velocity. Once the gap closes below 0x800 the velocity is zeroed, and if the target is
 * also well in front (projection at or above 0xc00) the charge is finished. Failing that it ends
 * on the accumulated-time limit of 0x2000.
 *
 * Ghidra: Ov121_ChargeTowardTarget_Step(Ov120ActionNode *pNode), types /khdays/Ov120ActionNode,
 * /khdays/Ov120ActionState, /khdays/Ov120Actor, /khdays/Ov107LockTarget,
 * /khdays/SceneFrameClock and /khdays/Vec3.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - THE TARGET IS READ TWICE THROUGH TWO DIFFERENT PATHS. The finder's result is stored
 *    straight into the state and used from there for VEC_Subtract; the radius later re-reads
 *    the field into a local. Holding the result in one local across both uses swaps the two
 *    callee-saved registers, because the local that is re-read has to be younger than the owner
 *    local for the allocator to pair it with the gap. Same crack the melee picker at 020ccd90
 *    records for its own two locals.
 *  - The two radii are subtracted target first, owner second, which is what fixes the load
 *    order of the two pointers.
 *  - The angle-to-index scale is the catalogued 64-bit form; it must stay one expression.
 *  - nElapsed40 is accumulated and compared in that order: the ROM stores the new value
 *    unconditionally and branches on it, which is what the single statement produces.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/actor.h"
#include "game/ai_task.h"

struct Ov107LockTarget {
    char pad000[0x80];
    int nRadius80;
    char pad084[0x10c];
    VecFx32 vPos190;
};

struct Ov120ActionState {
    Actor *pOwner;
    char pad004[4];
    struct Ov107LockTarget *pTarget;
    char pad00c[4];
    int nFacing10;
    int nHeading14;
    int nSpeed18;
    VecFx32 vVelocity;
    char pad028[0x18];
    int nElapsed40;
};

struct SceneFrameClock {
    char pad00[0x2c];
    int nDelta2c;
};

struct Ov120ActionNode {
    AI_TASK_FIELDS(struct Ov120ActionState)
};

extern const short data_0203d210[];
extern VecFx32 data_02041dc8;

extern struct Ov107LockTarget *Ov107_FindNearestObject(Actor *owner, int out);
extern void SetIndexedSlot(void *node, int idx, void *value);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *unit);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern void ScaleVec3Fx12(int scale, void *src, void *dst);

void Ov121_ChargeTowardTarget_Step(struct Ov120ActionNode *node)
{
    VecFx32 vAim;
    VecFx32 vFacing;
    struct Ov120ActionState *state;
    struct Ov107LockTarget *target;
    Actor *owner;
    int gap;
    int idx;
    int dot;

    state = node->pState;
    state->pTarget = Ov107_FindNearestObject(state->pOwner, 0);
    if (state->pTarget == 0) {
        state->pOwner->nextState = 2;
        SetIndexedSlot(node, node->slot, 0);
        return;
    }

    VEC_Subtract(&state->pTarget->vPos190, &state->pOwner->srt.translation, &vAim);
    vAim.y = 0;
    target = state->pTarget;
    owner = state->pOwner;
    gap = VEC_Normalize(&vAim, &vAim) - target->nRadius80 - owner->sphere.radius;
    state->nHeading14 = FX_Atan2(vAim.x, vAim.z);
    if (gap > state->pOwner->range) {
        state->pOwner->nextState = 2;
        SetIndexedSlot(node, node->slot, 0);
        return;
    }

    idx = (int)((unsigned)((int)(((long long)state->nFacing10 * 0x28be60db9391LL
                                  + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    vFacing.x = data_0203d210[idx * 2];
    vFacing.y = 0;
    vFacing.z = data_0203d210[idx * 2 + 1];
    dot = VEC_DotProduct(&vFacing, &vAim);
    if (dot < 0) {
        dot = 0;
    }
    ScaleVec3Fx12((int)(((long long)dot * 0x300 + 0x800) >> 0xc),
                  &vFacing, &state->vVelocity);
    state->nSpeed18 = (((struct SceneFrameClock *)node->pList)->nDelta2c * 30) / 5;

    if (gap < 0x800) {
        state->vVelocity = data_02041dc8;
        if (VEC_DotProduct(&vFacing, &vAim) >= 0xc00) {
            state->pOwner->nextState = 2;
            SetIndexedSlot(node, node->slot, 0);
            return;
        }
    }

    state->nElapsed40 += ((struct SceneFrameClock *)node->pList)->nDelta2c;
    if (state->nElapsed40 >= 0x2000) {
        state->pOwner->nextState = 2;
        SetIndexedSlot(node, node->slot, 0);
    }
}
