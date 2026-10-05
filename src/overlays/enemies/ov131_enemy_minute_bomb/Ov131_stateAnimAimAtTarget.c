/* AI step: posts pose 3, turns towards the target and continues with decelerating. */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov131_AiDecelUntilFlagClear(void);

void Ov131_stateAnimAimAtTarget(char *obj) {
    int *state = *(int **)(obj + 4);
    int v[3];
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    if (state[0xe] != 0) {
        int a;
        VEC_Subtract((void *)(state[0xe] + 0x190), (void *)(*state + 0xb0), v);
        a = FX_Atan2(v[0], v[2]);
        state[4] = a;
        state[3] = a;
    }
    SetIndexedSlot(obj, *(signed char *)(obj + 0x20), Ov131_AiDecelUntilFlagClear);
}
