/*
 * List_TryInvokeEntry - run CmdPacket_Dispatch on the indexed list entry if it is active.
 *
 * The manager global data_0204c22c points at a table whose entry array is at [+4]; each entry is
 * 0xc bytes. For index param_1, if the entry's activeness field (u16 at +4) is non-zero, the
 * global list context gSubHeap is swapped in via Heap_SetCurrent (saving the previous one),
 * CmdPacket_Dispatch is run on (entry, entryArray), then the previous context is restored. Returns 1
 * when it ran, 0 when the manager is null or the entry is inactive.
 */

#include "game/engine.h"

extern int *data_0204c22c;
extern GameHeap *gSubHeap;
extern void CmdPacket_Dispatch(int entry, int base);

int List_TryInvokeEntry(int param_1)
{
    int *ctx = data_0204c22c;
    int off;
    GameHeap *saved;

    if (ctx == 0)
        return 0;
    off = param_1 * 0xc;
    if (*(unsigned short *)(ctx[1] + off + 4) == 0)
        return 0;
    saved = Heap_SetCurrent(gSubHeap);
    CmdPacket_Dispatch(ctx[1] + off, ctx[1]);
    Heap_SetCurrent(saved);
    return 1;
}
