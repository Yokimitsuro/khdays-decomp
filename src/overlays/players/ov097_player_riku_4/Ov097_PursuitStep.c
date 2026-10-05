/*
 * Pursuit step: the per-frame body of the enemy's pursuit state (the ov041 sibling of the
 * approach step at 020b4478).
 *
 * Same skeleton: bit 16 of both 64-bit flag words for the local player, the aim at the target
 * sampler (020ad114/020ad0c0, atan2 of the normalised direction as a u16) written into the model
 * node on every 0x6000 tick unless its bit 5 is set, bit 35 for the local player, the ground
 * sample (falling velocity to +0x58; when grounded without bit 2 of +0x24 the target being live
 * OR bit 36 of the flags sets bit 46 and zeroes +0x58), the horizontal step into +0x498, the
 * rig's +0x660 latch raised by bit 0 of +0x18 and the state callback into bit 1 of +0x694. A
 * raised latch with a finished +0x22f8 channel drops from tick 0x27000 on (020acf14); on ticks
 * 0xc000, 0x18000 and 0x27000 a clear latch ends the state (bit 1) and the latch is reset either
 * way. 020b3a38 then runs the per-tick effects, and the finish/handover tail is the approach
 * step's (chained +0x698 clear in the state-2 arm, bit 16 of +0x46c cleared on handover).
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int FX_Atan2Idx(int y, int x);
extern int Ov022_StepAnchorDelta(char *self, void *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov097_FireTimedBurst(char *self);
extern int Ov022_IsState9Or6WithFlag200(char *chan);
extern void func_ov022_020acf14(char *self, int a);
extern void *Ov022_ActorSetState(char *self, int state);

void *Ov097_PursuitStep(char *self)
{
    int r;
    VecFx32 sample;
    VecFx32 dir;
    VecFx32 step;
    void *next = 0;
    char *rig = self + 0x84 + 0x2c00;
    int angle = -1;
    unsigned int *node;

    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (Ov022_ValidateTargetRef(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), (VecFx32 *)(self + 0x8c + 0x400), &dir);
        if (VEC_Mag(&dir) != 0) {
            VEC_Normalize(&dir, &dir);
        }
        angle = (u16)FX_Atan2Idx(-dir.x, -dir.z);
    }
    if (*(int *)(self + 0x7b0) % 0x6000 == 0 && angle != -1) {
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = angle + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
    }
    if (Session_GetLocalPlayerIndex() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x800000000ULL;
    }
    Ov022_StepAnchorDelta(self, &sample);
    if (sample.y != 0) {
        *(int *)(self + 0x58) = sample.y;
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        if (Ov022_ValidateTargetRef(self) != 0 || (*(unsigned long long *)self & 0x1000000000ULL) != 0) {
            *(unsigned long long *)self |= 0x400000000000ULL;
            *(int *)(self + 0x58) = 0;
        }
    }
    step = sample;
    step.y = 0;
    VEC_Add((VecFx32 *)(self + 0x98 + 0x400), &step, (VecFx32 *)(self + 0x98 + 0x400));
    if ((*(u16 *)(self + 0x18) & 1) != 0) {
        *(int *)(rig + 0x660) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x660) != 0 && Ov022_IsState9Or6WithFlag200(self + 0x2f8 + 0x2000) != 0
        && *(int *)(self + 0x7b0) >= 0x27000) {
        *(int *)(rig + 0x660) = 0;
        func_ov022_020acf14(self, 0);
    }
    if (*(int *)(self + 0x7b0) == 0xc000 || *(int *)(self + 0x7b0) == 0x18000
        || *(int *)(self + 0x7b0) == 0x27000) {
        if (*(int *)(rig + 0x660) == 0) {
            ((Flags *)(self + 0x694))->b1 = 1;
        }
        *(int *)(rig + 0x660) = 0;
    }
    Ov097_FireTimedBurst(self);
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
    if ((*(unsigned long long *)(self + 0x464) & 2) != 0) {
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            next = Ov022_ActorSetState(self, 0);
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
        } else {
            *(int *)(self + 0x698) = *(int *)(self + 0x69c) = *(int *)(self + 0x6a0) = 0;
            next = Ov022_ActorSetState(self, 2);
        }
    }
    if (next != 0) {
        *(unsigned long long *)(self + 0x46c) &= ~0x10000ULL;
    }
    return next;
}
