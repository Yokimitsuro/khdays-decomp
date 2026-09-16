/* func_ov008_02077b28 -- Ov008_MissionMenuInitStep: one step of the mission
 * menu's start-up (+0x0), returning 1 once done.  Step 0 clears the two
 * selection words (+0x180 / +0x184), sets the transfer flag (+0x150) when
 * context object 95c0 is 2 -- then the transfer ack (+0x154) is "no session
 * or session ready" and handler 02077b0c is stored at gate 0 -- takes the
 * cursor slot (+0x56c) from the smallest list value when transferring,
 * acquires message dbs 0x15 / 0x19 / 0x1a, loads the flag table (+0x174),
 * points the two text loaders (+0x530, +0x53c) at the mission / status
 * strings, opens the mission list (+0x548) with descriptor 0208fa1c when
 * context object 9634 exists (0208fa10 otherwise), refreshes the entries,
 * loads the graphics, creates the surfaces, allocates the scroll code node
 * (+0x170, running 02074560) and parks the page scroll (+0x168) at -0x40.
 * Step 1 hides the widgets, registers the trackers, redraws the rows and
 * page panel, on more than one selectable mission (+0x17a) sets tags 0xc / 0xd
 * of block 954c, switches to tab 1 when object 9634 exists without a
 * transfer (else 0) and marks slots 0x1a / 0x1b used.  Step 2 draws heading
 * 2.
 * Codegen: the widget hide (02077554) and the graphics load (02077190) are
 * called WITH the menu pointer although neither reads it -- case 1's opening
 * call then reuses the incoming r0 (no `mov r0, r5`), and that keeps r0 live
 * through the switch chain so the step temporary takes r1 as the ROM does.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define SCROLL_HIDDEN (-0x40)

typedef struct Ov008MissionResourceDescriptor {
    const u8 *resourcePath;
    int selector;
    int listKind;
} Ov008MissionResourceDescriptor;

typedef struct Ov008MissionMenu {
    int nInitStep;            /* 0x000 */
    u8  pad_004[0x150 - 0x4];
    int bTransfer;            /* 0x150 */
    int bTransferAcked;       /* 0x154 */
    u8  pad_158[0x168 - 0x158];
    int nPageScroll;          /* 0x168 */
    u8  pad_16c[4];
    void *pListNode;          /* 0x170 */
    void *pFlagTable;         /* 0x174 */
    u8  nCount;               /* 0x178 */
    u8  nCursor;              /* 0x179 */
    u8  nSelectable;          /* 0x17a */
    u8  pad_17b[0x180 - 0x17b];
    int bSelectionPending;    /* 0x180 */
    int bSelectionArmed;      /* 0x184 */
    u8  pad_188[0x530 - 0x188];
    u8  textCacheA[0xc];      /* 0x530 */
    u8  textCacheB[0xc];      /* 0x53c */
    u8  missionList[0x24];    /* 0x548 */
    u8  nCursorSlot;          /* 0x56c */
} Ov008MissionMenu;

