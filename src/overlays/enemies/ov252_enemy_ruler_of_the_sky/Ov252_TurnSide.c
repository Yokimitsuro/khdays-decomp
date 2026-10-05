/* Side of the ov252 actor that the ground-plane vector `v` points to: 0 when it is within the facing
 * cone (turn below 0x1a87) or shorter than twice the actor's +0x80 radius, else 2 for a turn to one
 * side and 1 for the other (turn from the +0x54 heading, 0203cd20). */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

u8 Ov252_TurnSide(int *state, VecFx32 v)
{
    int a = FX_Atan2(v.x, v.z);
    unsigned int ia = ANG2IDX(state[0x15]);
    unsigned int im = ANG2IDX(a);
    int turn = Fx_Acos(FX_MUL(data_0203d210[im * 2], data_0203d210[ia * 2]) +
                             FX_MUL(data_0203d210[im * 2 + 1], data_0203d210[ia * 2 + 1]));
    int mag = turn < 0 ? -turn : turn;

    if (mag < 0x1a87 || (state = (int *)*state, VEC_Normalize(&v, &v) < state[0x20] * 2)) {
        return 0;
    }
    return turn >= 0 ? 2 : 1;
}
