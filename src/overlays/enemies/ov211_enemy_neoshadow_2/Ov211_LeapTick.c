/* Leap tick of the ov210 enemy (x3 with ov211/ov282). Once (+0x64) the height of the +0x3d4
 * part's first node (+0x194) is handed to ov210 3ffc. The target is re-acquired into +0x10 --
 * none requests sub-state 2 and ends the action. Until the +0x66 byte marks it, the +0x60 timer
 * accumulates the owner's rate and past 0x199 fires reaction 0x117 mode 5 at the +4 point. The
 * +0x28 heading faces the target's +0x190 from the +4 point. The +0x2c timer accumulates the rate
 * and, while positive, the +0x30 timer's fraction of 0x4cc (capped at 1.0) raises the +0x34 base
 * by up to 1.0 and the owner is announced there (ov107 c5c54). Once the +0xc idle byte clears,
 * sub-state 8 is requested and the action ends. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void Ov211_BindOwnerAndAttach(int height, int a, int b);
extern int Ov107_FindNearestObject(int owner, int flag);
extern int Ov107_BuildAndSendUpdate(int a, int b, int c, int d);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern long long FX_DivFx64c(int num, int denom);
extern void SetIndexedSlot(int self, int idx, int cb);

void Ov211_LeapTick(int *self) {
    int *state = (int *)self[1];
    VecFx32 d;
    VecFx32 v;
    long long q;

    if (*(unsigned char *)((char *)state + 0x64) == 0) {
        Ov211_BindOwnerAndAttach(*(int *)(**(int **)(state[0] + 0x3d4) + 0x194), 0, 0);
        *(unsigned char *)((char *)state + 0x64) = 1;
    }
    state[4] = Ov107_FindNearestObject(state[0], 0);
    if (state[4] == 0) {
        *(char *)(state[0] + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    if (*(unsigned char *)((char *)state + 0x66) == 0) {
        state[0x18] += *(int *)(*self + 0x2c);
        if (state[0x18] >= 0x199) {
            *(unsigned char *)((char *)state + 0x66) = 1;
            Ov107_BuildAndSendUpdate(state[0], 0x117, 5, state[1]);
        }
    }
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], &d);
    state[0xa] = FX_Atan2(d.x, d.z);
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] > 0) {
        state[0xc] += *(int *)(*self + 0x2c);
        q = FX_DivFx64c(state[0xc], 0x4cc);
        if (q > 0x100000000LL) {
            q = 0x100000000LL;
        }
        v = *(VecFx32 *)(state + 0xd);
        v.y += (int)(((q * (long long)0x1000) + 0x80000000LL) >> 32);
        Ov107_MoveNodeAndRelayout((Actor *)state[0], &v);
    }
    if (*(unsigned char *)state[3] == 0) {
        *(char *)(state[0] + 0x1c7) = 8;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}
