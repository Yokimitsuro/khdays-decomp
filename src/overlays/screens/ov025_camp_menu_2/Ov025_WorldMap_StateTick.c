/* Ov025_WorldMap_StateTick -- Ov008_WorldMap_StateTick: the two opening steps of the holo-missions' world map,
 * one per call of its state (+0); returns 1 once state 1 has run.  State 0 notes whether the
 * 95c0 object (02084dd8) is 2 (+0x14e0), sets up the display (0208cde0) and builds the object
 * list from data_ov025_020b3934 with kind / selector 3 / 8 for that, else 4 / the current day
 * (game-state field 9) without the 9630 object (02084e08), 3 / 7 during a page transition
 * (02084e38) and 0 / 0 otherwise -- through the retrying builder 0208d69c when the 9630 object,
 * a page transition and a current mission (02084ff0) are all set, else straight into the
 * mission list +0x13fc (0208a13c); then 0208cdc4, the tag tracker (02084a64) loads member 0x13
 * (020891dc), the sub-object (+4) is reset (0208e5a4) and told the transition direction 4 (0
 * from day 357 on; 0208eaf8, kept at +0x14ec).  State 1 runs 0208d05c / 0208d2a4 / 0208d454
 * and stamps the opening tick (+0x14d4).  The sub-object ticks every call (0208ea58). */

#include "nitro/types.h"

typedef struct Ov008MissionResourceDescriptor {
    const char *pszPath;      /* 0x00 */
    int  nSelector;           /* 0x04 */
    int  nListKind;           /* 0x08 */
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionListState {
    u8   data[0x24];
} Ov008MissionListState;

typedef struct Ov008WorldMap {
    int  nState;              /* 0x0000 */
    u8   sub[0x13fc - 4];     /* 0x0004: the sub-object ticked by 0208ea58 */
    Ov008MissionListState missionList; /* 0x13fc */
    u8   pad_1420[0x14d4 - 0x1420];
    u64  nTick;               /* 0x14d4: the tick the menu opened at */
    int  bTimerFired;         /* 0x14dc */
    int  bWireless;           /* 0x14e0: the 95c0 object is 2 */
    int  nField14e4;          /* 0x14e4 */
    int  nField14e8;          /* 0x14e8 */
    int  nDir;                /* 0x14ec: the transition direction handed to 0208eaf8 */
} Ov008WorldMap;

extern int   Ov025_GetCtxObject95c0(void);                             /* Ov008_GetCtxObject95c0 */
extern void  Ov025_WorldMap_SetupDisplay(void);                             /* Ov008_WorldMap_SetupDisplay */
extern int   Ov025_GetCtxObject9630(void);                             /* Ov008_GetCtxObject9630 */
extern int   Ov025_GetCtxObject9634(void);                             /* Ov025_GetCtxObject9634: page transition */
extern u32   GameState_GetField(int nField, int nBits);                  /* GameState_GetField */
extern u32   Ov025_GetCtxField967c(void);                             /* Ov008_GetCtxField967c: current mission id */
extern void  Ov025_WorldMap_InitObjectListRetry(Ov008WorldMap *pMenu, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_WorldMap_InitObjectListRetry */
extern void  Ov025_InitObjectWithList(Ov008MissionListState *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov025_InitMissionList */
extern void  Ov025_SortListByKey(Ov008WorldMap *pMenu);
extern int   Ov025_GetCtxBlock954c(void);                             /* Ov008_GetCtxBlock954c: the tag tracker */
extern u32   Ov025_PackSlotTag(int nMember);                      /* Ov008_PackSlotTag */
extern void  Ov025_LoadBlockDispatchThreeThenFree(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern void  Ov025_WorldMap_InitPanelContext(void *pSub, int nArg);
extern void  Ov025_MenuCursor_MoveToSlotNoAnim(void *pSub, int nDir);
extern void  Ov025_WorldMap_SetupToolbar(Ov008WorldMap *pMenu);
extern void  Ov025_SetupMenuBgCellsAlt(Ov008WorldMap *pMenu);
extern void  Ov025_WorldMap_SetupTextSurfaces(Ov008WorldMap *pMenu);
extern u64   OS_GetTick(void);                                   /* GetTick64 */
extern void  Ov025_DrawMenuPanels(void *pSub);
extern const Ov008MissionResourceDescriptor data_ov025_020b3934;

int Ov025_WorldMap_StateTick(Ov008WorldMap *pMenu)
{
    Ov008MissionResourceDescriptor desc;
    int bDone;
    int nTracker;
    int nDir;

    desc = data_ov025_020b3934;
    bDone = 0;
    switch (pMenu->nState) {
    case 0:
        pMenu->bWireless = Ov025_GetCtxObject95c0() == 2;
        Ov025_WorldMap_SetupDisplay();
        if (pMenu->bWireless != 0) {
            desc.nListKind = 3;
            desc.nSelector = 8;
        } else if (Ov025_GetCtxObject9630() != 0) {
            if (Ov025_GetCtxObject9634() != 0) {
                desc.nListKind = 3;
                desc.nSelector = 7;
            } else {
                desc.nListKind = 0;
                desc.nSelector = 0;
            }
        } else {
            desc.nListKind = 4;
            desc.nSelector = GameState_GetField(0, 9);
        }
        if (Ov025_GetCtxObject9630() != 0 && Ov025_GetCtxObject9634() != 0 && Ov025_GetCtxField967c() != 0) {
            Ov025_WorldMap_InitObjectListRetry(pMenu, &desc);
        } else {
            Ov025_InitObjectWithList(&pMenu->missionList, &desc);
        }
        Ov025_SortListByKey(pMenu);
        nTracker = Ov025_GetCtxBlock954c();
        Ov025_LoadBlockDispatchThreeThenFree(nTracker, Ov025_PackSlotTag(0x13));
        nDir = 4;
        if (GameState_GetField(0, 9) >= 357) {
            nDir = 0;
        }
        Ov025_WorldMap_InitPanelContext(pMenu->sub, 0);
        Ov025_MenuCursor_MoveToSlotNoAnim(pMenu->sub, nDir);
        pMenu->nDir = nDir;
        pMenu->nState++;
        break;
    case 1:
        Ov025_WorldMap_SetupToolbar(pMenu);
        Ov025_SetupMenuBgCellsAlt(pMenu);
        Ov025_WorldMap_SetupTextSurfaces(pMenu);
        pMenu->nState++;
        pMenu->nTick = OS_GetTick();
        bDone = 1;
        break;
    }
    Ov025_DrawMenuPanels(pMenu->sub);
    return bDone;
}
