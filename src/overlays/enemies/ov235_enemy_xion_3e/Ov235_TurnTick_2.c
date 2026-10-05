/* Turn tick of an ov235 state: the nearest target (020cab14) becomes +0x5c and, when there is one,
 * the +0x2c orientation turns to face it (0202f188 about data_02042264). The +0x40 rate is the
 * frame rate x 3; once the +0xc idle byte clears, animation 0x1d plays, the +0x3a8 part plays
 * motion 0x16 and the tick hands over to Ov235_AiEnterGroundAttackB. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int w[4]; } Quat;

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov235_AiEnterGroundAttackB(int *node);
extern const VecFx32 data_02042264;

void Ov235_TurnTick_2(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    state[0x17] = Ov107_FindNearestObject(*state, 0);
    if (state[0x17] != 0) {
        VEC_Subtract((void *)(state[0x17] + 0x74), (void *)(*state + 0x74), &d);
        QuatFromAxisAngle((Quat *)(state + 0xb), &data_02042264, FX_Atan2(d.x, d.z));
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x1d, 0);
    Ov107_StartAnim(*(int *)(*state + 0x3a8), 0x16, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov235_AiEnterGroundAttackB);
}
