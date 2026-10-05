/* State step: posts pose 3, faces the target when one is set, starts the action resource's
 * animation and installs the offset-tracking step. */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov152_AiTrackOffsetUntilLanded(void);

void Ov152_Pose3AimYawAdvance(int *node) {
    int *state = (int *)node[1];
    int local[3];
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    if (state[0xf] != 0) {
        VEC_Subtract((void *)(state[0xf] + 0x190), (void *)state[0x10], local);
        int r = FX_Atan2(local[0], local[2]);
        state[3] = r;
        state[2] = r;
    }
    Ov107_StartAnim(*(int *)(*state + 0x3cc), 0, 0);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov152_AiTrackOffsetUntilLanded);
}
