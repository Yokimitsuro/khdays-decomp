/* Releases the pending service instance, rebuilds the menu list and, when the persistent flag
 * 0x2010 changed, starts syncing it before committing the page. */

#include "nitro/types.h"
#include "game/engine.h"

typedef union Ov008FlagsByte {
    u8 raw;
    struct {
        u8 bit0 : 1;
        u8 synchronized : 1;
        u8 rest : 6;
    } bits;
} Ov008FlagsByte;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x48];
    Ov008FlagsByte sharedFlags;
} Ov008MenuContext;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void VeneerTo_Obj_Destroy(int handle);
extern char *gGameState;
extern void Ov008_BuildMenuListFrom(void *source);
extern Ov008MenuContext *data_ov008_02090f00;
extern void Ov008_CommitSelectedPage(void);
extern void Ov008_WaitForLocalFlagSyncState(void);

void *Ov008_RefreshMenuAndSynchronizePersistentFlagState(void)
{
    char *root = NNSi_FndGetCurrentRootHeap();

    if (*(int *)(root + 0x14) >= 0) {
        VeneerTo_Obj_Destroy(*(int *)(root + 0x14));
        *(int *)(root + 0x14) = -1;
    }

    Ov008_BuildMenuListFrom(gGameState + 0xee0);

    {
        u8 synchronized =
            data_ov008_02090f00->sharedFlags.bits.synchronized;
        int flagSet = GameState_IsFlagSet(0x2010) != 0;

        if (synchronized == flagSet) {
            return (void *)Ov008_CommitSelectedPage;
        }

        data_ov008_02090f00->sharedFlags.bits.synchronized = (u8)flagSet;
        GameSession_SetSyncEnabled(1);
        return (void *)Ov008_WaitForLocalFlagSyncState;
    }
}
