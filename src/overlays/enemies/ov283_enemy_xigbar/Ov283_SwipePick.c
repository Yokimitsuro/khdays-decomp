/* Swipe pick of the ov283 actor: +0x5c is 0.56; with a target (+0xc) both headings (+0x38, +0x40)
 * turn toward it and it counts as in front when it lies ahead of the old +0x38 heading. A front target
 * gets pose 5 or 6, otherwise 7 or 8 (random), and the node moves on to 020cebb4. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov283_DecideTick(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov283_SwipePick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 fwd;
    VecFx32 d;
    int front;
    int actor;

    state[0x17] = 0x900;
    front = 0;
    if (state[3] != 0) {
        {
            int idx = ANG2IDX(state[0xe]) * 2;

            fwd.y = 0;
            fwd.x = data_0203d210[idx];
            fwd.z = data_0203d210[idx + 1];
        }
        VEC_Subtract((VecFx32 *)(state[3] + 0x74), (VecFx32 *)(*state + 0x74), &d);
        VEC_Normalize(&d, &d);
        if (VEC_DotProduct(&fwd, &d) >= 0) {
            front = 1;
        }
        state[0xe] = state[0x10] = FX_Atan2(d.x, d.z);
    }
    actor = *state;
    if (front) {
        Ov107_PostTagUpdate((Actor *)actor, RandNextScaled(2) + 5, 0);
    } else {
        Ov107_PostTagUpdate((Actor *)actor, RandNextScaled(2) + 7, 0);
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov283_DecideTick);
}
