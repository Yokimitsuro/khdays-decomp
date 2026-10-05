/*
 * Ov268_FaceTargetFireReadyB -- x3 (ov208/209/268). Twin of Ov208_FaceTargetFireReady (020d2024) with
 * attack 3 and the 020d215c continuation.
 */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov268_FireRangedShot(void);

void Ov268_FaceTargetFireReadyB(int *self) {
    int *state = (int *)self[1];
    int v[3];

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], v);
    state[0xd] = FX_Atan2(v[0], v[2]);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov268_FireRangedShot);
}
