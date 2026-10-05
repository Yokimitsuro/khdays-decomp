/*
 * Ov282_StrafeSameTargetTimed -- x3 (ov210/211/282). AI-state tick: strafe the same target on a timer, fire.
 * If the freshly acquired target no longer matches cached state[4], mark *state[0]+0x1c7=2 and bail.
 * Else dir = normalise(flatten_y(state[4](+0x190) - state[1])); state[0xa] = atan2(dir.x, dir.z);
 * state[5..7] = data_02042264 x dir scaled 0x100. Advance timer state[0xb] += owner_delta; while it
 * stays under state[0xc], return. Once past: fire attack 0x14 (020c9264) and hand off to the 020d2d38
 * state.
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
extern void Ov282_AimPerpStrafe(void);

void Ov282_StrafeSameTargetTimed(int *self) {
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
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] < state[0xc]) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0x14, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov282_AimPerpStrafe);
}
