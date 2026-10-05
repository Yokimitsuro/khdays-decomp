/* Return tick of the ov252 actor: it faces the target (020cdfe8 0, 1) and then turns its +0x58 heading
 * toward the origin from its +8 point; once the partner holds no queued move, with a +0xa0 reward
 * pending the next move is 8, else pose 1 and part motion 0 start and the node moves on to 020cf324. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov252_CheckTarget(int *node, VecFx32 *delta, int face);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov252_HoverTick(void);
extern const VecFx32 data_02041dc8;

void Ov252_ReturnTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    Ov252_CheckTarget(node, 0, 1);
    VEC_Subtract(&data_02041dc8, (VecFx32 *)state[2], &d);
    d.y = 0;
    VEC_Normalize(&d, &d);
    state[0x16] = FX_Atan2(d.x, d.z);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x28] != 0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        Ov107_PostTagUpdate((Actor *)(*state), 1, 0);
        Ov107_StartAnim(*(int *)(*state + 0x574), 0, 0);
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov252_HoverTick);
    }
}
