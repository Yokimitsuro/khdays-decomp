/* Ov025_MissionListOpen -- Ov008_MissionListOpen: prepare the mission list.  Of
 * the twelve mission slots, 0 and 4 are always open; the others lock (slot
 * value 0x333, kind 0) unless their game flag (0x3bc9 + slot) is set.  With a
 * modal object up: outside a page transition the current scroll word (u16) is
 * fed to the list; during one the mission named by the context is looked up --
 * found: its slot byte (+4) becomes the cursor slot and its selection text is
 * updated; not found: the cursor slot is cleared, and when the list has no
 * entries either, the cursor steps to the first accepted slot.
 */

#include "nitro/types.h"
#include "game/engine.h"

#define SLOT_COUNT     12
#define FLAG_SLOT_BASE 0x3bc9
#define SLOT_LOCKED    0x333

typedef struct Ov008MissionListEntry {
    u8  pad_00[4];
    u16 nCategory;                /* 0x04 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    u8  pad_00[0x54];
    u8  nCursorSlot;          /* 0x54 */
} Ov008MissionList;

extern void Ov025_Menu_ForwardToWidgets(int nSlot, u32 nValue, u32 nKind);        /* set a mission slot */
extern int  Ov025_GetCtxObject9630(void);                                    /* Ov008_GetCtxObject9630 */
extern int  Ov025_GetCtxObject9634(void);                                    /* page transition active */
extern u32  Ov025_GetCtxField9638(void);                                    /* Ov008_GetCtxField9638 */
extern void Ov025_DispatchIfReady_dcdc(u32 nWord);                               /* Ov008_FeedScrollInput */
extern u32  Ov025_GetCtxField967c(void);                                    /* Ov008_GetCtxField967c */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_5(u32 nMissionId);        /* find the listed mission */
extern void Ov025_EncodeCursorAction(int nSlot);                               /* cursor pick */
extern void Ov025_WorldMap_UpdateSelectionText(int nSlot, int nArg);                     /* Ov008_WorldMap_UpdateSelectionText */
extern u16  Ov025_GetCurrentListId(void);                                    /* mission entry count */
extern u32  Ov025_StepCursorToAcceptedSlot(Ov008MissionList *pList, int nCell);      /* Ov008_StepCursorToAcceptedSlot */

void Ov025_MissionListOpen(Ov008MissionList *pList)
{
    int nSlot;
    int bOpen;
    Ov008MissionListEntry *pEntry;

    for (nSlot = 0; nSlot < SLOT_COUNT; nSlot++) {
        if (nSlot == 0) {
            bOpen = 1;
        } else if (nSlot == 4) {
            bOpen = 1;
        } else {
            bOpen = GameState_IsFlagSet(nSlot + FLAG_SLOT_BASE);
        }
        if (bOpen == 0) {
            Ov025_Menu_ForwardToWidgets(nSlot, SLOT_LOCKED, 0);
        }
    }
    if (Ov025_GetCtxObject9630() == 0) {
        return;
    }
    if (Ov025_GetCtxObject9634() == 0) {
        Ov025_DispatchIfReady_dcdc((u16)Ov025_GetCtxField9638());
        return;
    }
    if (Ov025_GetCtxObject9634() == 0) {
        return;
    }
    pEntry = Ov025_GetNextMissionEntry_5(Ov025_GetCtxField967c());
    if (pEntry != 0) {
        pList->nCursorSlot = pEntry->nCategory;
        Ov025_EncodeCursorAction(pList->nCursorSlot);
        Ov025_WorldMap_UpdateSelectionText(pList->nCursorSlot, 0);
        return;
    }
    pList->nCursorSlot = 0;
    Ov025_EncodeCursorAction(0);
    if (Ov025_GetCurrentListId() == 0 && pEntry == 0) {
        pList->nCursorSlot = Ov025_StepCursorToAcceptedSlot(pList, 1);
    }
}
