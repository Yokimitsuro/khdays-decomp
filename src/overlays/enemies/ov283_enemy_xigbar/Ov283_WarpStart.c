/* Warp start of the ov283 actor: after the shared step (020ccb48) both headings (+0x38, +0x40) face
 * the target's +0x390 model point and the landing spot is picked past the target along the heading
 * (by both radii, vertical part from the aim); the floor is probed ahead of the target (twice the +0x80
 * range, radius 0x100). With the floor clear the warp is dropped: the +0x50 clock resets, +0x34
 * rerolls (1.57 to 3.14; +0x7c = past 2.36, +0x3c cleared) and the next move is 4. Otherwise an
 * effect plays at the +8 point, the actor moves to the spot at the target's height (020c5c54) and the
 * brain waits on 020ce620. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern void Ov283_MeasureTargetGap(int *node);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Collision_CastSphereEx(int collision, VecFx32 *origin, VecFx32 *dir, int radius, void *ignore);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov283_AiFaceTargetB(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov283_WarpStart(int *node)
{
    int *state = (int *)node[1];
    VecFx32 fwd;
    VecFx32 d;
    VecFx32 unit;
    VecFx32 off;
    VecFx32 target;
    VecFx32 probe;
    int world;
    int hit;

    Ov283_MeasureTargetGap(node);
    world = *(int *)(*state + 4);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        fwd.x = data_0203d210[idx];
        fwd.y = 0;
        fwd.z = data_0203d210[idx + 1];
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x390) + 0x190), (VecFx32 *)(*state + 0x74), &d);
    VEC_Normalize(&d, &d);
    state[0xe] = state[0x10] = FX_Atan2(d.x, d.z);
    target = *(VecFx32 *)(*(int *)(*state + 0x390) + 0x190);
    VEC_Normalize(&d, &unit);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        off.x = data_0203d210[idx];
        off.y = unit.y;
        off.z = data_0203d210[idx + 1];
    }
    ScaleVec3Fx12(*(int *)(*(int *)(*state + 0x390) + 0x80) + *(int *)(*state + 0x80), &off, &off);
    VEC_Add(&target, &off, &target);
    probe = target;
    VEC_Add(&probe, &off, &probe);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        fwd.x = data_0203d210[idx];
        fwd.y = 0;
        fwd.z = data_0203d210[idx + 1];
    }
    ScaleVec3Fx12(*(int *)(*state + 0x80) * 2, &fwd, &d);
    hit = Collision_CastSphereEx(*(int *)(world + 0x7c), (VecFx32 *)(*(int *)(*state + 0x390) + 0x74), &d, 0x100, 0);
    target.y = *(int *)(*(int *)(*state + 0x390) + 0x194);
    if (hit != 0 && *(int *)(hit + 8) == 0) {
        state[0x14] = 0;
        state[0xd] = Rand16NextScaled(0x1922) + 0x1922;
        state[0x1f] = state[0xd] > 0x25b3;
        state[0xf] = 0;
        *(signed char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c0b90(*state, 0, *(VecFx32 *)state[2], 0);
    Ov107_MoveNodeAndRelayout((Actor *)(*state), &target);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov283_AiFaceTargetB);
}
