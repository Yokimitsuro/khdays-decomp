/* Ov008_MissionListInitStep -- Ov008_MissionListInitStep: one step of the mission
 * list's start-up (+0x2c), returning 1 once done; mode (+0x504) is 1
 * throughout.  Step 0 clears game flag 0x200a and the two words at +0x4f8,
 * sets the entry gate (+0x40) when context object 95c0 is 2 -- then the
 * transfer ack (+0x44) is "no session or session ready" and handler
 * 0207350c is stored at gate 0 -- takes the cursor slot (+0x57) from the
 * smallest list value when gated, clears +0x58, resets the list (0206fbc4
 * 0), points the two text loaders (+0x4bc, +0x4c8) at the select / status
 * strings, opens the mission list (+0x4d4) with descriptor 0208f8dc when
 * context object 9634 exists (0208f8d0 otherwise), opens the list, counts
 * its dots, recalculates the summary, loads the graphics, creates the row
 * surfaces and allocates the code node (+0x80, running 02071fc0).  Step 1 shows the
 * widgets, registers the trackers, refreshes the rows, draws the shop row,
 * lays the list out and scrolls it instantly to +0x28 (or 0 while animating,
 * +0x68).  Step 2 selects the current entry unless animating, draws heading
 * 2 and fades both engines in.
 */

#include "nitro/types.h"

#define FLAG_LIST_OPEN 0x200a
#define SCROLL_NOW     0x7fffffff

