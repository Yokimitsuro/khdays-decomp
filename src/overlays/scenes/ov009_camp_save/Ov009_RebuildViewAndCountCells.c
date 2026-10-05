/* Rebuild the panel view (x7: ov000/004/005/008/009/025/026). Load the three message
 * databases this screen needs -- the caller's type code plus 0x14 and 0x13 -- but only
 * the ones not already resident, remembering which we loaded so we can drop exactly
 * those again at the end. Lay out every entry in the source list (each at its own
 * 0xa0-byte row) and total their heights into self[0]. Then snapshot the three 64-bit
 * cell masks out of self+0xcc, hand each to the row renderer, and count every set cell
 * across the 3 panels of 8 rows x 5 columns into self[1]. Finally give every list node
 * a non-zero default for its two counters and refresh the cursor.
 *
 * The masks really are 64-bit: the ROM builds `1LL << bit` as a hi/lo pair (the
 * lsl/rsb/orr/orr dance) and tests both words, which is why `unsigned long long` is the
 * right type -- and it also gives the stride-8 indexing the ROM uses.
 *
 * Two spellings are load-bearing:
 *  - `covered[k]` must come off a struct member: 0xcc is not a multiple of the 8-byte
 *    element, so `self[k*2 + 0x33]` makes mwcc build a k*2 induction variable instead of
 *    the ROM's `add r0, r4, r5, lsl #3`. See codegen-cracks.md.
 *  - `base` must advance in the for-increment. Written as a statement in the body it is
 *    emitted BEFORE the mask pointer's own increment; the ROM does the mask first.
 *
 * (Ghidra renders MsgDb_LoadDb with four arguments here. It takes TWO -- the ROM sets
 * only r0/r1, and there is a call between the first two uses that clobbers r2/r3.) */

#include "game/engine.h"

extern void Ov009_ClearStateFreeLists(int *self);
extern int Ov009_LookupTypeCode(int a);
extern void *NNS_FndGetNextListObject(void *list, void *cur);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int n);
extern void Ov009_LayoutPanelEntry(int *self, int a, void *node, int idx);
extern void Ov009_FoldPanelIntoTally(int *self, int base, unsigned long long covered, unsigned long long *m);

struct Self { char pad[0xcc]; unsigned long long covered[3]; };
extern void Ov009_ClampStatBlock(void *p);

void Ov009_RebuildViewAndCountCells(int *self, int base, void *list, int p4) {
    unsigned long long mask[3];
    int k;
    int tc;
    void *node;
    int row, col;

    Ov009_ClearStateFreeLists(self);
    tc = Ov009_LookupTypeCode(0);
    self[0x3d] = 0;
    self[0x3c] = 0;
    self[0x3a] = 0;
    if (MsgDb_IsLoaded(tc) == 0) {
        MsgDb_LoadDb(tc, 0xe);
        self[0x3d] = 1;
    }
    if (MsgDb_IsLoaded(0x14) == 0) {
        MsgDb_LoadDb(0x14, 0xe);
        self[0x3c] = 1;
    }
    if (MsgDb_IsLoaded(0x13) == 0) {
        MsgDb_LoadDb(0x13, 0xe);
        self[0x3a] = 1;
    }
    for (node = NNS_FndGetNextListObject(list, 0); node != 0;
         node = NNS_FndGetNextListObject(list, node)) {
        Ov009_LayoutPanelEntry(self, *(unsigned short *)((char *)node + 0xa) * 0xa0 + base, node,
                            *(unsigned short *)((char *)node + 0xa));
        self[0] += *(unsigned short *)((char *)node + 8);
    }
    MIi_CpuCopy32((char *)self + 0xcc, mask, 0x18);
    for (k = 0; k < 3; k++, base += 0xa0) {
        Ov009_FoldPanelIntoTally(self, base, ((struct Self *)self)->covered[k], &mask[k]);
    }
    self[1] = 0;
    for (k = 0; k < 3; k++) {
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 5; col++) {
                if ((mask[k] & (1ULL << (col + row * 5))) != 0) {
                    self[1]++;
                }
            }
        }
    }
    for (node = NNS_FndGetNextListObject((char *)self + 8, 0); node != 0;
         node = NNS_FndGetNextListObject((char *)self + 8, node)) {
        if (*(int *)((char *)node + 0x14) == 0) {
            *(int *)((char *)node + 0x14) = 1;
        }
        if (*(int *)((char *)node + 0x10) == 0) {
            *(int *)((char *)node + 0x10) = 1;
        }
    }
    Ov009_ClampStatBlock((char *)self + 0x2c);
    if (self[0x3a] != 0) {
        ResSlot_Release_2(0x13);
        self[0x3a] = 0;
    }
    if (self[0x3c] != 0) {
        ResSlot_Release_2(0x14);
        self[0x3c] = 0;
    }
    if (self[0x3d] != 0) {
        ResSlot_Release_2(tc);
        self[0x3d] = 0;
    }
}
