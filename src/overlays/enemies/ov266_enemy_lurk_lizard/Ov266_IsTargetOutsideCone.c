/* "Is the target outside the facing cone?" (and its byte-identical twins). With no target,
 * answer no. Otherwise take the heading from the anchor (ctx[2]) to the target
 * (target+0x190) FLATTENED to the XZ plane, turn it into a Q12-radian angle, and
 * compare it against the stored heading (ctx+0x34): convert both to sin/cos table
 * entries and dot them, which is cos(measured - stored); acos that (0203cd20) and
 * report whether the absolute difference exceeds 0x1ac (~24 degrees).
 *
 * Two spellings are load-bearing:
 *  - The guard must be written as `if (tgt != 0) { ...; return ...; } return 0;`.
 *    The natural `if (tgt == 0) return 0;` makes mwcc predicate the early exit
 *    inline (addeq/moveq/popeq, 1 instruction short); the ROM branches to a shared
 *    out-of-line `return 0` at the end.
 *  - `d.y = 0` is a DEAD store -- d is never read again after d.x/d.z -- but the ROM
 *    emits it, so it stays. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int *Ov107_FindNearestObject(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int a, int b);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

int Ov266_IsTargetOutsideCone(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    VecFx32 d;
    int *tgt = Ov107_FindNearestObject(*ctx, 0);
    unsigned int ia, im;
    int a, ang;

    if (tgt != 0) {
        VEC_Subtract((char *)tgt + 0x190, (void *)ctx[2], &d);
        d.y = 0;
        a = FX_Atan2(d.x, d.z);
        ia = ANG2IDX(ctx[0xd]);
        im = ANG2IDX(a);
        ang = Fx_Acos(FX_MUL(data_0203d210[im * 2], data_0203d210[ia * 2]) +
                            FX_MUL(data_0203d210[im * 2 + 1], data_0203d210[ia * 2 + 1]));
        if (ang < 0) {
            ang = -ang;
        }
        return ang > 0x1ac;
    }
    return 0;
}