extern const char data_ov008_020909a4[];                                  /* "UI/cm/str/mission_&.s.z" */
extern const char data_ov008_020909bc[];                                  /* "UI/cm/str/status_&.s.z" */
extern const Ov008MissionResourceDescriptor data_ov008_0208fa1c;
extern const Ov008MissionResourceDescriptor data_ov008_0208fa10;
extern int  func_ov008_02050fc8(void);                                    /* Ov008_GetCtxObject95c0 */
extern int  func_02030670(void);                                          /* Session_IsActive */
extern int  func_02030694(void);                                          /* Session_IsReady */
extern void func_02030cf8(int nGate, void *pHandler);                     /* StoreGlobalPtrArray4At0c */
extern void func_ov008_02077b0c(void);                                    /* gate 0 handler */
extern u32  func_ov008_0207430c(void);                                    /* FindMinListValue */
extern int  func_ov008_02051094(int nDb);                                 /* Ov008_AcquireMsgDb */
extern void func_ov008_02074384(Ov008MissionMenu *pMenu);                 /* load the flag table */
extern void func_ov008_02055c4c(void *pLoader, const char *pPath);        /* Ov008_Set_5c4c */
extern int  func_ov008_02051028(void);                                    /* Ov008_GetCtxObject9634 */
extern void func_ov008_0205652c(void *pList, Ov008MissionResourceDescriptor *pDescriptor); /* Ov008_InitMissionList */
extern void func_ov008_02076ffc(Ov008MissionMenu *pMenu);                 /* Ov008_MissionMenuRefreshEntries */
extern void func_ov008_02077190(Ov008MissionMenu *pMenu);                 /* Ov008_LoadMissionMenuGraphics (pMenu unused) */
extern void func_ov008_0207733c(Ov008MissionMenu *pMenu);                 /* Ov008_InitMissionMenuSurfaces */
extern void *func_ov008_02050d04(void *pFn);                              /* Ov008_AllocCodeNode */
extern void func_ov008_02074560(void);                                    /* Ov008_UpdateBg3ScrollFromPage */
extern void  func_ov008_02077554(Ov008MissionMenu *pMenu);                 /* Ov008_HideMissionMenuWidgets (pMenu unused) */                                    /* Ov008_HideMissionMenuWidgets */
extern void func_ov008_020776bc(Ov008MissionMenu *pMenu);                 /* Ov008_InitMissionMenuTrackers */
extern void func_ov008_02076158(Ov008MissionMenu *pMenu);                 /* redraw rows */
extern void func_ov008_02076780(Ov008MissionMenu *pMenu, int nPage);      /* redraw page panel */
extern int  func_ov008_02050c3c(void);                                    /* Ov008_GetCtxBlock954c */
extern void func_ov008_020744d4(int nCtx, u32 nTag, u16 nValue, u16 nFlag); /* Ov008_SetActiveTagValueAndFlag */
extern void func_ov008_02074a4c(Ov008MissionMenu *pMenu, int nTab);       /* Ov008_SwitchMenuTab */
extern void func_ov008_02050b3c(int nSlot);                               /* Ov008_MarkSlotUsed */
extern void func_ov008_0205ba6c(int nHeadingMode);                        /* Ov008_DrawMissionSummaryHeading */

int func_ov008_02077b28(Ov008MissionMenu *pMenu)
{
    int bDone;
    Ov008MissionResourceDescriptor descriptorA;
    Ov008MissionResourceDescriptor descriptorB;
    int bReady;
    int nCtx;
    int nTab;

    bDone = 0;
    switch (pMenu->nInitStep) {
    case 0:
        pMenu->bSelectionPending = 0;
        pMenu->bSelectionArmed = 0;
        pMenu->bTransfer = func_ov008_02050fc8() == 2;
        if (pMenu->bTransfer) {
            if (func_02030670() == 0 || func_02030694() != 0) {
                bReady = 1;
            } else {
                bReady = 0;
            }
            pMenu->bTransferAcked = bReady;
            func_02030cf8(0, func_ov008_02077b0c);
        }
        if (pMenu->bTransfer != 0) {
            pMenu->nCursorSlot = func_ov008_0207430c();
        }
        func_ov008_02051094(0x15);
        func_ov008_02051094(0x19);
        func_ov008_02051094(0x1a);
        pMenu->pFlagTable = 0;
        func_ov008_02074384(pMenu);
        func_ov008_02055c4c(pMenu->textCacheA, data_ov008_020909a4);
        func_ov008_02055c4c(pMenu->textCacheB, data_ov008_020909bc);
        if (func_ov008_02051028() != 0) {
            descriptorA = data_ov008_0208fa1c;
            func_ov008_0205652c(pMenu->missionList, &descriptorA);
        } else {
            descriptorB = data_ov008_0208fa10;
            func_ov008_0205652c(pMenu->missionList, &descriptorB);
        }
        func_ov008_02076ffc(pMenu);
        func_ov008_02077190(pMenu);
        func_ov008_0207733c(pMenu);
        pMenu->pListNode = func_ov008_02050d04(func_ov008_02074560);
        pMenu->nPageScroll = SCROLL_HIDDEN;
        pMenu->nInitStep++;
        break;
    case 1:
        func_ov008_02077554(pMenu);
        func_ov008_020776bc(pMenu);
        func_ov008_02076158(pMenu);
        func_ov008_02076780(pMenu, 0);
        if (pMenu->nSelectable > 1) {
            nCtx = func_ov008_02050c3c();
            func_ov008_020744d4(nCtx, 0xc, 0, 0);
            func_ov008_020744d4(nCtx, 0xd, 0x1e, 0);
        }
        nTab = 0;
        if (func_ov008_02051028() != 0) {
            nTab = pMenu->bTransfer == 0;
        }
        func_ov008_02074a4c(pMenu, nTab);
        func_ov008_02050b3c(0x1a);
        func_ov008_02050b3c(0x1b);
        pMenu->nInitStep++;
        break;
    case 2:
        func_ov008_0205ba6c(2);
        bDone = 1;
        break;
    }
    return bDone;
}
