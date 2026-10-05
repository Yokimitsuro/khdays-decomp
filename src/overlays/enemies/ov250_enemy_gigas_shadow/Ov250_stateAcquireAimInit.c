/* State step: acquires the nearest target and faces it, posts pose 0, sets the alpha to its
 * minimum, sets bit 0 of +0x1ae, clears bit 0 of the model's flag byte, clears the timer and
 * installs the slow fade-in step. */

#include "game/enemy_common.h"

struct bf { unsigned b : 8; };
extern int Ov107_FindNearestObject();
extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov250_AiFadeInSlowTick(void);
void Ov250_stateAcquireAimInit(int *node) {
    int *state = (int *)node[1];
    int t = Ov107_FindNearestObject(*state, 0);
    state[4] = t;
    if (t != 0) {
        int buf[3];
        int a;
        VEC_Subtract(t + 0x190, state[1], buf);
        a = FX_Atan2(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0, 0);
    *(int *)(*state + 0x394) = 1;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[7] = 0;
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov250_AiFadeInSlowTick);
}
