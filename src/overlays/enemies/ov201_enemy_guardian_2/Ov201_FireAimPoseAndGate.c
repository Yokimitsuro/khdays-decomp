/*
 * Ov201_FireAimPoseAndGate -- x3 (ov200/201/271). AI-state tick: fire, aim the pose at the target, and
 * transition.
 * Fire attack 2 (020c9264). If a target is set (state[0x15]!=0): dir = target(+0x190) - *state(+0xb0);
 * build the aim pose at state[0x25..] from data_02042264 and atan2(dir.x,dir.z) (0202f188), then copy
 * that 4-word pose down to state[0x21..] (field-to-field). Always hand off to the 020cfaec state.
 */

#include "game/enemy_common.h"
#include "game/engine.h"

struct m4 { int w[4]; };
struct S200 { char pad[0x84]; struct m4 dst; struct m4 src; };
extern void VEC_Subtract(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov201_DecayOffsetPickGiveUp(void);
extern int  data_02042264;

void Ov201_FireAimPoseAndGate(int *self) {
    int *state = (int *)self[1];
    int v[3];

    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0x15] != 0) {
        VEC_Subtract((void *)(state[0x15] + 0x190), (void *)(*state + 0xb0), v);
        QuatFromAxisAngle((void *)(state + 0x25), &data_02042264, FX_Atan2(v[0], v[2]));
        ((struct S200 *)state)->dst = ((struct S200 *)state)->src;
    }
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov201_DecayOffsetPickGiveUp);
}
