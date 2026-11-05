/* Ov025_MissionMenuRefreshEntries -- Ov008_MissionMenuRefreshEntries: recount the mission
 * menu's entries.  During a transfer (+0x150) the current mission's entry (by
 * id) gets its text slot picked (0205b720) and shown, and the mission summary
 * is recalculated.  Then the entry count (+0x178) is taken from the list, the
 * "all locked" word (+0x17c) is set, and every listed entry is walked: the
 * entry of the current mission id becomes the cursor (+0x179); a normal entry
 * (not special, flag bit 1 clear) clears "all locked"; and an entry that is
 * selectable -- see Ov008_MissionMenuStep for the same gates: status field
 * 0x28e4 + 3 * id below 2 without a modal object, or during a transition the
 * rank cap / helper 020742ec -- bumps the selectable count (+0x17a).
 */

#include "nitro/types.h"

#define FIELD_MISSION_STATUS 0x28e4
#define ENTRY_FLAG_LOCKED    2

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u16 nCategory;            /* 0x04 */
    u8  pad_06[6];
    u8  bSpecial;             /* 0x0c */
    u8  pad_0d[7];
    u8  nFlags;               /* 0x14 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8  pad_000[0x150];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x178 - 0x154];
    u8  nCount;               /* 0x178 */
    u8  nCursor;              /* 0x179 */
    u8  nSelectable;          /* 0x17a */
    u8  pad_17b;
    int bAllLocked;           /* 0x17c */
} Ov008MissionMenu;

extern u32  Ov025_GetCtxField967c(void);                                    /* Ov008_GetCtxField967c: current mission id */
extern int  Ov025_GetCtxObject9630(void);                                    /* Ov008_GetCtxObject9630 */
extern int  Ov025_GetCtxObject9634(void);                                    /* page transition active */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_5(u32 nMissionId);        /* find the listed mission */
extern void Ov025_EncodeCursorAction(int nSlot);                               /* cursor pick */
extern void Ov025_WorldMap_UpdateSelectionText(int nSlot, int bLocked);                  /* Ov008_WorldMap_UpdateSelectionText */
extern void Ov025_WorldMap_RecalculateMissionSummary(void);                                    /* Ov008_WorldMap_RecalculateMissionSummary */
extern u16  Ov025_GetCurrentListId(void);                                    /* mission entry count */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry(Ov008MissionListEntry *pEntry); /* Ov008_GetNextMissionEntry */
extern u32  GameState_GetField(int nField, int nBits);                         /* GameState_GetField */
extern int  Ov025_IsField8LeField56c(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* rank <= cap */
extern int  Ov025_DefaultStepDone_2(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* helper (ignores its arguments) */

void Ov025_MissionMenuRefreshEntries(Ov008MissionMenu *pMenu)
{
    u32 nMissionId;
    int i;
    int bModal;
    int bTransition;
    int nSlot;
    Ov008MissionListEntry *pEntry;
    int bOk;
    int bDone;

    nMissionId = Ov025_GetCtxField967c();
    bModal = Ov025_GetCtxObject9630();
    bTransition = Ov025_GetCtxObject9634();
    if (pMenu->bTransfer != 0) {
        pEntry = Ov025_GetNextMissionEntry_5(nMissionId);
        if (pEntry != 0) {
            nSlot = pEntry->nCategory;
            Ov025_EncodeCursorAction(nSlot);
            Ov025_WorldMap_UpdateSelectionText(nSlot, 0);
        }
        Ov025_WorldMap_RecalculateMissionSummary();
    }
    pMenu->nCount = Ov025_GetCurrentListId();
    i = 0;
    pMenu->bAllLocked = 1;
    for (pEntry = Ov025_GetNextMissionEntry(0); pEntry != 0; pEntry = Ov025_GetNextMissionEntry(pEntry)) {
        if (pEntry->missionId == nMissionId) {
            pMenu->nCursor = i;
        }
        if (pEntry->bSpecial == 0 && (pEntry->nFlags & ENTRY_FLAG_LOCKED) == 0) {
            pMenu->bAllLocked = 0;
        }
        bOk = 1;
        if (bModal == 0) {
            bDone = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
            if (bDone) {
                bOk = 0;
            }
        }
        if (bModal != 0 && bTransition != 0) {
            if (pMenu->bTransfer != 0) {
                if (Ov025_IsField8LeField56c(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
            if (pMenu->bTransfer == 0) {
                if (Ov025_DefaultStepDone_2(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
        }
        if (bOk) {
            pMenu->nSelectable++;
        }
        i++;
    }
}
