/* Path-following tick of the ov291 enemy. The +0x394 item's speed and forward vector (rotated by
 * the actor's +0xa0 orientation) drive a three-phase sound cue on the +0x28 byte: the +0x384
 * item's channel-0 progress past 0x4000 fires reaction 0x16f/4, past 0x15000 reaction 0x16f/5,
 * and dropping below 0x15000 rearms it. The direction to the +0x3a0 path node after the +0x24
 * index (from the +0xc position) is normalised; a distance below the speed halves it; the +8
 * yaw aims at it and the +0x10 velocity is the facing (sin, 0, cos) of that yaw scaled by the
 * speed times the (clamped) alignment with the forward vector. The +0x1c turn step is
 * 30 x dt / 25. Within 0x1000 of the node its kind decides: 1/2 clears the +0x384 item's +0xa8
 * flag and hands off to cd100, 3 clears bit 0 of the +0x60 high byte and requests sub-state 0
 * (slot released), otherwise the index advances modulo the path's count. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct hw60 { unsigned short lo : 8, hi : 8; };

struct PathEntry {
    int x;
    int y;
    int z;
    int kind;
};

extern void Ov107_BuildAndSendUpdate(int actor, int id, int mode, void *anchor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov291_ApproachTick(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void Ov291_PathFollowTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 fwd;
    VecFx32 point;
    VecFx32 dir;
    int speed;
    int len;
    int dot;
    unsigned int idx;
    int i;
    struct PathEntry *path;
    int kind;

    speed = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x394), &fwd);
    Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &fwd);
    if (*(u8 *)(state + 0xa) == 0) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) >= 0x4000) {
            Ov107_BuildAndSendUpdate(*state, 0x16f, 4, (void *)state[3]);
            *(u8 *)(state + 0xa) = 1;
        }
    } else if (*(u8 *)(state + 0xa) == 1) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) >= 0x15000) {
            Ov107_BuildAndSendUpdate(*state, 0x16f, 5, (void *)state[3]);
            *(u8 *)(state + 0xa) = 2;
        }
    } else if (*(u8 *)(state + 0xa) == 2) {
        if (queryTableEntry(*(int *)(*state + 0x384), 0) < 0x15000) {
            *(u8 *)(state + 0xa) = 0;
        }
    }
    point = *(VecFx32 *)(*(int *)(*state + 0x3a0) + state[9] * 0x10 + 0x10);
    VEC_Subtract(&point, (VecFx32 *)state[3], &dir);
    len = VEC_Normalize(&dir, &dir);
    if (len < speed) {
        speed = len >> 1;
    }
    state[2] = FX_Atan2(dir.x, dir.z);
    dot = VEC_DotProduct(&dir, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    idx = ANG2IDX(state[2]);
    fwd.x = data_0203d210[idx * 2];                                       /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
    ScaleVec3Fx12(FX_MUL(speed, dot), &fwd, (VecFx32 *)(state + 4));
    state[7] = *(int *)(*node + 0x2c) * 30 / 25;
    if (len > 0x1000) {
        return;
    }
    i = state[9];
    path = (struct PathEntry *)*(int *)(*state + 0x3a0);
    kind = (u16)path[i].kind;
    if (kind == 1 || kind == 2) {
        *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov291_ApproachTick);
        return;
    }
    if (kind == 3) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~1;
        *(u8 *)(*state + 0x1c7) = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[9] = (i + 1) % path[0].z;
}
