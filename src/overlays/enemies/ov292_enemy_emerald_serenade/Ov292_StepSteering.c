/* Per-frame steering step for the ov292 actor's sub-state.
 *
 * Faces the target, builds the rotation from the flat heading, and works out a
 * speed: a base of 0x780 reduced in proportion to the hit points still left,
 * scaled by how squarely the actor already faces the target (the dot product,
 * doubled and clamped into [0x200, 0x1000]), scaled again by the stored
 * throttle and floored at 0x3c0. The throttle then ramps up by 0xc0 a frame,
 * clamped into [0, 0x1000].
 *
 * When the owner has a lap count it also checks arrival: once the flat distance
 * to the target drops below the speed, the step zeroes the velocity, advances
 * the point index modulo the lap count, and walks the point list to the new
 * index. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx16 FX_Atan2(int x, int z);
extern long long func_02020400(int num, int den);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void *List_First(void *list);

extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;

void Ov292_StepSteering(char *state)
{
    VecFx32 vToTarget;
    VecFx32 vFacing;
    VecFx32 vFlat;
    char *actor;
    int nSpeed;
    int nAim;
    int i;
    VecFx32 *point;

    actor = *(char **)state;
    VEC_Subtract((VecFx32 *)(state + 0x1c), *(VecFx32 **)(state + 8),
                 &vToTarget);
    VEC_Normalize(&vToTarget, &vToTarget);
    QuatFromAxisAngle(state + 0x48, &data_02042264,
                  FX_Atan2(vToTarget.x, vToTarget.z));
    Vec3TransformViaTempMtx(&vFacing, *(char **)state + 0xa0, &data_02042258);

    nSpeed = 0x780;
    if (*(short *)(actor + 0x218) != 0) {
        nSpeed = nSpeed - (int)func_02020400(*(short *)(actor + 0x21a) * 0x500,
                                             *(short *)(actor + 0x218));
    }

    nAim = VEC_DotProduct(&vToTarget, &vFacing) * 2;
    if (nAim > 0x1000) {
        nAim = 0x1000;
    } else if (nAim < 0x200) {
        nAim = 0x200;
    }
    nSpeed = (int)(((long long)nSpeed * nAim + 0x800) >> 12);
    nSpeed = (int)(((long long)nSpeed * *(int *)(state + 0x30) + 0x800) >> 12);
    if (nSpeed < 0x3c0) {
        nSpeed = 0x3c0;
    }
    ScaleVec3Fx12(nSpeed, &vToTarget, (VecFx32 *)(state + 0x10));

    nAim = *(int *)(state + 0x30) + 0xc0;
    if (nAim > 0x1000) {
        nAim = 0x1000;
    } else if (nAim < 0) {
        nAim = 0;
    }
    *(int *)(state + 0x30) = nAim;

    if (*(int *)(*(char **)state + 0x3b4) == 0) {
        return;
    }

    VEC_Subtract((VecFx32 *)(state + 0x1c), *(VecFx32 **)(state + 8),
                 &vFlat);
    vFlat.y = 0;
    if (VEC_Normalize(&vFlat, &vFlat) >= nSpeed) {
        return;
    }

    VEC_Subtract((VecFx32 *)(state + 0x1c), *(VecFx32 **)(state + 8),
                 (VecFx32 *)(state + 0x10));
    *(int *)(state + 0x34) = (int)((u64)func_02020400(*(int *)(state + 0x34) + 1,
                                                      *(int *)(*(char **)state + 0x3b4)) >> 32);

    point = List_First(*(char **)state + 0x394);
    i = 0;
    while (point != 0) {
        *(VecFx32 *)(state + 0x1c) = *point;
        if (i >= *(int *)(state + 0x34)) {
            return;
        }
        point = (VecFx32 *)List_Next(*(char **)state + 0x394);
        i++;
    }
}
