/* State step: posts a pose and, when a target is set, turns the heading toward it; installs the
 * eased-pose step. */

#include "game/enemy_common.h"

extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov250_stEasePoseCheckFlags(void);
void Ov250_stateAnimAimAtTarget(int *node) {
    int *state = (int *)node[1];
    Ov107_PostTagUpdate((Actor *)(*state), 8, 0);
    if (state[9] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[9] + 0x190, state[1], buf);
        a = FX_Atan2(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov250_stEasePoseCheckFlags);
}
