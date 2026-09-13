/* func_ov008_02073564 -- Ov008_MissionListInitStep: one step of the mission
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
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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

extern const char data_ov008_0209089c[];                                  /* "UI/cm/str/select_&.s.z" */
extern const char data_ov008_020908b4[];                                  /* "UI/cm/str/status_&.s.z" */
extern const Ov008MissionResourceDescriptor data_ov008_0208f8dc;
extern const Ov008MissionResourceDescriptor data_ov008_0208f8d0;
extern void func_020235bc(int nFlag);                                     /* GameState_ClearFlag */
extern int  func_ov008_02050fc8(void);                                    /* Ov008_GetCtxObject95c0 */
extern int  func_02030670(void);                                          /* Session_IsActive */
extern int  func_02030694(void);                                          /* Session_IsReady */
extern void func_02030cf8(int nGate, void *pHandler);                     /* StoreGlobalPtrArray4At0c */
extern void func_ov008_02071fc0(void);                                    /* Ov008_FlushMissionListGraphics */
extern u32  func_ov008_0206fb4c(void);                                    /* FindMinListValue */
extern void func_ov008_0206fbc4(Ov008MissionList *pList, int nArg);       /* reset the list */
extern void func_ov008_02055c4c(void *pLoader, const char *pPath);        /* Ov008_Set_5c4c */
extern int  func_ov008_02051028(void);                                    /* Ov008_GetCtxObject9634 */
extern void func_ov008_0205652c(void *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_InitMissionList */
extern void func_ov008_02072114(Ov008MissionList *pList);                 /* Ov008_MissionListOpen */
extern void func_ov008_020725c4(Ov008MissionList *pList);                 /* Ov008_InitMissionListProgress */
extern void func_ov008_0205b7fc(void);                                    /* Ov008_MainMenu_RecalculateMissionSummary */
extern void func_ov008_02072418(Ov008MissionList *pList);                 /* Ov008_LoadMissionListGraphics (pList unused) */
extern void func_ov008_02072214(Ov008MissionList *pList);                 /* Ov008_InitMissionListRowSurfaces */
extern void *func_ov008_02050d04(void *pFn);                              /* Ov008_AllocCodeNode */
extern void func_ov008_0207350c(void);                                    /* gate 0 handler */
extern void func_ov008_02072858(Ov008MissionList *pList);                 /* Ov008_ShowMissionListWidgets */
extern void func_ov008_020729dc(Ov008MissionList *pList);                 /* Ov008_InitMissionListTrackers */
extern void func_ov008_02072c7c(Ov008MissionList *pList);                 /* Ov008_RefreshMissionRows */
extern void func_ov008_02072d34(Ov008MissionList *pList);                 /* Ov008_DrawShopRow */
extern void func_ov008_02071970(Ov008MissionList *pList);                 /* Ov008_InitMissionListLayout */
extern void func_ov008_02071760(Ov008MissionList *pList, int nPos, int nTarget, int bNow); /* Ov008_ScrollListTo */
extern void func_ov008_02072bc0(Ov008MissionList *pList);                 /* Ov008_MissionListSelectCurrent */
extern void func_ov008_0205ba6c(int nHeadingMode);                        /* Ov008_DrawMissionSummaryHeading */
extern void func_ov008_0206fe08(int nArg);                                /* Ov008_FadeMasterBrightnessBothEngines */

int func_ov008_02073564(Ov008MissionList *pList)
{
    int bDone;
    Ov008MissionResourceDescriptor descriptorA;
    Ov008MissionResourceDescriptor descriptorB;
    int bReady;

    pList->nMode = 1;
    bDone = 0;
    switch (pList->nInitStep) {
    case 0:
        func_020235bc(FLAG_LIST_OPEN);
        pList->nPendingA = 0;
        pList->nPendingB = 0;
        pList->bEntryGate = func_ov008_02050fc8() == 2;
        if (pList->bEntryGate) {
            if (func_02030670() == 0 || func_02030694() != 0) {
                bReady = 1;
            } else {
                bReady = 0;
            }
            pList->bTransferAcked = bReady;
            func_02030cf8(0, func_ov008_0207350c);
        }
        if (pList->bEntryGate != 0) {
            pList->nCursorSlot = func_ov008_0206fb4c();
        }
        pList->nCursorWord = 0;
        func_ov008_0206fbc4(pList, 0);
        func_ov008_02055c4c(pList->textCacheA, data_ov008_0209089c);
        func_ov008_02055c4c(pList->textCacheB, data_ov008_020908b4);
        if (func_ov008_02051028() != 0) {
            descriptorA = data_ov008_0208f8dc;
            func_ov008_0205652c(pList->missionList, &descriptorA);
        } else {
            descriptorB = data_ov008_0208f8d0;
            func_ov008_0205652c(pList->missionList, &descriptorB);
        }
        func_ov008_02072114(pList);
        func_ov008_020725c4(pList);
        func_ov008_0205b7fc();
        func_ov008_02072418(pList);
        func_ov008_02072214(pList);
        pList->pListNode = func_ov008_02050d04(func_ov008_02071fc0);
        pList->nInitStep++;
        break;
    case 1:
        func_ov008_02072858(pList);
        func_ov008_020729dc(pList);
        func_ov008_02072c7c(pList);
        func_ov008_02072d34(pList);
        func_ov008_02071970(pList);
        if (pList->bAnimating == 0) {
            func_ov008_02071760(pList, pList->nTrackMax, SCROLL_NOW, 0);
        } else {
            func_ov008_02071760(pList, 0, SCROLL_NOW, 0);
        }
        pList->nInitStep++;
        break;
    case 2:
        if (pList->bAnimating == 0) {
            func_ov008_02072bc0(pList);
        }
        func_ov008_0205ba6c(2);
        func_ov008_0206fe08(0);
        bDone = 1;
        break;
    }
    return bDone;
}
