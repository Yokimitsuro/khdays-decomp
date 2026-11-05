/* Bounce entry of the ov114 enemy: sets bit 0 of the actor's +0x1ae and bit 1 of the +0x60
 * high byte, deactivates the +0x388 shape, seeds the height scale +0x390 with 0xcc (flat) and plays
 * animation 6 (looped). Two random headings (yaw within +-0x3244, scaled to 10.0 plus a random
 * 0..4.0) go to +0x1c and +0x28, the +4 position is copied to +0x34, a third random yaw to
 * +0x40 and +0x44 is cleared before the cd560 tick takes over. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct w8 { unsigned int lo : 8, rest : 24; };

extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov114_BounceTick(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + RandNextScaled(span + 1);
}

void Ov114_BounceEntry(int *node)
{
    int *state = (int *)node[1];
    unsigned int idx;

    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    *(int *)(*state + 0x390) = 0xcc;
    Ov107_PostTagUpdate((Actor *)(*state), 6, 1);
    idx = ANG2IDX(RandRange(-0x3244, 0x3244));
    state[7] = data_0203d210[idx * 2];                                        /* FX_SinIdx */
    state[8] = 0;
    state[9] = data_0203d210[idx * 2 + 1];                                    /* FX_CosIdx */
    ScaleVec3Fx12(RandRange(0, 0x4000) + 0xa000, (VecFx32 *)(state + 7), (VecFx32 *)(state + 7));
    idx = ANG2IDX(RandRange(-0x3244, 0x3244));
    state[10] = data_0203d210[idx * 2];                                       /* FX_SinIdx */
    state[11] = 0;
    state[12] = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
    ScaleVec3Fx12(RandRange(0, 0x4000) + 0xa000, (VecFx32 *)(state + 10), (VecFx32 *)(state + 10));
    *(VecFx32 *)(state + 13) = *(VecFx32 *)state[1];
    state[0x10] = RandRange(-0x3244, 0x3244);
    state[0x11] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov114_BounceTick);
}
