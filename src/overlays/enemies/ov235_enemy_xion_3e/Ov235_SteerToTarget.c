/* Steering helper of the ov235 states: returns the gap from the owner to the target (the distance
 * between their +0x74 centres less both +0x80 radii; 0 without a target) and turns the +0x2c
 * orientation towards it. For the owner kinds 4, 6 and 7 (+0x1c6) the heading blends the tangent
 * of the circle about the origin (flipped to the target's side) with the direct direction, by how
 * well the target and the owner line up from the origin; otherwise it faces the target about
 * data_02042264. The +0x3a8 part's motion step (020c9f48) is then turned by the +0x1c
 * orientation and stored in *dir, its speed in *speed (either may be null). */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int w[4]; } Quat;

extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void Quat_FromTwoVectors(Quat *out, const VecFx32 *a, const VecFx32 *b);
extern fx16 FX_Atan2(int y, int x);
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;

static inline void VEC_Set(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

int Ov235_SteerToTarget(int *state, int target, VecFx32 *dir, int *speed)
{
    VecFx32 step;
    VecFx32 d;
    VecFx32 other;
    VecFx32 self;
    VecFx32 flat;
    VecFx32 side;
    int owner;
    int gap;
    int kind;
    int s;

    if (target != 0) {
    owner = *state;
    VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), &d);
    gap = VEC_Normalize(&d, &d) - *(int *)(owner + 0x80) - *(int *)(target + 0x80);
    kind = *(signed char *)(*state + 0x1c6);
    if (!(kind != 4 && kind != 6 && kind != 7)) {
        VecFx32 blend = {0, 0, 0};
        int dot;

        VEC_Subtract(&data_02041dc8, (void *)(target + 0x74), &other);
        other.y = 0;
        VEC_Normalize(&other, &other);
        VEC_Subtract(&data_02041dc8, (void *)(owner + 0x74), &self);
        self.y = 0;
        VEC_Normalize(&self, &self);
        flat = d;
        flat.y = 0;
        VEC_Normalize(&flat, &flat);
        VEC_CrossProduct(&data_02042264, &self, &side);
        dot = VEC_DotProduct(&other, &self);
        if (dot < 0) {
            dot = 0;
        }
        if ((long long)self.x * other.z - (long long)self.z * other.x < 0) {
            ScaleVec3Fx12(-0x1000, &side, &side);
        }
        blend.x = (int)(((long long)flat.x * dot + (long long)side.x * (0x1000 - dot) + 0x800) >> 12);
        blend.z = (int)(((long long)flat.z * dot + (long long)side.z * (0x1000 - dot) + 0x800) >> 12);
        Quat_FromTwoVectors((Quat *)(state + 0xb), &data_02042258, &blend);
    } else {
        QuatFromAxisAngle((Quat *)(state + 0xb), &data_02042264, FX_Atan2(d.x, d.z));
    }
    s = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3a8), &step);
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
