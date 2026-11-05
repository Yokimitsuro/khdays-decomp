/* Waits until the local player's persistent flag state matches the shared one, then refreshes the
 * save slot widget and commits the page. */

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

typedef struct Ov008PlayerFlags {
    Ov008FlagsByte flags;
    u8 pad_0001[5];
} Ov008PlayerFlags;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x30];
    Ov008PlayerFlags playerFlags[4];
    Ov008FlagsByte sharedFlags;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;

extern void Ov008_UpdateMenuInput(void);
extern int Ov008_Link_IsLocal(void);
extern void Ov008_RefreshSeatCharacter(int slot);
extern void Ov008_CommitSelectedPage(void);

void *Ov008_WaitForLocalFlagSyncState(void)
{
    if (Ov008_UpdateMenuInput(), Ov008_Link_IsLocal() != 0) {
        u32 slot = Session_GetLocalPlayerIndex();
        Ov008MenuContext *context = data_ov008_02090f00;

        context->playerFlags[slot].flags.bits.synchronized =
            context->sharedFlags.bits.synchronized;
    }

    {
        Ov008MenuContext *context = data_ov008_02090f00;
        u32 slot = Session_GetLocalPlayerIndex();

        if (context->playerFlags[slot].flags.bits.synchronized !=
            context->sharedFlags.bits.synchronized) {
            return 0;
        }
    }

    Ov008_RefreshSeatCharacter((int)Session_GetLocalPlayerIndex());
    GameSession_SetSyncEnabled(0);
    return (void *)Ov008_CommitSelectedPage;
}
