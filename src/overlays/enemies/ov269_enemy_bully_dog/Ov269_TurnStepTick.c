/* Turn-and-step tick of the ov194 enemy (x3: ov194/195/196, x5 with two ov2xx twins): acquires
 * a target (+8) -- none requests sub-state 2 and releases the slot. The flattened, normalised
 * offset from the actor's +0xb0 position to the target's +0x190 gives the +0x10 heading; the
 * +0xc facing becomes a unit vector (sine/cosine table) whose dot with that offset, clamped to
 * 0..1, scales the +0x3d0 resource's forward speed into the +0x18 step. Once the +4 item's
 * +0xad byte clears, a positive +0x44 timer requests sub-state 7 and otherwise 2. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern const short data_0203d210[];

void Ov269_TurnStepTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    VecFx32 fwd;
    int idx;
    int dot;
    int speed;

    state[2] = Ov107_FindNearestObject(*state, 0);
    if (state[2] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    d.y = 0;
    VEC_Normalize(&d, &d);
    state[4] = FX_Atan2(d.x, d.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[3] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                              /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                        /* FX_CosIdx */
    dot = VEC_DotProduct(&fwd, &d);
    if (dot < 0) {
        dot = -dot;
    }
    if (dot < 0) {
        dot = 0;
    }
    speed = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3d0), 0);
    ScaleVec3Fx12((int)(((long long)speed * dot + 0x800) >> 12), &fwd, (VecFx32 *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x11] > 0) {
        *(unsigned char *)(*state + 0x1c7) = 7;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
