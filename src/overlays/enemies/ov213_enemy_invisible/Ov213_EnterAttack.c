/* Attack entry: sets the +0x48 rate to 30/5 of the frame step, plays pose 4, clears the +0x6a
 * latch and +0x70 timer, re-acquires the lock-on target into +0x24 and, when one exists, builds
 * the aim pose at +0x38 from data_02042264 and atan2 of the flattened, normalised direction from
 * the +4 anchor to the target's +0x74 position (data_02042258 when degenerate); then moves the
 * node to 020cf768. */

#include "game/enemy_common.h"
#include "game/engine.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Normalize(void *v, void *out);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov213_WindupTickA(void);
extern int  data_02042258;
extern int  data_02042264;
struct v3 { int a, b, c; };

void Ov213_EnterAttack(int *self) {
    int *state = (int *)self[1];
    int target;
    struct v3 v;

    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 5;
    Ov107_PostTagUpdate((Actor *)(*state), 4, 0);
    *((unsigned char *)state + 0x6a) = 0;
    state[0x1c] = 0;
    target = Ov107_FindNearestObject(*state, 0);
    state[9] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)state[1], &v);
        v.b = 0;
        if (VEC_Normalize(&v, &v) == 0) {
            v = *(struct v3 *)&data_02042258;
        }
        QuatFromAxisAngle((void *)(state + 0xe), &data_02042264, FX_Atan2(v.a, v.c));
    }
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov213_WindupTickA);
}
