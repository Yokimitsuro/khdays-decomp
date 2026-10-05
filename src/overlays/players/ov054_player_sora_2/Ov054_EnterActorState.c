/* state entry for this boss: per message the flags/animation setup and the step function handed
 * back (0x21 -> Ov054_StepRiseState, 0x22 -> Ov054_VolleyStep). */

#include "nitro/fx_types.h"

extern int Ov022_IsSlotReady(unsigned int *obj);
extern int *Anim_SetFrameWrapped(int node, int index, int value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern char *data_ov054_020b74a0;
extern void Ov054_StepRiseState(void);
extern void Ov054_VolleyStep(void);

void *Ov054_EnterActorState(char *self, int msg) {
    char *blk = data_ov054_020b74a0 + 0x2ca4;
    void *next = 0;
    VecFx32 delta;
    unsigned short angle;
    int *node;

    switch (msg) {
    case 0x21:
        *(int *)(blk + 8) = 0;
        if (Ov022_IsSlotReady((unsigned int *)(self + 0x22f8)) == 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
            node = *(int **)(self + 0x20);
            Anim_SetFrameWrapped((int)(node + 1), 0, 0xf000);
            *(int *)(self + 0x7b0) = 0xf000;
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        if (Ov022_ValidateTargetRef(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (const VecFx32 *)(self + 0x48c), &delta);
            delta.y = 0;
            if (VEC_Mag(&delta) != 0)
                VEC_Normalize(&delta, &delta);
            angle = (unsigned short)FX_Atan2Idx(-delta.x, -delta.z);
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = angle + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        next = (void *)&Ov054_StepRiseState;
        break;
    case 0x22:
        *(int *)(blk + 4) = 0;
        *(unsigned char *)(blk + 0xc) = 0;
        if (*(int *)blk == 0) {
            *(unsigned char *)(blk + 0xd) = *(int *)(blk + 8) == 2 ? 6 : 3;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            *(unsigned char *)(blk + 0xd) = 1;
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        }
        next = (void *)&Ov054_VolleyStep;
        break;
    }
    return next;
}
