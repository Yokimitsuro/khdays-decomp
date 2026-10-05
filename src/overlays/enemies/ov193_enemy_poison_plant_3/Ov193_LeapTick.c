/* Leap tick of the ov191 enemy (x3: ov191/192/193): re-acquires the target (020d1bdc) and, if
 * any, faces its +0x190 anchor from the +8 position and sets the turn rate (+0x30) to 30x the
 * node's +0x2c speed over 10; the +0x2c phase advances by that speed. At 0x1bbb the ground
 * below the model is probed once (+0x38 latch) into the +0x20 landing point, and between 0x1bbb
 * and 0x22a9 the descent is driven (020d073c) with the 64-bit fraction (phase - 0x1bbb) /
 * (0x1bbb / 4). Once the actor's first byte says the pose is over: bit 0 of the +0x38c item's +8
 * is dropped, the +0x1c counter re-rolled to 2 + rand(5), pose 5 plays, the heading is
 * re-aimed at the target with a random +-0xc90 spread, the phase and latch reset, bit 1 of
 * +0x39 cleared and the follow-up handler (020d190c) installed. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

struct bf { unsigned b : 8; };

extern int Ov193_FindTarget(int obj, int *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov193_ProbeGroundBelowNode(int *node, VecFx32 *out);
extern long long FX_DivFx64c(int num, int denom);
extern void Ov193_BoxSweepPush(int *node, long long t, VecFx32 *at);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void Ov193_ChargeAimedShotState(void);

void Ov193_LeapTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    VecFx32 d2;
    int spread;
    int heading;

    state[6] = Ov193_FindTarget(*state, 0);
    if (state[6] != 0) {
        VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[2], &d);
        state[5] = FX_Atan2(d.x, d.z);
        state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 10;
    }
    state[0xb] += *(int *)(*(int *)node + 0x2c);
    if (*(unsigned char *)(state + 0xe) == 0 && state[0xb] >= 0x1bbb) {
        Ov193_ProbeGroundBelowNode(state, (VecFx32 *)(state + 8));
        *(unsigned char *)(state + 0xe) = 1;
    }
    if (state[0xb] >= 0x1bbb && state[0xb] <= 0x22a9) {
        Ov193_BoxSweepPush(state, FX_DivFx64c(state[0xb] - 0x1bbb, 0x1bbb >> 2), (VecFx32 *)(state + 8));
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    state[7] = RandNextScaled(5) + 2;
    Ov107_PostTagUpdate((Actor *)(*state), 5, 0);
    if (state[6] != 0) {
        VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[2], &d2);
        spread = RandNextScaled(0x1923) - 0xc91;
        heading = FX_Atan2(d2.x, d2.z);
        state[5] = heading + spread;
    }
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    *(unsigned char *)((char *)state + 0x39) &= ~2;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), Ov193_ChargeAimedShotState);
}
