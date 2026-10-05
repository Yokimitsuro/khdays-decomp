/* Aim tick of the ov153 enemy (x3: ov153/154/155): acquires a target through the ov107 hook
 * (mode 0) into +0x18 -- none ends in sub-state 2 with the slot released. Otherwise the heading
 * (+0x14) is the atan2 of the offset from the +4 position to the target's +0x190, the +0x20 step
 * is 30 x dt / 40 and the +0x1c timer grows by dt; once the timer passes 0.8 and the +0x24 latch
 * is clear the latch is set, the world Z axis is rotated by the actor's +0xa0 placement, reaction
 * 0x13c/4 fires at the +0x38c node's +0x14 and Ov155_RelayoutAndStoreVec launches from the +0x398 item
 * along that vector. Finally the byte behind +0xc (the item's +0xad) being clear ends the aim in
 * sub-state 2. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate(int actor, int id, int mode, void *anchor);
extern void Ov155_RelayoutAndStoreVec(int item, void *anchor, VecFx32 *dir);
extern const VecFx32 data_02042258;

void Ov155_AimTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    VecFx32 dir;

    state[6] = Ov107_FindNearestObject(*state, 0);
    if (state[6] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[1], &d);
    state[5] = FX_Atan2(d.x, d.z);
    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 40;
    state[7] += *(int *)(*(int *)node + 0x2c);
    if (*(unsigned char *)(state + 9) == 0 && state[7] >= 0xccc) {
        *(unsigned char *)(state + 9) = 1;
        Vec3TransformViaTempMtx(&dir, (void *)(*state + 0xa0), &data_02042258);
        Ov107_BuildAndSendUpdate(*state, 0x13c, 4, (void *)(*(int *)(*state + 0x38c) + 0x14));
        Ov155_RelayoutAndStoreVec(*(int *)(*state + 0x398), (void *)(*(int *)(*state + 0x38c) + 0x14), &dir);
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
