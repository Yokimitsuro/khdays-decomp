/* Turn entry of the ov298 enemy: half the time the +0x28 turn is rolled (0x1922 to 0x3243), the
 * target gap measured and the +0x30 target yaw aimed from the actor at its +0x394 target plus
 * the turn; animation 8 plays, the +0x90 flag is set, bit 0 of the +0x38c part's +8 word is set,
 * reaction 0 mode 0x43 fires at the +8 point and the tick hands off to d51fc. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct LowByte32 { unsigned bits : 8; };

extern int Ov298_AcquireTargetGapAndAngle(void *node);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate(int actor, int a, int b, void *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov298_ForwardThenEnterSubState4(int *node);

void Ov298_TurnEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if ((unsigned int)RandNextScaled(0x64) < 0x32) {
        state[10] = Rand16NextScaled(0x1922) + 0x1922;
        Ov298_AcquireTargetGapAndAngle(node);
        VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x74), (void *)(*state + 0x74), &d);
        VEC_Normalize(&d, &d);
        state[0xc] = FX_Atan2(d.x, d.z);
        state[0xc] += state[10];
    }
    Ov107_PostTagUpdate((Actor *)(*state), 8, 0);
    state[0x24] = 1;
    ((struct LowByte32 *)(*(int *)(*state + 0x38c) + 8))->bits |= 1;
    Ov107_BuildAndSendUpdate(*state, 0, 0x43, (void *)state[2]);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov298_ForwardThenEnterSubState4);
}
