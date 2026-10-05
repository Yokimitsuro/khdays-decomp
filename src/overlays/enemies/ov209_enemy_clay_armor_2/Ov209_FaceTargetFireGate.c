/*
 * Ov209_FaceTargetFireGate -- x3 (ov208/209/268). AI-state tick: face the target and fire, branching the
 * attack on whether we're aligned.
 * state[0x18] = owner_delta*30/10. Acquire target (020d0ea4) -> state[4]; none -> mark
 * *state[0]+0x1c7=2 and bail (0203c634 cb=0). Else clear state[0xb] and the state+0x49 byte, build a
 * heading vec {sin,0,cos} from state[0xc] (Q12 rad -> sin/cos table, computed inline per component),
 * dir = normalise(target(+0x190) - state[2]); state[0xd] = atan2(dir.x, dir.z). If heading . dir >=
 * 0xf00 fire attack 3 and go to the 020d215c state; else fire attack 9 and go to 020d2024.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int  Ov209_PickBestFacingNode(int obj, void *p);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern int  VEC_DotProduct(void *a, void *b);
extern void Ov209_FireRangedShot(void);
extern void Ov209_FaceTargetFireReady(void);
extern short data_0203d210;

void Ov209_FaceTargetFireGate(int *self) {
    int *state = (int *)self[1];
    VecFx32 v;
    VecFx32 dir;
    int target;

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = Ov209_PickBestFacingNode(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    state[0xb] = 0;
    *(char *)((int)state + 0x49) = 0;
    dir.x = (&data_0203d210)[
        ((unsigned short)((state[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4) * 2];
    dir.y = 0;
    dir.z = (&data_0203d210)[
        ((unsigned short)((state[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4) * 2 + 1];
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[2], &v);
    VEC_Normalize(&v, &v);
    state[0xd] = FX_Atan2(v.x, v.z);
    if (VEC_DotProduct(&dir, &v) >= 0xf00) {
        Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov209_FireRangedShot);
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 9, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov209_FaceTargetFireReady);
}
