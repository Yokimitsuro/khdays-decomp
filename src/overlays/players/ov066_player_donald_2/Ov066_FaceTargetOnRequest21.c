/* State 0x21 handler: sends the attack command for the variant, faces the locked target (turning
 * the display object once) and returns the panel update step. */

#include "nitro/fx_types.h"

extern void Ov066_PanelUpdate(void);
extern int Ov022_ValidateTargetRef(int self);
extern int func_ov022_020ad0c0(int self);
extern void VEC_Subtract(int a, int b, void *out);
extern int VEC_Mag(void *v);
extern void VEC_Normalize(void *a, void *b);
extern int FX_Atan2Idx(int y, int x);

void *Ov066_FaceTargetOnRequest21(int self, int req) {
    VecFx32 d;
    void *cb = 0;
    char *blk = (char *)(self + 0xc50);
    int *flag = (int *)(blk + 0x2000);
    if (req == 0x21) {
        cb = (void *)&Ov066_PanelUpdate;
        if (*flag != 0) {
            (*(void (**)(int, int))(self + 0x664))(self, 0x31);
        } else {
            (*(void (**)(int, int))(self + 0x664))(self, 0x30);
        }
        if (Ov022_ValidateTargetRef(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), self + 0x8c + 0x400, &d);
            if (VEC_Mag(&d) != 0) {
                VEC_Normalize(&d, &d);
            }
            {
                unsigned short ang = (unsigned short)FX_Atan2Idx(-d.x, -d.z);
                int *n = *(int **)(self + 0x20);
                if ((*n & 0x20) == 0) {
                    *(unsigned short *)((char *)n + 0x80) = ang + 0x8000;
                    *(unsigned short *)((char *)n + 4) |= 0x20;
                }
            }
        }
    }
    return cb;
}
