/* Ov253_SubStateRootB -- sub-state root: clears the actor's +0x1c6 kind and +0x1c7 sub-state
 * (-1), points the state at the +0x38c item's +0xad flag and the actor's +0xb0 vector, seeds the
 * +0xc / +0x10 angles with atan2(0, 1.0) and atan2(1.0, 0), clears bit 0 of the +0x444 item's
 * +8 low byte, raises bits 1, 2 and 4 of the +0x60 high byte and installs the three sub-nodes
 * (slot 1: 020cd5a8, slot 0: 020cd2a4, slot 2: 020cd484). */

#include "nitro/types.h"

struct w8 { unsigned int lo : 8, rest : 24; };

extern short FX_Atan2(int y, int x);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov253_HoldEnter(void);
extern void Ov253_SubStateDispatchB(void);
extern void Ov253_FacingTick(void);

void Ov253_SubStateRootB(int *node) {
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[1] = *(int *)(*state + 0x38c) + 0xad;
    state[2] = *state + 0xb0;
    state[3] = FX_Atan2(0, 0x1000);
    state[4] = FX_Atan2(0x1000, 0);
    ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo &= ~1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x16) << 0x18) >> 0x10);
    }
    SetIndexedSlot(node, 1, Ov253_HoldEnter);
    SetIndexedSlot(node, 0, Ov253_SubStateDispatchB);
    SetIndexedSlot(node, 2, Ov253_FacingTick);
}
