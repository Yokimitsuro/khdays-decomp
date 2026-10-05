/*
 * Ov210_StrafeSameTarget -- x3 (ov210/211/282). AI-state tick: keep strafing the same target, fire when
 * the sub-node frees.
 * If the freshly acquired target no longer matches the cached state[4], mark *state[0]+0x1c7=2 and
 * bail (0203c634 cb=0). Else dir = normalise(flatten_y(state[4](+0x190) - state[1]));
 * state[0xa] = atan2(dir.x, dir.z); state[5..7] = data_02042264 x dir (VEC_CrossProduct) scaled 0x100.
 * While the sub-node byte *(u8)state[3] is set keep waiting; else fire attack 0x13 (flag 1) and hand
 * off to the 020d2c44 state.
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
extern void Ov210_StrafeSameTargetTimed(void);

void Ov210_StrafeSameTarget(int *self) {
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
    ScaleVec3Fx12(0x100, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x13, 1);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov210_StrafeSameTargetTimed);
}