typedef struct Ov008MissionResourceDescriptor {
    const u8 *resourcePath;
    int selector;
    int listKind;
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionList {
    u8  pad_000[0x28];
    int nTrackMax;            /* 0x028 */
    int nInitStep;            /* 0x02c */
    u8  pad_030[0x40 - 0x30];
    int bEntryGate;           /* 0x040 */
    int bTransferAcked;       /* 0x044 */
    u8  pad_048[0x57 - 0x48];
    u8  nCursorSlot;          /* 0x057 */
    int nCursorWord;          /* 0x058 */
    u8  pad_05c[0x68 - 0x5c];
    int bAnimating;           /* 0x068 */
    u8  pad_06c[0x80 - 0x6c];
    void *pListNode;          /* 0x080 */
    u8  pad_084[0x4bc - 0x84];
    u8  textCacheA[0xc];      /* 0x4bc */
    u8  textCacheB[0xc];      /* 0x4c8 */
    u8  missionList[0x24];    /* 0x4d4 */
    int nPendingA;            /* 0x4f8 */
    int nPendingB;            /* 0x4fc */
    u8  pad_500[4];
    int nMode;                /* 0x504 */
} Ov008MissionList;

extern const char gOv008UiCmStrSelectTextPath_2[];                                  /* "UI/cm/str/select_&.s.z" */
extern const char gOv008UiCmStrStatusTextPath_3[];                                  /* "UI/cm/str/status_&.s.z" */
extern const Ov008MissionResourceDescriptor data_ov008_0208f8dc;
extern const Ov008MissionResourceDescriptor data_ov008_0208f8d0;
extern void GameState_ClearFlag(int nFlag);
extern int  Ov008_GetCtxObject95c0(void);                                    /* Ov008_GetCtxObject95c0 */
extern int  Session_IsActive(void);                                          /* Session_IsActive */
extern int  Session_IsReady(void);                                          /* Session_IsReady */
extern void StoreGlobalPtrArray4At0c(int nGate, void *pHandler);                     /* StoreGlobalPtrArray4At0c */
extern void Ov008_FlushMissionListGraphics(void);                                    /* Ov008_FlushMissionListGraphics */
extern u32  Ov008_FindMinListValue_2(void);                                    /* FindMinListValue */
extern void Ov008_RelocateOffsetTable(Ov008MissionList *pList, int nArg);       /* reset the list */
extern void Ov008_VarTable_Load(void *pLoader, const char *pPath);        /* Ov008_Set_5c4c */
extern int  Ov008_GetCtxObject9634(void);                                    /* Ov008_GetCtxObject9634 */
extern void Ov008_InitMissionList(void *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_InitMissionList */
extern void Ov008_MissionListOpen(Ov008MissionList *pList);                 /* Ov008_MissionListOpen */
extern void Ov008_InitMissionListProgress(Ov008MissionList *pList);                 /* Ov008_InitMissionListProgress */
extern void Ov008_WorldMap_RecalculateMissionSummary(void);                                    /* Ov008_WorldMap_RecalculateMissionSummary */
extern void Ov008_LoadMissionListGraphics(Ov008MissionList *pList);                 /* Ov008_LoadMissionListGraphics (pList unused) */
extern void Ov008_InitMissionListRowSurfaces(Ov008MissionList *pList);                 /* Ov008_InitMissionListRowSurfaces */
extern void *Ov008_AllocCodeNode(void *pFn);                              /* Ov008_AllocCodeNode */
extern void Ov008_HandleKind4Message(void);                                    /* gate 0 handler */
extern void Ov008_ShowMissionListWidgets(Ov008MissionList *pList);                 /* Ov008_ShowMissionListWidgets */
extern void Ov008_InitMissionListTrackers(Ov008MissionList *pList);                 /* Ov008_InitMissionListTrackers */
extern void Ov008_RefreshMissionRows(Ov008MissionList *pList);                 /* Ov008_RefreshMissionRows */
extern void Ov008_DrawShopRow(Ov008MissionList *pList);                 /* Ov008_DrawShopRow */
extern void Ov008_InitMissionListLayout(Ov008MissionList *pList);                 /* Ov008_InitMissionListLayout */
extern void Ov008_ScrollListTo(Ov008MissionList *pList, int nPos, int nTarget, int bNow); /* Ov008_ScrollListTo */
extern void Ov008_MissionListSelectCurrent(Ov008MissionList *pList);                 /* Ov008_MissionListSelectCurrent */
extern void Ov008_DrawMissionSummaryHeading(int nHeadingMode);                        /* Ov008_DrawMissionSummaryHeading */
extern void Ov008_FadeMasterBrightnessBothEngines(int nArg);                                /* Ov008_FadeMasterBrightnessBothEngines */

int Ov008_MissionListInitStep(Ov008MissionList *pList)
{
    int bDone;
    Ov008MissionResourceDescriptor descriptorA;
    Ov008MissionResourceDescriptor descriptorB;
    int bReady;

    pList->nMode = 1;
    bDone = 0;
    switch (pList->nInitStep) {
    case 0:
        GameState_ClearFlag(FLAG_LIST_OPEN);
        pList->nPendingA = 0;
        pList->nPendingB = 0;
        pList->bEntryGate = Ov008_GetCtxObject95c0() == 2;
        if (pList->bEntryGate) {
            if (Session_IsActive() == 0 || Session_IsReady() != 0) {
                bReady = 1;
            } else {
                bReady = 0;
            }
            pList->bTransferAcked = bReady;
            StoreGlobalPtrArray4At0c(0, Ov008_HandleKind4Message);
        }
        if (pList->bEntryGate != 0) {
            pList->nCursorSlot = Ov008_FindMinListValue_2();
        }
        pList->nCursorWord = 0;
        Ov008_RelocateOffsetTable(pList, 0);
        Ov008_VarTable_Load(pList->textCacheA, gOv008UiCmStrSelectTextPath_2);
        Ov008_VarTable_Load(pList->textCacheB, gOv008UiCmStrStatusTextPath_3);
        if (Ov008_GetCtxObject9634() != 0) {
            descriptorA = data_ov008_0208f8dc;
            Ov008_InitMissionList(pList->missionList, &descriptorA);
        } else {
            descriptorB = data_ov008_0208f8d0;
            Ov008_InitMissionList(pList->missionList, &descriptorB);
        }
        Ov008_MissionListOpen(pList);
        Ov008_InitMissionListProgress(pList);
        Ov008_WorldMap_RecalculateMissionSummary();
        Ov008_LoadMissionListGraphics(pList);
        Ov008_InitMissionListRowSurfaces(pList);
        pList->pListNode = Ov008_AllocCodeNode(Ov008_FlushMissionListGraphics);
        pList->nInitStep++;
        break;
    case 1:
        Ov008_ShowMissionListWidgets(pList);
        Ov008_InitMissionListTrackers(pList);
        Ov008_RefreshMissionRows(pList);
        Ov008_DrawShopRow(pList);
        Ov008_InitMissionListLayout(pList);
        if (pList->bAnimating == 0) {
            Ov008_ScrollListTo(pList, pList->nTrackMax, SCROLL_NOW, 0);
        } else {
            Ov008_ScrollListTo(pList, 0, SCROLL_NOW, 0);
        }
        pList->nInitStep++;
        break;
    case 2:
        if (pList->bAnimating == 0) {
            Ov008_MissionListSelectCurrent(pList);
        }
        Ov008_DrawMissionSummaryHeading(2);
        Ov008_FadeMasterBrightnessBothEngines(0);
        bDone = 1;
        break;
    }
    return bDone;
}
