/*
 * Ov274_FireAttack2OnIdle -- x4 (ov206/207/274/275). AI-state tick: acquire the target, wind up, then
 * fire attack 2 once the sub-node at state[3] goes idle.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/20;
 * state[0x11] = atan2(dir.x, dir.z); seed state[5..7] from const vec3 data_02041dc8. While the
 * sub-node byte *(char*)state[3] is still set, return. Once idle: fire attack 2 (020c9264, flag 1)
 * and hand off to the 020ce1c8 continuation via 0203c634.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern void Ov274_FaceTargetAndGate(void);
extern int  data_02041dc8;

void Ov274_FireAttack2OnIdle(int *self) {
    int *state = (int *)self[1];
    VecFx32 v;
    int target;

    target = Ov107_FindNearestObject(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    VEC_Normalize(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 0x1e / 20;
    state[0x11] = FX_Atan2(v.x, v.z);
    *(VecFx32 *)(state + 5) = *(VecFx32 *)&data_02041dc8;
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 2, 1);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov274_FaceTargetAndGate);
}
