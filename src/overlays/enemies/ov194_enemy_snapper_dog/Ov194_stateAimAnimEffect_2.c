/* State step: derives the speed from the owner's frame step, aims at the nearest target, posts a
 * pose, starts the effect animation and installs the spin-and-retreat step. */

#include "game/enemy_common.h"

extern int Ov107_FindNearestObject();
extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov194_TickSpinRetreat(void);
void Ov194_stateAimAnimEffect_2(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[5] = v / 3;
    }
    {
        int t = Ov107_FindNearestObject(*state, 0);
        state[2] = t;
        if (t != 0) {
            VEC_Subtract(t + 0x190, *state + 0xb0, buf);
            state[4] = FX_Atan2(buf[0], buf[2]);
        }
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0xb, 0);
    Ov107_StartAnim(*(int *)(*state + 0x3d0), 3, 0);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov194_TickSpinRetreat);
}
