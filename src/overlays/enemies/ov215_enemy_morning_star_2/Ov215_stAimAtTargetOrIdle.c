/* State step: without a target queues action 2 and ends the step; otherwise faces it (recording the
 * distance), posts pose 3, sends a state update and installs the next step. */

#include "game/enemy_common.h"

extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Normalize(void *v, void *v2);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate();
extern void Ov215_stEnterSetFlag40(void);

void Ov215_stAimAtTargetOrIdle(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int target = state[2];
    if (target == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 8), (void *)0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), buf);
    buf[1] = 0;
    state[0x12] = VEC_Normalize(buf, buf);
    {
        int angle = FX_Atan2(buf[0], buf[2]);
        state[0x13] = angle;
        state[0x11] = angle;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    Ov107_BuildAndSendUpdate(*state, 0x129, 6, state[4]);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov215_stEnterSetFlag40);
}
