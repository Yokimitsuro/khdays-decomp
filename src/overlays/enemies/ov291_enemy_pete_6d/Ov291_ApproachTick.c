/* Approach tick of the ov291 enemy: the +0x394 part's motion step gives the speed and, rotated
 * by the actor's +0xa0 orientation, the forward vector; the +0x28 phase fires reaction 0x16f
 * mode 4 once the +0x384 item's animation passes 0x4000, mode 5 past 0x15000 and resets below
 * it. The +0x3a0 waypoint selected by +0x24 (16 bytes each, +0x10) minus the +0xc position gives
 * the +8 heading and the distance, which halves the speed when shorter; the +0x10 velocity is
 * the forward vector at half the speed scaled by the (clamped) alignment, +0x1c clears and,
 * once the +0x20 busy byte clears, animation 3 plays, the part runs action 2, the phase resets
 * and the tick hands off to cd2d0. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern void Ov107_BuildAndSendUpdate(int actor, int id, int mode, void *anchor);
extern int Ov107_ActionResource_GetOffsetAndScale(int resource, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void Ov107_PostTagUpdate(int actor, int anim, int flag);
extern void Ov107_StartAnim(void *part, int a, int b);
extern void Ov291_AiSpinTick(void);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int node, int slot, void *cb);

void Ov291_ApproachTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 fwd;
    VecFx32 at;
    VecFx32 d;
    int dist;
    int limit;
    int dot;
    int speed;

    speed = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x394), &fwd);
    Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &fwd);
    if (*(unsigned char *)(state + 0xa) == 0) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) >= 0x4000) {
            Ov107_BuildAndSendUpdate(*state, 0x16f, 4, (void *)state[3]);
            *(unsigned char *)(state + 0xa) = 1;
        }
    } else if (*(unsigned char *)(state + 0xa) == 1) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) >= 0x15000) {
            Ov107_BuildAndSendUpdate(*state, 0x16f, 5, (void *)state[3]);
            *(unsigned char *)(state + 0xa) = 2;
        }
    } else if (*(unsigned char *)(state + 0xa) == 2) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) < 0x15000) {
            *(unsigned char *)(state + 0xa) = 0;
        }
    }
    at = *(VecFx32 *)(*(int *)(*state + 0x3a0) + (state[9] << 4) + 0x10);
    VEC_Subtract(&at, (VecFx32 *)state[3], &d);
    dist = VEC_Normalize(&d, &d);
    limit = speed;
    if (dist < limit) {
        limit = dist >> 1;
    }
    state[2] = FX_Atan2(d.x, d.z);
    dot = VEC_DotProduct(&d, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    ScaleVec3Fx12((int)(((long long)limit * dot + 0x800) >> 12) >> 1, &fwd, (VecFx32 *)(state + 4));
    state[7] = 0;
    if (*(unsigned char *)state[8] != 0) {
        return;
    }
    Ov107_PostTagUpdate(*state, 3, 0);
    Ov107_StartAnim(*(void **)(*state + 0x394), 2, 0);
    *(unsigned char *)(state + 0xa) = 0;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), Ov291_AiSpinTick);
}
