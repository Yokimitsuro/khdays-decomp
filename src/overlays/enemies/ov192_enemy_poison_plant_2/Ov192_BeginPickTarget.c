/* Begin the ov191 enemy's "pick target" state (x3: ov191/192/193): plays pose 3, clears the
 * +0x2c/+0x38 counters, sets the turn rate (+0x30) to 30x the node's +0x2c speed over 5, sends
 * the canned {0,5} event to the notify hook, gathers the owner's +0xa8 actor list (up to four
 * entries, the count kept as a byte), and with none goes to sub-state 2; otherwise picks one at
 * random as the target (+0x18), faces its +0x190 anchor from the +8 position, re-sets the turn
 * rate and advances to the chase handler (020d1370).
 * The candidate array is a block-scoped `int found[4] = {0, 0, 0, 0}` opened after the notify
 * call: the initialiser is what zeroes it through one base register, at that position. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { unsigned short a, b; } Pair;

extern int *List_First(void *list);
extern int *List_Next(void *list);
extern int RandNextScaled(int bound);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern Pair data_ov192_020d4b90;
extern void Ov192_FireShockwave(void);

void Ov192_BeginPickTarget(int node)
{
    int *state = *(int **)(node + 4);
    Pair p;
    int found[4];
    VecFx32 d;
    signed char n = 0;
    int owner;
    int *pNode;
    int actor;
    void (*cb)(int owner, Pair *p, int n);

    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 5;
    {
        Pair *pp = &p;
        pp->b = data_ov192_020d4b90.b;
        pp->a = data_ov192_020d4b90.a;
        cb = *(void (**)(int, Pair *, int))(*state + 0x24);
        if (cb != 0) {
            cb(*state, pp, 4);
        }
    }
    {
        int found[4] = {0, 0, 0, 0};
        owner = *(int *)(*state + 4);
        pNode = List_First((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
        while (actor != 0) {
            found[n] = actor;
            n = n + 1;
            pNode = List_Next((void *)(owner + 0xa8));
            actor = pNode == 0 ? 0 : *pNode;
        }
        if (n == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        state[6] = found[RandNextScaled(n)];
        VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[2], &d);
        state[5] = FX_Atan2(d.x, d.z);
        state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 5;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), Ov192_FireShockwave);
    }
}
