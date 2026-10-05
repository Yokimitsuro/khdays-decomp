/*
 * Message handler: 0x21 resets the counter and reports 0x2f; 0x22 runs the launch -- notify,
 * reset the node, set the speed word at +0x7b0 to 0x27000, raise the 64-bit flag pair at +0,
 * set the turn rate at +0x64, and re-aim at the partner.
 *
 * THE 64-BIT OR.  The ROM's `orr rN, rN, #0` is not a no-op and not a macro artifact: it is
 * the HIGH HALF of a 64-bit OR on a pair of adjacent flag words.  `*(long long *)(p) |= mask`
 * emits exactly two loads, `orr` low with the mask, `orr` high with zero, two stores.
 * Everything else tried on this -- plain `|= 0`, volatile `|= 0`, explicit `*p = *p | 0`,
 * volatile pointer locals -- recovers the load and the store but never the orr, because there
 * is no `| 0` in the source to preserve.  It also explains the second oddity: the two-step
 * base (`add r0, r5, #0x64` then `[r0, #0x404]`) is just how mwcc addresses the high half,
 * not a separate source construct.
 */

#include "nitro/fx_types.h"

extern void Ov022_FillEightHalvesMinus1At0x2bd4(char *self);
extern void Anim_SetFrameWrapped(char *p, int i, int v);
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern char *data_ov037_020b4e20;
extern void Ov037_ApproachStep(void);
extern void Ov037_ChargeStep(void);

void *Ov037_HandleMsgAndLaunch(char *self, int msg) {
    char *blk = data_ov037_020b4e20 + 0x2c + 0x2c00;
    void *next = 0;
    VecFx32 d;
    unsigned short a;
    int *node;

    switch (msg) {
    case 0x21:
        *(int *)(blk + 0x110) = 0;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        next = (void *)&Ov037_ApproachStep;
        break;
    case 0x22:
        next = (void *)&Ov037_ChargeStep;
        Ov022_FillEightHalvesMinus1At0x2bd4(self);
        (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        Anim_SetFrameWrapped(*(char **)(self + 0x20) + 4, 0, 0x27000);
        *(int *)(self + 0x7b0) = 0x27000;
        *(long long *)self |= 0x20000000;
        *(unsigned short *)(self + 0x64) = 0x1800;
        if (Ov022_ValidateTargetRef(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (const VecFx32 *)(self + 0x48c), &d);
            if (VEC_Mag(&d) != 0) {
                VEC_Normalize(&d, &d);
            }
            a = (unsigned short)FX_Atan2Idx(-d.x, -d.z);
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    }
    return next;
}
