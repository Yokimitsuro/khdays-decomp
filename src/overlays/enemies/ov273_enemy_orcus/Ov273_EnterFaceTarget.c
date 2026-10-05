/* Face-target entry: dir = target(+0x3dc)+0x74 - self+0x74 flattened (y = 0) and normalised;
 * builds the aim pose at state+0x38 from data_02042264 and atan2(dir.x, dir.z), copies it down
 * to state+0x28 and, unless the +8 flag byte is set, plays pose 0x17 and hands off to 020ceeb8. */

#include "game/enemy_common.h"
#include "game/engine.h"

struct m4 { int w[4]; };
struct S213 { char pad[0x28]; struct m4 dst; struct m4 src; };
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Normalize(void *v, void *out);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov273_AiEnterSubState9(void);
extern int  data_02042264;

void Ov273_EnterFaceTarget(int *self) {
    int *state = (int *)self[1];
    int v[3];

    VEC_Subtract((void *)(*(int *)(*state + 0x3dc) + 0x74), (void *)(*state + 0x74), v);
    v[1] = 0;
    VEC_Normalize(v, v);
    QuatFromAxisAngle((void *)(state + 0xe), &data_02042264, FX_Atan2(v[0], v[2]));
    ((struct S213 *)state)->dst = ((struct S213 *)state)->src;
    if (*(unsigned char *)state[2] != 0) return;
    Ov107_PostTagUpdate((Actor *)(*state), 0x17, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov273_AiEnterSubState9);
}
