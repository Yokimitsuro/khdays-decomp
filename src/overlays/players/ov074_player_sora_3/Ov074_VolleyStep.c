/* Volley step of the ov035 enemy (x4: ov035/053/073/091): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; before the first shot the node turns to face the target
 * on the ground plane unless the facing is locked; the shared sampler's motion is folded into
 * the position at +0x498 (a vertical component becomes the vertical speed, otherwise -- unless
 * grounded -- bit 46 is raised and the speed cleared); at 0x3000 on the +0x7b0 timer with shots
 * left (rig +0x2cb0 < +0x2cb1) the animation rewinds and bit 29 is raised, and at 0 a shot goes
 * out (the mark or the aimed request by the rig's +0x2ca4 mode) and the count advances. The
 * actor's hook decides bit 1 of +0x694: becoming active raises bit 49, shows the node and, for
 * the local player, sets bit 1 of +0x464; while active the velocities are cleared, bit 2 is
 * raised and the enemy lands (state 0 with the slot callback when grounded, else state 2). */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int Ov022_StepAnchorDelta(char *self, void *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *Ov022_ActorSetState(char *self, int state);
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern void Anim_SetFrameWrapped(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern void Ov074_Weapon_FireSpreadShot(char *self);
extern void Ov074_Weapon_FireStraightShot(char *self);
extern char *data_ov074_020b9b80;

void *Ov074_VolleyStep(char *self)
{
    int r;
    VecFx32 d;
    VecFx32 sample;
    VecFx32 step;
    char *rig = data_ov074_020b9b80 + 0xa4 + 0x2c00;
    void *next = 0;
    unsigned int *node;
    unsigned short a;

    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(signed char *)(rig + 0xc) == 0 && Ov022_ValidateTargetRef(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), (VecFx32 *)(self + 0x8c + 0x400), &d);
        d.y = 0;
        if (VEC_Mag(&d) != 0) {
            VEC_Normalize(&d, &d);
        }
        a = (unsigned short)FX_Atan2Idx(-d.x, -d.z);
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
            *(unsigned short *)((char *)node + 4) |= 0x20;
        }
    }
    Ov022_StepAnchorDelta(self, &sample);
    if (sample.y != 0) {
        *(int *)(self + 0x58) = sample.y;
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((VecFx32 *)(self + 0x98 + 0x400), &step, (VecFx32 *)(self + 0x98 + 0x400));
    if (*(int *)(self + 0x7b0) == 0x3000 && *(signed char *)(rig + 0xc) < *(signed char *)(rig + 0xd)) {
        Anim_SetFrameWrapped(*(char **)(self + 0x20) + 4, 0, 0);
        *(int *)(self + 0x7b0) = 0;
        *(unsigned long long *)self |= 0x20000000;
    }
    if (*(int *)(self + 0x7b0) == 0) {
        if (*(int *)rig == 0) {
            Ov074_Weapon_FireSpreadShot(self);
        } else {
            Ov074_Weapon_FireStraightShot(self);
        }
        *(signed char *)(rig + 0xc) += 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            SceneNode_Enable(node + 1);
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2;
        }
    }
    if (((Flags *)(self + 0x694))->b1) {
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
            next = Ov022_ActorSetState(self, 0);
        } else {
            next = Ov022_ActorSetState(self, 2);
        }
    }
    return next;
}
