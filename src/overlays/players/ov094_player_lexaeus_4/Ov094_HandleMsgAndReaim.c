/* Message handler: arm the follow-up state for 0x21 and 0x22, and on 0x22 also re-aim at
 * the partner.
 *
 * Sibling of Ov*_HandleMsgAndFacePartner (328 B, ov046 and company) with one extra step:
 * here the mode at +0x228 selects BOTH the value written to +4 (0, 1, 2) and the code sent
 * to the owner (0x2f, 0x32, 0x30), and there is an additional notify before the aim.
 *
 * Same three levers as that sibling, applied straight from the catalogue and matched on the
 * first compile: both dispatches are SWITCH statements (the ROM jumps to each case, an
 * if-chain falls into the next test and gets predicated), func_ov022_020ad0c0's RETURN
 * VALUE is VEC_Subtract's first argument, and the anchor is self+0x48c reached as one
 * offset even though the ROM splits it into +0x8c and +0x400.
 */

#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *unit);
extern int FX_Atan2Idx(int x, int z);
extern void Ov022_FillEightHalvesMinus1At0x2bd4(char *self);
extern int Ov022_ValidateTargetRef(char *self);
extern VecFx32 *func_ov022_020ad0c0(char *self);
extern char *data_ov094_020bc240;
extern void Ov094_WaitForActionCompletion(void);
extern void Ov094_FinishActionTick(void);

void *Ov094_HandleMsgAndReaim(char *self, int msg) {
    char *blk = data_ov094_020bc240 + 0x2c + 0x2c00;
    void *next = 0;
    VecFx32 d;
    unsigned short a;
    int *node;
    int code;

    switch (msg) {
    case 0x21:
        next = (void *)&Ov094_WaitForActionCompletion;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        break;
    case 0x22:
        next = (void *)&Ov094_FinishActionTick;
        switch (*(int *)(blk + 0x228)) {
        case 2:  *(int *)(blk + 4) = 0; code = 0x2f; break;
        case 3:  *(int *)(blk + 4) = 1; code = 0x32; break;
        case 4:  *(int *)(blk + 4) = 2; code = 0x30; break;
        }
        (*(void (**)(char *, int))(self + 0x664))(self, code);
        Ov022_FillEightHalvesMinus1At0x2bd4(self);
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
