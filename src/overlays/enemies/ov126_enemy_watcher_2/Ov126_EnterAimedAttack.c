/*
 * Ov126_EnterAimedAttack -- AI-state entry: seed the +0x3c counter with 6 times the owner's +0x2c
 * rate (30/5), fire attack 2 (020c9264) and, if a target is set (state[0xc]), aim the pose at
 * state[0x1a..] from data_02042264 and atan2(dir.x, dir.z) of target(+0x190) - *state(+0xb0).
 * Always hand off to the 020cdb28 state.
 */

#include "game/enemy_common.h"
#include "game/engine.h"

extern void VEC_Subtract(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov126_AimedAttackTick(void);
extern int  data_02042264;

void Ov126_EnterAimedAttack(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0xf] = *(int *)(self[0] + 0x2c) * 0x1e / 5;
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0xc] != 0) {
        VEC_Subtract((void *)(state[0xc] + 0x190), (void *)(*state + 0xb0), v);
        QuatFromAxisAngle((void *)(state + 0x1a), &data_02042264, FX_Atan2(v[0], v[2]));
    }
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov126_AimedAttackTick);
}
