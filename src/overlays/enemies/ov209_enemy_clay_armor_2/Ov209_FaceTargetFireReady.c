/*
 * Ov209_FaceTargetFireReady -- x3 (ov208/209/268). AI-state tick: face the cached target, fire attack 0xa
 * once the owner ready-byte clears.
 * state[0x18] = owner_delta*30/10; dir = target(state[4]+0x190) - state[2]; state[0xd] =
 * atan2(dir.x, dir.z). While the ready byte *(u8)(state[1]+0xad) is set, return; once clear fire
 * attack 0xa (020c9264) and hand off to the 020d20c0 state.
 */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov209_FaceTargetFireReadyB(void);

void Ov209_FaceTargetFireReady(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], v);
    state[0xd] = FX_Atan2(v[0], v[2]);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0xa, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov209_FaceTargetFireReadyB);
}
