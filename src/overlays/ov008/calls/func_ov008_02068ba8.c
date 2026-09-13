/* func_ov008_02068ba8 -- Ov008_SaveMenuTick: per-frame step of the save menu,
 * by phase (+0x4).  Phase 0 (slot pick) renders the running play time: the
 * game state's seconds plus the ticks since the menu opened (0208becc), scaled
 * by 64 and divided by 0x1ff6210.  Phase 2 (saving) polls the card op
 * (Ov008_PollSaveCardOp): 0 = done -> the game state (0x1cac bytes) is copied
 * into the menu's backup (+0x248), the load phase byte (+0x244) reset, phase
 * 3 entered and the card poll disarmed; 3 = no card -> state / sub-state 1.
 * Phase 3 (reload) steps the chosen slot's load (Ov008_StepSaveSlotLoad);
 * once done (2) the backup is copied back over the game state, the slot rows
 * rebuilt (020697a4) and their digits refreshed, the prompt hidden and
 * redrawn for phase 3 with sound 0x39, phase 4 entered, menu button 5
 * refreshed, the global save counter decremented and context field 95fc set.
 * Phase 5 forces both master brightnesses to 0.  A pending card state
 * (+0x23c) then draws the phase-4 prompt, hides the confirm prompt, enters
 * phase 5 and clears field 95fc.  The page scroll and the slot rows tick last.
 */
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define PHASE_PICK     0
#define PHASE_SAVING   2
#define PHASE_RELOAD   3
#define PHASE_DONE     4
#define PHASE_EXIT     5
#define CARD_OP_DONE   0
#define CARD_OP_NOCARD 3
#define LOAD_DONE      2
#define SOUND_SAVED    0x39
#define TICKS_PER_SECOND 0x1ff6210
#define GAME_STATE_SIZE 0x1cac

typedef struct GameState {
    int nPlayTimeSeconds;     /* 0x00 */
    u8  pad_04[GAME_STATE_SIZE - 4];
} GameState;

typedef struct Ov008SaveMenu {
    int nSlot;                /* 0x000: chosen slot */
    int nPhase;               /* 0x004 */
    u8  pad_008[0x23c - 0x8];
    int nState;               /* 0x23c */
    int nSubState;            /* 0x240 */
    u8  nLoadPhase;           /* 0x244 */
    u8  pad_245[3];
    GameState backup;         /* 0x248 */
} Ov008SaveMenu;

extern GameState *data_0204be18;
extern int  func_ov008_02050c54(void);                                   /* Ov008_GetContext */
extern long long func_020031d4(void);                                    /* GetTick64 */
extern long long func_ov008_0208becc(void);                              /* tick at menu open */
extern u64  func_02020368(long long nValue, unsigned int nDivisor, int nUnused); /* _ll_udiv */
extern void func_ov008_02067b0c(u32 nSeconds);                           /* Ov008_RenderTimeDigits */
extern int  func_ov008_020676b4(Ov008SaveMenu *pMenu);                   /* Ov008_PollSaveCardOp */
extern void MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void func_ov008_0208beb8(void);                                   /* disarm the card poll */
extern u8   func_ov008_020684d0(Ov008SaveMenu *pMenu, int nSlot);        /* Ov008_StepSaveSlotLoad */
extern void func_ov008_020697a4(Ov008SaveMenu *pMenu);                   /* rebuild the slot rows */
extern void func_ov008_02069224(Ov008SaveMenu *pMenu);                   /* Ov008_RefreshSaveRowDigits (pMenu unused) */
extern void func_ov008_02068d58(int bPrompt, int bShow);                 /* confirm prompt */
extern void func_ov008_020693c4(Ov008SaveMenu *pMenu, int nPhase);       /* Ov008_SaveMenuDrawPrompt */
extern void func_02033b78(int nKind, int nSound);                        /* PlaySound */
extern void func_ov008_0206f7b0(int nArg);                               /* Ov008_UpdateMenuButton5 */
extern void func_020208f0(void);                                         /* DecGlobalShortIfPositive_0204bda0 */
extern void func_ov008_02050a40(int nValue);                             /* Ov008_SetCtxField95fc */
extern void func_0201e374(int nBrightness);                              /* SetMasterBrightnessMain */
extern void func_0201e3cc(int nBrightness);                              /* SetMasterBrightnessSub */
extern void func_ov008_02068e68(Ov008SaveMenu *pMenu);                   /* page scroll tick */
extern void func_ov008_02069180(Ov008SaveMenu *pMenu);                   /* slot rows tick */

void func_ov008_02068ba8(Ov008SaveMenu *pMenu)
{
    long long nElapsed;
    int nResult;

    func_ov008_02050c54();
    switch (pMenu->nPhase) {
    case PHASE_PICK:
        nElapsed = func_020031d4() - func_ov008_0208becc();
        func_ov008_02067b0c((u32)(data_0204be18->nPlayTimeSeconds + func_02020368(nElapsed << 6, TICKS_PER_SECOND, 0)));
        break;
    case PHASE_SAVING:
        nResult = func_ov008_020676b4(pMenu);
        if (nResult == CARD_OP_DONE) {
            MI_CpuCopy8(data_0204be18, &pMenu->backup, GAME_STATE_SIZE);
            pMenu->nLoadPhase = 0;
            pMenu->nPhase = PHASE_RELOAD;
            func_ov008_0208beb8();
        } else if (nResult == CARD_OP_NOCARD) {
            pMenu->nState = 1;
            pMenu->nSubState = 1;
        }
        break;
    case PHASE_RELOAD:
        if (func_ov008_020684d0(pMenu, pMenu->nSlot) == LOAD_DONE) {
            MI_CpuCopy8(&pMenu->backup, data_0204be18, GAME_STATE_SIZE);
            func_ov008_020697a4(pMenu);
            func_ov008_02069224(pMenu);
            func_ov008_02068d58(0, 0);
            func_ov008_020693c4(pMenu, PHASE_RELOAD);
            func_02033b78(0, SOUND_SAVED);
            pMenu->nPhase = PHASE_DONE;
            func_ov008_0206f7b0(1);
            func_020208f0();
            func_ov008_02050a40(1);
        }
        break;
    case PHASE_EXIT:
        func_0201e374(0);
        func_0201e3cc(0);
        break;
    }
    if (pMenu->nState != 0) {
        func_ov008_020693c4(pMenu, PHASE_DONE);
        func_ov008_02068d58(0, 0);
        pMenu->nPhase = PHASE_EXIT;
        func_ov008_02050a40(0);
    }
    func_ov008_02068e68(pMenu);
    func_ov008_02069180(pMenu);
}
