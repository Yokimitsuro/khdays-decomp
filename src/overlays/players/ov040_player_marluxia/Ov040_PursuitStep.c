/* Pursuit step of the ov040 enemy (x4: ov040/059/079/096): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; while flag bit 33 is set the enemy chases at the rig's
 * speed (+0x2d70): without a target it flies straight ahead at half speed, with one it turns to
 * face it (unless the facing is locked) and closes at most the remaining distance, stopping
 * within 0x1800; the vertical part of the step becomes the vertical speed; without bit 33 an
 * airborne enemy raises bit 46 and clears the speed. Past 0x18000 on the +0x4cc counter, or once
 * in range, it hands over to state 0x22. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern int FX_Atan2Idx(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);         /* ScaleVec3Fx12 */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *Ov022_ActorSetState(char *self, int state);
extern char *data_ov040_020b4b20;
extern short data_0203d210[];

void *Ov040_PursuitStep(char *self)
{
    VecFx32 d;
    VecFx32 step;
    VecFx32 flat;
    int speed = *(int *)(data_ov040_020b4b20 + 0x2d70);
    int bClose = 0;
    void *next = 0;
    int dist;
    int idx;
    u16 a;
    unsigned int *node;

    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    step.z = 0;
    step.y = 0;
    step.x = 0;
    d.z = 0;
    d.y = 0;
    d.x = 0;
    if ((*(unsigned long long *)(self + 0x464) & 0x200000000ULL) != 0) {
        *(int *)(self + 0x4b4) = 0x2000;
        if (Ov022_ValidateTargetRef(self) == 0) {
            idx = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
            speed = speed / 2;
            step.x = -data_0203d210[idx * 2];
            step.y = 0;
            step.z = -data_0203d210[idx * 2 + 1];
        } else {
            VEC_Subtract(func_ov022_020ad0c0(self), (VecFx32 *)(self + 0x8c + 0x400), &d);
            dist = VEC_Mag(&d);
            if (dist >= 0x1800) {
                a = (u16)FX_Atan2Idx(-d.x, -d.z);
                node = *(unsigned int **)(self + 0x20);
                if ((*node & 0x20) == 0) {
                    *(u16 *)((char *)node + 0x80) = a + 0x8000;
                    *(u16 *)((char *)node + 4) |= 0x20;
                }
                if (dist < speed) {
                    speed = VEC_Mag(&d);
                }
                if (VEC_Mag(&d) == 0) {
                    step = d;
                } else {
                    VEC_Normalize(&d, &step);
                }
            } else {
                speed = 0;
                bClose = 1;
            }
        }
        ScaleVec3Fx12(speed, &step, &step);
        if (step.y != 0) {
            *(int *)(self + 0x58) = step.y;
        }
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    flat = step;
    flat.y = 0;
    VEC_Add((VecFx32 *)(self + 0x98 + 0x400), &flat, (VecFx32 *)(self + 0x98 + 0x400));
    if (*(int *)(self + 0x4cc) >= 0x18000 || bClose != 0) {
        next = Ov022_ActorSetState(self, 0x22);
    }
    return next;
}
