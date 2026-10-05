/* AI step: advances the timer by the owner's frame step until it passes 0x6ee; then acquires the
 * nearest target and faces it, clears flags 0x82 in the high byte of the actor's flags, posts pose
 * 0 and installs the next step. */

#include "game/enemy_common.h"

struct hw { unsigned short lo:8, hi:8; };

extern int Ov107_FindNearestObject(int a, int b);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int a, int b);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void Ov132_AiRollTimerQueue2(void);

void Ov132_stAdvanceTimerAimTarget(int *param_1) {
    int *state = (int *)param_1[1];
    int sp[3];
    int acc = state[0xc] + *(int *)(*param_1 + 0x2c);
    state[0xc] = acc;
    if (acc < 0x6ee) return;
    {
        int target = Ov107_FindNearestObject(*state, 0);
        state[2] = target;
        if (target != 0) {
            int angle;
            VEC_Subtract((void *)(target + 0x74), (void *)state[0x11], sp);
            angle = FX_Atan2(sp[0], sp[2]);
            state[4] = angle;
            state[3] = angle;
        }
    }
    ((struct hw *)(*state + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)(*state), 0, 0);
    SetIndexedSlot((int)param_1, *(signed char *)((int)param_1 + 0x20), &Ov132_AiRollTimerQueue2);
}
