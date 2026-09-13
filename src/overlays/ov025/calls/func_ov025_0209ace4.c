/* func_ov025_0209ace4 -- Ov008_SaveMenuInitStep: one step of the save menu's
 * start-up sequence (+0xc), returning 1 once it is done.  Step 0 loads the
 * menu graphics, clears the main BG1..3 screens, points the text loader
 * (+0x158) at data_ov025_020b4eb0, backs the whole game state up (+0x248),
 * resets the load phase byte (+0x244) and the phase (+0x4).  Step 1 loads
 * the summary of slot +0x8 (Ov008_StepSaveSlotLoad); once done the slot's
 * stamp (fields 0xc77:0xc87, 16 bits each) replaces the best stamp (+0x1ef8)
 * and best slot (+0x1ef4) when newer, and the next slot is loaded until all
 * three are.  Step 2 restores the backup, rebuilds the backgrounds, rows and
 * surfaces, selects the last saved slot (field 0xc98, 2 bits, +0x0), refreshes
 * the row digits, clears the tween (+0x218) and shows the points.  Step 3 is
 * the end: a pending card state (+0x23c) draws prompt 4 and enters phase 5.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define SLOT_COUNT   3
#define STEP_DONE    3
#define PHASE_EXIT   5
#define FIELD_STAMP_HI 0xc77
#define FIELD_STAMP_LO 0xc87
#define FIELD_LAST_SLOT 0xc98
#define GAME_STATE_SIZE 0x1cac

typedef struct GameState {
    int nPlayTimeSeconds;     /* 0x00 */
    int nRewardTotal;         /* 0x04 */
    int nPoints;              /* 0x08 */
    u8  pad_0c[GAME_STATE_SIZE - 0xc];
} GameState;

typedef struct Ov008SaveMenu {
    int nSlot;                /* 0x0000: chosen slot */
    int nPhase;               /* 0x0004 */
    int nCursor;              /* 0x0008: slot being loaded */
    int nInitStep;            /* 0x000c */
    u8  pad_0010[0x158 - 0x10];
    u8  varRecords[0xc];      /* 0x0158 */
    u8  pad_0164[0x218 - 0x164];
    u8  tween[0x24];          /* 0x0218 */
    int nState;               /* 0x023c */
    int nSubState;            /* 0x0240 */
    u8  nLoadPhase;           /* 0x0244 */
    u8  pad_0245[3];
    GameState backup;         /* 0x0248 */
    int nBestSlot;            /* 0x1ef4 */
    u32 nBestStamp;           /* 0x1ef8 */
} Ov008SaveMenu;

extern GameState *data_0204be18;
extern const char data_ov025_020b4eb0[];
extern void  func_ov025_02099fe4(void);                                   /* load the menu graphics */
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  func_ov025_0208985c(void *pLoader, const char *pPath);       /* Ov008_Set_5c4c */
extern u8    func_ov025_0209a8b0(Ov008SaveMenu *pMenu, int nSlot);        /* Ov008_StepSaveSlotLoad */
extern u32   func_020235d0(int nField, int nBits);                        /* GameState_GetField */
extern void  func_ov025_0209a190(void);                                   /* Ov008_LoadMenuBgWithVariantChars */
extern void  func_ov025_0209a2bc(Ov008SaveMenu *pMenu);
extern void  func_ov025_0209a5fc(Ov008SaveMenu *pMenu);
extern void  func_ov025_02099d50(Ov008SaveMenu *pMenu, int nOld, int nNew); /* Ov008_PlaceElementByVariant */
extern void  func_ov025_0209b604(Ov008SaveMenu *pMenu);                   /* Ov008_RefreshSaveRowDigits */
extern void  func_02035f84(void *pTween);                                 /* Tween_Clear */
extern void  func_ov025_02099dd8(int nPoints);
extern void  func_ov025_0209b7a4(Ov008SaveMenu *pMenu, int nPhase);       /* Ov008_SaveMenuDrawPrompt */
extern void  func_ov025_0209b138(int bPrompt, int bShow);                 /* confirm prompt */

int func_ov025_0209ace4(Ov008SaveMenu *pMenu)
{
    int bDone;
    u32 nStamp;

    bDone = 0;
    switch (pMenu->nInitStep) {
    case 0:
        func_ov025_02099fe4();
        MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
        func_ov025_0208985c(pMenu->varRecords, data_ov025_020b4eb0);
        pMenu->backup = *data_0204be18;
        pMenu->nLoadPhase = 0;
        pMenu->nPhase = 0;
        pMenu->nInitStep++;
        break;
    case 1:
        if (func_ov025_0209a8b0(pMenu, pMenu->nCursor) == 2) {
            nStamp = func_020235d0(FIELD_STAMP_HI, 16) << 16;
            nStamp = func_020235d0(FIELD_STAMP_LO, 16) | nStamp;
            if (nStamp > pMenu->nBestStamp) {
                pMenu->nBestStamp = nStamp;
                pMenu->nBestSlot = pMenu->nCursor;
            }
            pMenu->nCursor++;
            pMenu->nLoadPhase = 0;
            if (pMenu->nCursor >= SLOT_COUNT) {
                pMenu->nInitStep++;
            }
        }
        break;
    case 2:
        *data_0204be18 = pMenu->backup;
        func_ov025_0209a190();
        func_ov025_0209a2bc(pMenu);
        func_ov025_0209a5fc(pMenu);
        pMenu->nSlot = func_020235d0(FIELD_LAST_SLOT, 2);
        func_ov025_02099d50(pMenu, 0, pMenu->nSlot);
        func_ov025_0209b604(pMenu);
        func_02035f84(pMenu->tween);
        func_ov025_02099dd8(data_0204be18->nPoints);
        pMenu->nInitStep++;
        break;
    case STEP_DONE:
        if (pMenu->nState != 0) {
            func_ov025_0209b7a4(pMenu, 4);
            func_ov025_0209b138(0, 0);
            pMenu->nPhase = PHASE_EXIT;
        }
        bDone = 1;
        break;
    }
    return bDone;
}
