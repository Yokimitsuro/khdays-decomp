/* Chase tick of the ov283 helper (move 1 only): the goal heading (+0x18) points from its +4 point to
 * the owner's +0x38c model's target (+0x390); the +0x14 heading turns toward it at 1.125 per frame and
 * the +8 velocity runs along it at 0.5 (vertical part from the aim), the pose turns about up and the
 * +0xf0 velocity mirrors it. */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int x, y, z, w; } Quat;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void Srt_SetRotationQuat(void *srt, const Quat *rot);
extern const short data_0203d210[];
extern const VecFx32 data_02042264;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void VecSet(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Ov283_HelperChaseTick(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    VecFx32 d;
    VecFx32 unit;
    int rate;
    int target;

    if (*(signed char *)(*state + 0x1c6) != 1) {
        return;
    }
    rate = *(int *)(node[0] + 0x2c) * 0x5a / 80;
    target = *(int *)(*(int *)(*state + 0x38c) + 0x390);
    VEC_Subtract((VecFx32 *)(target + 0x190), (VecFx32 *)state[1], &d);
    state[6] = FX_Atan2(d.x, d.z);
    VEC_Normalize(&d, &unit);
    state[5] = Angle_TurnToward(state[5], state[6], rate, 0);
    {
        int idx = ANG2IDX(state[5]) * 2;

        VecSet((VecFx32 *)(state + 2), data_0203d210[idx], unit.y, data_0203d210[idx + 1]);
    }
    ScaleVec3Fx12(0x800, (VecFx32 *)(state + 2), (VecFx32 *)(state + 2));
    QuatFromAxisAngle(&q, &data_02042264, state[5]);
    Srt_SetRotationQuat((void *)(*state + 0xa0), &q);
    *(VecFx32 *)(*state + 0xf0) = *(VecFx32 *)(state + 2);
}
