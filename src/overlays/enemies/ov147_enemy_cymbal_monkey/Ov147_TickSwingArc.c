/* Per-frame step for the swinging-weapon enemy, on top of the base step at Obj_RenderModel. First
 * half samples a joint: NNS_G3dGetResultMtx fetches the matrix for joint index +0x3d0, and words 9..11 of
 * that 12-word block are its translation column (it is a MtxFx43, so the last row IS the position).
 * The sampled point is stored at +0x3a4, and while the 'restart' flag at +0x3e4 is clear the
 * per-frame DELTA is written to +0x3b0 first -- VEC_Subtract(new, +0x3a4, +0x3b0) is dst = new -
 * previous. That pair is a position and its velocity, sampled off the skeleton. Second half only
 * runs while the guard byte at +0xad is clear, and only for animation ids 0 and 1: it flips the
 * swing. The turn rate at +0x3bc keeps its sign but takes magnitude 0x244d when the target is
 * within 0x4800 of the actor and 0x10c1 beyond that -- it turns HARDER up close. The rate is then
 * negated (that is the flip) and QuatFromAxisAngle rebuilds the rotation at +0x3c0 about the fixed
 * axis data_02042264 by the new angle. Either way it ends by zeroing +0x3a4 and +0x3b0 and raising
 * the restart flag, so the next sample starts a fresh arc rather than differencing across the
 * discontinuity. */

#include "nitro/fx_types.h"

extern void Obj_RenderModel();
extern int NNS_G3dGetResultMtx();
extern void VEC_Subtract();
extern int VEC_Normalize();
extern void SetSubitemState();
extern void QuatFromAxisAngle();
extern VecFx32 data_02042264;
extern VecFx32 data_02041dc8;

void Ov147_TickSwingArc(int self, int a, int b, int c)
{
    int o = *(int *)(self + 0x84);
    int buf[12];
    VecFx32 tmp;
    VecFx32 dir;
    int n;

    Obj_RenderModel(self, a, b, c);

    if (NNS_G3dGetResultMtx(*(int *)(self + 0x88) + 0x20, buf, 0,
                      *(unsigned int *)(o + 0x3d0)) != 0) {
        tmp = *(VecFx32 *)&buf[9];

        if (*(int *)(o + 0x3e4) == 0) {
            VEC_Subtract(&tmp, o + 0x3a4, o + 0x3b0);
        }

        *(VecFx32 *)(o + 0x3a4) = tmp;
        *(int *)(o + 0x3e4) = 0;
    }

    if (*(unsigned char *)(self + 0xad) == 0) {
        int k = *(short *)(*(int *)(self + 0x88) + 2);

        if (k != 0 && k != 1) {
            goto skip;
        }

        if (*(int *)(o + 0x3e8) != 0) {
            if (*(int *)(o + 0x394) != 0) {
                VEC_Subtract(*(int *)(o + 0x394) + 400, o + 0xb0, &dir);

                if (VEC_Normalize(&dir, &dir) <= 0x4800) {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x244d : -0x244d;
                } else {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x10c1 : -0x10c1;
                }
            }

            SetSubitemState(self, 0, k, 0);

            n = *(int *)(o + 0x3bc);
            n *= -1;

            *(int *)(o + 0x3bc) = n;

            QuatFromAxisAngle(o + 0x3c0, &data_02042264, n);
        }

skip:
        ;

        {
            VecFx32 z = data_02041dc8;

            *(VecFx32 *)(o + 0x3a4) = z;
            *(VecFx32 *)(o + 0x3b0) = z;
        }

        *(int *)(o + 0x3e4) = 1;
    }
}
