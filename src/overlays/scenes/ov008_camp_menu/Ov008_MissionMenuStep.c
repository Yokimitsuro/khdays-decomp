/* Ov008_MissionMenuStep -- Ov008_MissionMenuStep: move the mission menu's cursor
 * (+0x179) by nStep entries, wrapping over the entry count (+0x178), to the
 * next selectable entry.  A candidate is refused when its list entry is null;
 * without a modal object when the mission's status field (0x28e4 + 3 * id) is
 * already 2 or more; with one during a page transition when the transfer flag
 * (+0x150) is set and the entry's rank exceeds the menu's cap byte, or when it
 * is clear and the helper 020742ec answers 0.  The first accepted entry becomes
 * the cursor and its mission id goes into the context; then the selection text
 * is refreshed for the entry's text slot, and the menu's rows and the panel
 * for the current page (+0x4) are redrawn.  The wrap uses _s32_div_f's
 * remainder (the high word of the 64-bit return); the status test is kept as a
 * materialised bool (cmp/movcs/movcc).
 */

#include "nitro/types.h"

#define FIELD_MISSION_STATUS 0x28e4

typedef struct Ov008MissionListEntry {
    u8  pad_00[2];
    u16 missionId;            /* 0x02 */
    u16 nCategory;            /* 0x04 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8  pad_000[4];
    int nPage;                /* 0x004 */
    u8  pad_008[0x150 - 0x8];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x178 - 0x154];
    u8  nCount;               /* 0x178 */
    u8  nCursor;              /* 0x179 */
} Ov008MissionMenu;

extern int  Ov008_GetCtxObject9630(void);                                    /* Ov008_GetCtxObject9630 */
extern int  Ov008_GetCtxObject9634(void);                                    /* page transition active */
extern long long func_02020400(int nNum, int nDen);                       /* _s32_div_f: remainder in the high word */
extern Ov008MissionListEntry *Ov008_GetNextMissionEntry_2(int nIndex);
extern u32  GameState_GetField(int nField, int nBits);                         /* GameState_GetField */
extern int  Ov008_IsField8LeField56c(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* rank <= cap */
extern int  Ov008_DefaultStepDone_2(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry); /* helper (ignores its arguments) */
extern void Ov008_SetCtxField967c(u32 nMissionId);                          /* Ov008_SetCtxField967c */
extern void Ov008_WorldMap_UpdateSelectionText(int nSlot, int bLocked);                  /* Ov008_WorldMap_UpdateSelectionText */
extern void Ov008_LayoutMissionBadges(Ov008MissionMenu *pMenu);                 /* redraw rows */
extern void Ov008_DrawMissionDetail(Ov008MissionMenu *pMenu, int nPage);      /* redraw page panel */

void Ov008_MissionMenuStep(Ov008MissionMenu *pMenu, int nStep)
{
    Ov008MissionListEntry *pEntry;
    int bModal;
    int i;
    int bOk;
    int bTransition;
    int nIndex;
    int bDone;

    bModal = Ov008_GetCtxObject9630();
    bTransition = Ov008_GetCtxObject9634();
    nIndex = pMenu->nCursor + nStep;
    for (i = 0; i < pMenu->nCount; i++) {
        bOk = 1;
        nIndex = (int)(func_02020400(nIndex + pMenu->nCount, pMenu->nCount) >> 32);
        pEntry = Ov008_GetNextMissionEntry_2(nIndex);
        if (pEntry == 0) {
            bOk = 0;
        }
        if (bModal == 0) {
            bDone = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
            if (bDone) {
                bOk = 0;
            }
        }
        if (bModal != 0 && bTransition != 0) {
            if (pMenu->bTransfer != 0) {
                if (Ov008_IsField8LeField56c(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
            if (pMenu->bTransfer == 0) {
                if (Ov008_DefaultStepDone_2(pMenu, pEntry) == 0) {
                    bOk = 0;
                }
            }
        }
        if (bOk) {
            pMenu->nCursor = nIndex;
            Ov008_SetCtxField967c(pEntry->missionId);
            break;
        }
        nIndex += nStep;
    }
    Ov008_WorldMap_UpdateSelectionText(pEntry->nCategory, 0);
    Ov008_LayoutMissionBadges(pMenu);
    Ov008_DrawMissionDetail(pMenu, pMenu->nPage);
}
