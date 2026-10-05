/* Walk tick of the ov241 enemy (x3: ov241/242/243): the +0x40 latch flips to 1 with reaction
 * 0x13a/4 at the +0xc position once the +0x384 item's animation passes 22.0, and back to 0 when
 * it drops under it. The +0x39c resource's forward vector (scaled speed) is rotated by the
 * actor's +0xa0 placement; the offset from the +0xc position to the +0x1c waypoint gives the +8
 * heading and, normalised, the walk: the step (+0x10) is the forward vector scaled by
 * min(1.5 x speed, dist / 2) times the (clamped) dot with the offset; +0x28 is 30 x dt / 10.
 * Arriving inside the actor's +0x80 radius requests sub-state 2 and releases the slot. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern void Ov107_BuildAndSendUpdate(int actor, int id, int mode, void *anchor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int node, int slot, void *cb);

void Ov241_WalkTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    VecFx32 fwd;
    int dist;
    int limit;
    int dot;
    int speed;

    if (*(unsigned char *)(state + 0x10) == 0) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) >= 0x16000) {
            Ov107_BuildAndSendUpdate(*state, 0x13a, 4, (void *)state[3]);
            *(unsigned char *)(state + 0x10) = 1;
        }
    } else if (*(unsigned char *)(state + 0x10) == 1) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) < 0x16000) {
            *(unsigned char *)(state + 0x10) = 0;
        }
    }
    speed = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x39c), &fwd);
    limit = (int)(((long long)speed * 0x1800 + 0x800) >> 12);
    Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &fwd);
    VEC_Subtract((VecFx32 *)state[7], (VecFx32 *)state[3], &d);
    dist = VEC_Normalize(&d, &d);
    if (dist < limit) {
        limit = dist >> 1;
    }
    state[2] = FX_Atan2(d.x, d.z);
    dot = VEC_DotProduct(&d, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    ScaleVec3Fx12((int)(((long long)limit * dot + 0x800) >> 12), &fwd, (VecFx32 *)(state + 4));
    state[0xa] = *(int *)(*(int *)node + 0x2c) * 30 / 10;
    if (dist > *(int *)(*state + 0x80)) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
