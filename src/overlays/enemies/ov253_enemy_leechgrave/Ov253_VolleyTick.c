/* Ov253_VolleyTick -- volley tick: the nearest visible target facing the +0xc heading within
 * 60.0 (020cd0d8) is kept at +0x24; with one, the +0x10 heading turns towards it and the +0x1c
 * timer runs up: past 0.167 the first idle +0x45c part (bit 0 of its +0x60 low byte clear) is
 * launched from the +0x39c joint towards the target (020d3a30), reaction 0x16b/5 fires there,
 * the timer restarts and the +0x20 count grows. The +0x14 speed follows three times the frame
 * step (30 / 10); without a target or after eight launches the +0x38c item's +0xa8 flag clears
 * and the node moves to 020ce0ac. */

#include "nitro/fx_types.h"

struct hw60 { unsigned short lo : 8, hi : 8; };

extern int Ov253_FindNearestTarget(int self, const VecFx32 *pos, const VecFx32 *dir, int minDot, int maxDist);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void Ov253_Item_StoreVecAndRelayout(int part, void *anchor, VecFx32 *dir);
extern void Ov107_BuildAndSendUpdate(int actor, int id, int kind, void *anchor);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void Ov253_AiEnterRecover(void);

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void Ov253_VolleyTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 launch;
    VecFx32 aim;
    VecFx32 dir;
    int i;

    launch.x = data_0203d210[(FX_RadToIdx(state[3]) >> 4) << 1];
    launch.y = 0;
    launch.z = data_0203d210[((FX_RadToIdx(state[3]) >> 4) << 1) + 1];
    state[9] = Ov253_FindNearestTarget(*state, (VecFx32 *)state[2], &launch, -0x1000, 0x3c000);
    if (state[9] != 0) {
        VEC_Subtract((VecFx32 *)(state[9] + 0x74), (VecFx32 *)(*(int *)(*state + 0x39c) + 0x14), &dir);
        VEC_Normalize(&dir, &dir);
        VEC_Subtract((VecFx32 *)(state[9] + 0x74), (VecFx32 *)state[2], &aim);
        aim.y = 0;
        state[4] = FX_Atan2(aim.x, aim.z);
        state[7] += *(int *)(node[0] + 0x2c);
        if (state[7] >= 0x2aa) {
            VEC_Normalize(&aim, &aim);
            for (i = 0; i < 8; i++) {
                if ((((struct hw60 *)((*(int **)(*state + 0x45c))[i] + 0x60))->lo & 1) == 0) {
                    state[7] = 0;
                    Ov253_Item_StoreVecAndRelayout((*(int **)(*state + 0x45c))[i], (void *)(*(int *)(*state + 0x39c) + 0x14), &dir);
                    Ov107_BuildAndSendUpdate(*state, 0x16b, 5, (void *)(*(int *)(*state + 0x39c) + 0x14));
                    state[8] += 1;
                    break;
                }
            }
        }
    }
    state[5] = *(int *)(node[0] + 0x2c) * 0x1e / 10;
    if (state[9] != 0 && state[8] < 8) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x38c) + 0xa8) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov253_AiEnterRecover);
}
