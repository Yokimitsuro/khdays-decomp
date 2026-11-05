/* MobiClip player teardown: release the two blocks the player owns on the root heap (the stream
 * state at +0x8b4c and the reader at +0x8b40), drop sound channel 3, then invalidate the
 * current-clip id and clear the player block's second word.
 *
 * Parked as pure instruction scheduling -- the original materialises both constants first and
 * then does both stores, while mwcc interleaved them. It was the global read: written as
 * `*(int *)((char *)&data + 4)` the whole store is one expression mwcc schedules as it likes;
 * written as `data[1]` it comes out as the original has it. Same lever as
 * Ov008_SetTargetSlot. */

#include "game/heap.h"
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_ov024_020835cc(int p);
extern void StoreGlobalArrayEntry(int channel, int a);
extern int  data_ov024_02093900;
extern int  data_ov024_02093a20[];

void Ov024_TeardownPlayer(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    func_ov024_020835cc(heap + 0x8b4c);
    FontResource_Destroy((void *)(heap + 0x8b40));
    StoreGlobalArrayEntry(3, 0);
    data_ov024_02093900 = -1;
    data_ov024_02093a20[1] = 0;
}
