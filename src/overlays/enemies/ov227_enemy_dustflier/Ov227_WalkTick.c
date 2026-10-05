/* Walk tick of the ov227 enemy: when the tracking step (Ov227_MeasureTargetGap) reports the target
 * lost the tick ends; otherwise the +0x58 heading faces the +0x38 goal from the +8 point. While the
 * rig is busy (+0xad) the enemy keeps steering along it (Ov227_Steer); once it is free, a
 * d100 below 30 requests move 0x10, the move chooser (Ov227_ChooseMove) may queue another, and
 * otherwise sub-state 2 is requested. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov227_MeasureTargetGap(int *node, VecFx32 *dir);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern int Ov227_ChooseMove(int *node, int dist);
extern void Ov227_Steer(int *node, int rad);

void Ov227_WalkTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int dist;

    dist = Ov227_MeasureTargetGap(node, 0);
    if (dist < 0) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state + 0xe), (void *)state[2], &d);
    state[0x16] = FX_Atan2(d.x, d.z);
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) == 0) {
        if (RandNextScaled(100) < 0x1e) {
            *(signed char *)(*state + 0x1c7) = 0x10;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (Ov227_ChooseMove(node, dist) != 0) {
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    Ov227_Steer(node, state[0x16]);
}
