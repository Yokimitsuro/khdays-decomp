/* Knock-back reaction of the ov146 actor (unless +0x1ac bit 0 shields it): an attacker hitting it
 * outside move 1 launches it away along the attacker's heading (020ce694), pose 6 plays, +0x1c is set
 * and the next move is 1. Always returns 0. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov146_Launch(int *state, VecFx32 dir);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int Ov146_OnKnockback(char *self, char *attacker)
{
    int *state = *(int **)(self + 0x214);
    VecFx32 d;
    VecFx32 dir;

    if (*(unsigned short *)(self + 0x1ac) & 1) {
        return 0;
    }
    if (attacker != 0 && *(signed char *)(*state + 0x1c6) != 1) {
        VEC_Subtract((VecFx32 *)(*state + 0xb0), (VecFx32 *)(attacker + 0x190), &d);
        {
            int idx = ANG2IDX(FX_Atan2(d.x, d.z)) * 2;

            dir.y = 0;
            dir.x = data_0203d210[idx];
            dir.z = data_0203d210[idx + 1];
        }
        Ov146_Launch(state, dir);
        Ov107_PostTagUpdate((Actor *)(*state), 6, 0);
        state[7] = 1;
        *(unsigned char *)(*state + 0x1c7) = 1;
    }
    return 0;
}
