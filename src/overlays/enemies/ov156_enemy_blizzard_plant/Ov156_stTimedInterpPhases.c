/* Timed attack step: after a delay probes the ground below and later shows the second model; during
 * the active window sweeps the ground, pushing what it touches; when the model's animation ends
 * picks a random wait, queues action 2 and clears the step handler. */

#include "game/engine.h"

struct bf { unsigned b : 8; };
extern void Ov156_ProbeGroundBelowNode(void *state, void *p);
extern long long FX_DivFx64c(int a, int b);
extern void Ov156_GroundSweep(void *state, long long t, void *p);
extern void SetIndexedSlot(void *obj, int idx, void *value);

void Ov156_stTimedInterpPhases(int *node) {
    int a = node[0];
    int *state = (int *)node[1];
    state[0xb] += *(int *)(a + 0x2c);
    if (*(unsigned char *)((char *)state + 0x38) == 0) {
        if (state[0xb] >= 0x4cc) {
            Ov156_ProbeGroundBelowNode(state, (char *)state + 0x20);
            *(unsigned char *)((char *)state + 0x38) = 1;
        }
    } else if (*(unsigned char *)((char *)state + 0x38) == 1) {
        if (state[0xb] >= 0x911) {
            ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        }
    }
    if (state[0xb] >= 0x4cc && state[0xb] <= 0xbba) {
        long long res = FX_DivFx64c(state[0xb] - 0x4cc, 0x6ee);
        Ov156_GroundSweep(state, res, (char *)state + 0x20);
    }
    if (*(unsigned char *)state[1] == 0) {
        int lo, hi, d;
        *(signed char *)(*state + 0x1c7) = 2;
        lo = *(int *)(*state + 0x224);
        hi = *(int *)(*state + 0x228);
        d = hi - lo;
        if (d < 0) d = -d;
        state[0xd] = lo + RandNextScaled(d + 1);
        SetIndexedSlot(node, *(signed char *)(node + 8), (void *)0);
    }
}
