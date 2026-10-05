/*
 * Ov210_StrafeSameTargetNeg -- x3 (ov210/211/282). Twin of Ov210_StrafeSameTarget (020d2b60) with the cross
 * product scaled by -0x100, attack 0x10, and the 020d2f5c continuation.
 */

#include "game/enemy_common.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *c);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern int  data_02042264;
extern void Ov210_StrafeSameTargetTimedNeg(void);

void Ov210_StrafeSameTargetNeg(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target = Ov107_FindNearestObject(*state, 0);

    if (state[4] != target) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], v);
    v[1] = 0;
    VEC_Normalize(v, v);
    state[0xa] = FX_Atan2(v[0], v[2]);
    VEC_CrossProduct(&data_02042264, v, (void *)(state + 5));
    ScaleVec3Fx12(-0x100, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x10, 1);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov210_StrafeSameTargetTimedNeg);
}
