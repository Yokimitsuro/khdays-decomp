/* Finds the nearest target and faces it. */

#include "game/enemy_common.h"

struct bf { unsigned b : 8; };
extern int Ov107_FindNearestObject();
extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov277_AiFadeInTick(void);
void Ov277_AiTargetAndFace(int *node) {
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
    *(int *)(*state + 0x390) = 1;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[17] = 0;
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov277_AiFadeInTick);
}
