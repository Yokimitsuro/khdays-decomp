
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern char *data_ov002_0207fa00;
extern u8 data_0204c240;
extern u16 gMissionNumber;

extern int Ov002_GetStateWord(void);
extern void Ov002_AppendPendingId(int nId);
/* Declared with one parameter on purpose. The callee reads four, and passes
 * the last two on to the archive loader, but the ROM sets only r0 here and
 * leaves the rest holding whatever the previous call left behind - so this
 * translation unit had the one-argument declaration. */
extern void Ov002_LoadOffsetTableOnce(int bAlternate);
extern char *Ov002_FindHandlerByKey(int nKey);
extern int Ov002_TakeEntryOfKind1(void);
extern void Ov002_SpawnSpot(int nIndex, int nGroup, int nSlot, int nKind,
                                VecFx32 *pPlace, int nFlags, int nLevel);
extern void Ov002_FreeRootBuffer0x8d7c(void);

/* Put out the mission's badges (its evi rows: the ordeal badge, the blazon, the unity badge) not
 * yet taken.
 *
 * Only the first seat does this, and only when bit 1 of the mode flags is
 * clear. Three ids are queued for loading and the offset table is brought in,
 * then the set for the field's key (the mission's file, the state word) is
 * walked: each row whose bit (+4: 0, 1 or 3, the missions' list kinds 1, 2
 * and 4) is already set in the mission's 4 badge bits at 0x92b + 4 x
 * gMissionNumber is skipped, and the rest get a spot spawned at the
 * row's own place, with the row's s16 at +8 stamped into the context's
 * per-slot table. The buffer is released either way.
 */
void Ov002_SpawnStateSpots(void)
{
    char *pCtx;
    int nKey;
    char *pTable;
    char *pRow;
    VecFx32 *pPlace;
    int i;
    int nBits;

    pCtx = data_ov002_0207fa00;
    nKey = Ov002_GetStateWord();
    if ((data_0204c240 & 2) == 0 && Session_GetLocalPlayerIndex() == 0) {
        Ov002_AppendPendingId(0x1c2);
        Ov002_AppendPendingId(0x1c3);
        Ov002_AppendPendingId(0x1c4);
        Ov002_LoadOffsetTableOnce(1);

        pTable = Ov002_FindHandlerByKey(nKey);
        if (pTable != 0) {
            i = 0;
            if (*(s8 *)(pTable + 2) > 0) {
                pRow = pTable;
                pPlace = (VecFx32 *)(pTable + 0xc);
                do {
                    nBits = GameState_GetField(gMissionNumber * 4 + 0x92b, 4);
                    if ((nBits & (1 << *(s8 *)(pRow + 4))) == 0) {
                        Ov002_SpawnSpot(Ov002_TakeEntryOfKind1(), 0xf,
                                            (u16)*(s8 *)(pRow + 4),
                                            *(s8 *)(pRow + 5), pPlace, 3, 0);
                        *(s16 *)(pCtx + *(s8 *)(pRow + 4) * 4 + 0x8d4c) =
                            *(s16 *)(pRow + 8);
                    }
                    i++;
                    pRow += 0x14;
                    pPlace = (VecFx32 *)((char *)pPlace + 0x14);
                } while (i < *(s8 *)(pTable + 2));
            }
        }
        Ov002_FreeRootBuffer0x8d7c();
    }
}
