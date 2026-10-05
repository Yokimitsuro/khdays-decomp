/* Lunge tick of the ov259 actor: it keeps turning from the +0x10 point to the +0x2c goal (+0x78 /
 * +0x7c heading) and the +0x14 drift becomes the heading's unit vector with the goal's normalised
 * height. While the goal is farther than 0.5 (020cddbc) and the actor is airborne on neither flag of
 * +0x17a the drift scales by 0.4375; otherwise +0x60 stops it, and a stopped actor's drift clears.
 * Once the partner holds no queued move the node moves on to 020cf474. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern int Ov259_ComputeNormalizedDir(int node, VecFx32 pos);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_LandingCheck(void);
extern const short data_0203d210[];
extern const VecFx32 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov259_LungeTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 n;

    VEC_Subtract((VecFx32 *)(state + 0xb), (VecFx32 *)state[4], &d);
    state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    VEC_Normalize(&d, &n);
    {
        int idx = ANG2IDX(state[0x1e]);

        int y = n.y;
        state[5] = data_0203d210[idx * 2];
        state[6] = y;
        state[7] = data_0203d210[idx * 2 + 1];
    }
    if (Ov259_ComputeNormalizedDir((int)node, *(VecFx32 *)(state + 0xb)) > 0x800 &&
        !((struct Flag17a *)(*state + 0x17a))->b0 && !((struct Flag17a *)(*state + 0x17a))->b1) {
        ScaleVec3Fx12(0x700, (VecFx32 *)(state + 5), (VecFx32 *)(state + 5));
    } else {
        state[0x18] = 1;
    }
    if (state[0x18] != 0) {
        *(VecFx32 *)(state + 5) = data_02041dc8;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_LandingCheck);
}
