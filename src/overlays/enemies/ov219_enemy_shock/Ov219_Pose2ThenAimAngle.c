/* AI step: posts pose 2, sends the attack update when armed, turns towards the target and
 * continues. */

#include "game/enemy_common.h"

extern void Ov107_BuildAndSendUpdate(int a, int b, int c, int d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov219_ConfigSubStateThenAdvanceSlot(void);

void Ov219_Pose2ThenAimAngle(int *node) {
    int *state = (int *)node[1];
    int v[3];
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0x14] != 0) {
        Ov107_BuildAndSendUpdate(*state, 0x136, 6, state[2]);
    }
    if (state[0x10] != 0) {
        int r;
        VEC_Subtract((void *)(state[0x10] + 0x190), (void *)(*state + 0xb0), v);
        r = FX_Atan2(v[0], v[2]);
        state[4] = r;
        state[3] = r;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov219_ConfigSubStateThenAdvanceSlot);
}
