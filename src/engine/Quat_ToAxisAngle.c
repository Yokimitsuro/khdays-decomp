
#include "nitro/fx_types.h"

typedef struct Quat {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quat;

extern int FX_Sqrt(int x);
extern fx16 FX_Atan2(int x, int z);
extern long long FX_InvFx64c(int x);

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

/*
 * Quat_ToAxisAngle -- quaternion to axis-angle: given a unit quaternion q = {w, x, y, z},
 * writes the (unnormalized-length) rotation axis to *axis and the rotation angle
 * (in Q12 fixed-point radians) to *angle.
 *
 * magSq is the squared length of the vector part (x, y, z). If it is zero the
 * rotation is identity: angle = 0, axis = (FX32_ONE, 0, 0).
 * Otherwise the half-angle is recovered from w: w <= -1 clamps to PI, w >= 1
 * clamps to 0, otherwise half = atan2(sqrt(1 - w*w), w) via FX_Atan2. The
 * full angle is 2 * half. axis is (x, y, z) scaled by 1/|xyz| (FX_InvFx64c's
 * 64-bit reciprocal), each component rounded via the standard
 * (recip * v + 0x80000000) >> 32 idiom.
 */
void Quat_ToAxisAngle(VecFx32 *axis, int *angle, Quat *q)
{
    int magSq = FX_Mul(q->x, q->x) + FX_Mul(q->y, q->y) + FX_Mul(q->z, q->z);

    if (magSq != 0) {
        int half;
        fx32 w = q->w;

        if (w > -0x1000) {
            if (w < 0x1000) {
                int sinHalf = FX_Sqrt(FX_Mul(0x1000 - w, 0x1000 + w));
                half = FX_Atan2(sinHalf, w);
            } else {
                half = 0;
            }
        } else {
            half = 0x3244; /* PI in Q12 */
        }
        *angle = half << 1;

        {
            long long recip = FX_InvFx64c(FX_Sqrt(magSq));
            axis->x = (int)((recip * q->x + 0x80000000LL) >> 32);
            axis->y = (int)((recip * q->y + 0x80000000LL) >> 32);
            axis->z = (int)((recip * q->z + 0x80000000LL) >> 32);
        }
    } else {
        *angle = 0;
        axis->x = 0x1000;
        axis->y = 0;
        axis->z = 0;
    }
}
