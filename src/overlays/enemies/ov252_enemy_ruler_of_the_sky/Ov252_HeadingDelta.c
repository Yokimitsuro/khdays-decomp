/* Angle between the `dir` heading and `angle` (0203cd20 of the dot product of their unit vectors),
 * made positive when `absolute` is set. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern fx16 FX_Atan2(int x, int z);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

int Ov252_HeadingDelta(int *node, VecFx32 *dir, int angle, int absolute)
{
    int heading = FX_Atan2(dir->x, dir->z);
    int ia = ANG2IDX(angle) * 2;
    int ih = ANG2IDX(heading) * 2;
    int diff = Fx_Acos(FX_MUL(data_0203d210[ih], data_0203d210[ia]) +
                             FX_MUL(data_0203d210[ih + 1], data_0203d210[ia + 1]));
    int mag = diff < 0 ? -diff : diff;

    return absolute == 0 ? diff : mag;
}
