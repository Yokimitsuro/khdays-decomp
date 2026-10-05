/* Steering helper of the ov255 states: returns the gap from the owner to the target (the distance
 * between their +0x74 centres less both +0x80 radii; 0 without a target) after turning the +0x2c
 * orientation to face it about data_02042264. The +0x3a4 part's motion step (020c9f48) is then
 * turned by the +0x1c orientation and stored in *dir, its speed in *speed (either may be null). */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int w[4]; } Quat;

extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern const VecFx32 data_02042264;

int Ov255_SteerToTarget(int *state, int target, VecFx32 *dir, int *speed)
{
    VecFx32 step;
    VecFx32 d;
    int owner;
    int gap;
    int s;

    if (target != 0) {
        owner = *state;
        VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), &d);
        QuatFromAxisAngle((Quat *)(state + 0xb), &data_02042264, FX_Atan2(d.x, d.z));
        gap = VEC_Normalize(&d, &d) - *(int *)(owner + 0x80) - *(int *)(target + 0x80);
        s = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3a4), &step);
        Vec3TransformViaTempMtx(&step, state + 7, &step);
        if (dir != 0) {
            *dir = step;
        }
        if (speed != 0) {
            *speed = s;
        }
        return gap;
    }
    return 0;
}
