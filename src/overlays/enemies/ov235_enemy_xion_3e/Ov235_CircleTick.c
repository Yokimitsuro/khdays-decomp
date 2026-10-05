/* Circle tick of an ov235 state: the +0x40 rate is the frame rate x 1.5 and the nearest target
 * (020cab14) becomes +0x5c; with one, the +0x2c orientation turns to face it and the +0x10 step is
 * the +0x3a8 part's travel (020c9f48) turned by the +0x1c orientation. Once the +0xc idle byte
 * clears, a coin flip picks the +0x58 circling direction, animation 0x1b plays, the +0x7c duration
 * is rolled in [0x100, 0x300] and the tick hands over to Ov235_CirclingTick. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int w[4]; } Quat;

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov235_CirclingTick(int *node);
extern const VecFx32 data_02042264;

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + RandNextScaled(d + 1);
}

void Ov235_CircleTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 v;
    VecFx32 d;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 20;
    state[0x17] = Ov107_FindNearestObject(*state, 0);
    if (state[0x17] != 0) {
        VEC_Subtract((void *)(state[0x17] + 0x74), (void *)(*state + 0x74), &d);
        QuatFromAxisAngle((Quat *)(state + 0xb), &data_02042264, FX_Atan2(d.x, d.z));
        speed = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3a8), &v);
        Vec3TransformViaTempMtx(&v, (Quat *)(state + 7), &v);
        ScaleVec3Fx12(speed, &v, (VecFx32 *)(state + 4));
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    state[0x16] = RandRange(0, 1) == 0 ? -1 : 1;
    Ov107_PostTagUpdate((Actor *)(*state), 0x1b, 0);
    state[0x1f] = RandRange(0x100, 0x300);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov235_CirclingTick);
}
