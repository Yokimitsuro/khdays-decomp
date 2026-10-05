/* State step: posts pose 3, faces the target when one is set, starts the action resource's
 * animation and installs the projectile step. */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov142_stAdvanceProjectilePose(void);

void Ov142_stAimAngleToTarget(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    {
        int p = state[0xe];
        if (p != 0) {
            int r;
            VEC_Subtract((void *)(p + 0x190), (void *)(*state + 0xb0), buf);
            r = FX_Atan2(buf[0], buf[2]);
            state[3] = r;
            state[2] = r;
        }
    }
    Ov107_StartAnim(*(int *)(*state + 0x3cc), 0, 0);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov142_stAdvanceProjectilePose);
}
