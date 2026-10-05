/* State step: posts pose 3, faces the target when one is set and installs the decelerate step. */

#include "game/enemy_common.h"

extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov132_AiDecelUntilFlagClear(void);
void Ov132_stateAnimAimAtTarget(int *node) {
    int *state = (int *)node[1];
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    if (state[0xe] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[0xe] + 0x190, *state + 0xb0, buf);
        a = FX_Atan2(buf[0], buf[2]);
        state[4] = a;
        state[3] = a;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov132_AiDecelUntilFlagClear);
}
