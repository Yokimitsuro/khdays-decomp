/* Ov025_SaveMenuTick -- Ov008_SaveMenuTick: per-frame step of the save menu,
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

#include "nitro/types.h"
#include "game/engine.h"

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

extern GameState *gGameState;
extern int  Ov025_GetContext(void);                                   /* Ov008_GetContext */
extern long long OS_GetTick(void);                                    /* GetTick64 */
extern long long Ov025_GetLatchedTick(void);                              /* tick at menu open */
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor); /* _ll_udiv */
extern void Ov025_RenderTimeDigits(u32 nSeconds);                           /* Ov008_RenderTimeDigits */
extern int  Ov025_PollSaveCardOp(Ov008SaveMenu *pMenu);                   /* Ov008_PollSaveCardOp */
extern void MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void Ov025_LatchTick(void);                                   /* disarm the card poll */
extern u8   Ov025_StepSaveSlotLoad(Ov008SaveMenu *pMenu, int nSlot);        /* Ov008_StepSaveSlotLoad */
extern void Ov025_SaveMenu_RefreshRows(Ov008SaveMenu *pMenu);                   /* rebuild the slot rows */
extern void Ov025_RefreshSaveRowDigits(Ov008SaveMenu *pMenu);                   /* Ov008_RefreshSaveRowDigits (pMenu unused) */
extern void Ov025_SetMenuEntriesVisible(int bPrompt, int bShow);                 /* confirm prompt */
extern void Ov025_SaveMenuDrawPrompt(Ov008SaveMenu *pMenu, int nPhase);       /* Ov008_SaveMenuDrawPrompt */
extern void Ov025_UpdateMenuButton5(int nArg);                               /* Ov008_UpdateMenuButton5 */
extern void Ov025_SetCtxField95fc(int nValue);                             /* Ov008_SetCtxField95fc */
extern void Ov025_TickPageScroll(Ov008SaveMenu *pMenu);                   /* page scroll tick */
extern void Ov025_SaveMenu_SlideArrows(Ov008SaveMenu *pMenu);                   /* slot rows tick */

void Ov025_SaveMenuTick(Ov008SaveMenu *pMenu)
{
    long long nElapsed;
    int nResult;

    Ov025_GetContext();
    switch (pMenu->nPhase) {
    case PHASE_PICK:
        nElapsed = OS_GetTick() - Ov025_GetLatchedTick();
        Ov025_RenderTimeDigits((u32)(gGameState->nPlayTimeSeconds + func_02020368(nElapsed << 6, TICKS_PER_SECOND)));
        break;
    case PHASE_SAVING:
        nResult = Ov025_PollSaveCardOp(pMenu);
        if (nResult == CARD_OP_DONE) {
            MI_CpuCopy8(gGameState, &pMenu->backup, GAME_STATE_SIZE);
            pMenu->nLoadPhase = 0;
            pMenu->nPhase = PHASE_RELOAD;
            Ov025_LatchTick();
        } else if (nResult == CARD_OP_NOCARD) {
            pMenu->nState = 1;
            pMenu->nSubState = 1;
        }
        break;
    case PHASE_RELOAD:
        if (Ov025_StepSaveSlotLoad(pMenu, pMenu->nSlot) == LOAD_DONE) {
            MI_CpuCopy8(&pMenu->backup, gGameState, GAME_STATE_SIZE);
            Ov025_SaveMenu_RefreshRows(pMenu);
            Ov025_RefreshSaveRowDigits(pMenu);
            Ov025_SetMenuEntriesVisible(0, 0);
            Ov025_SaveMenuDrawPrompt(pMenu, PHASE_RELOAD);
            PlaySound(0, SOUND_SAVED);
            pMenu->nPhase = PHASE_DONE;
            Ov025_UpdateMenuButton5(1);
            Sleep_Unblock();
            Ov025_SetCtxField95fc(1);
        }
        break;
    case PHASE_EXIT:
        SetMasterBrightnessMain(0);
        SetMasterBrightnessSub(0);
        break;
    }
    if (pMenu->nState != 0) {
        Ov025_SaveMenuDrawPrompt(pMenu, PHASE_DONE);
        Ov025_SetMenuEntriesVisible(0, 0);
        pMenu->nPhase = PHASE_EXIT;
        Ov025_SetCtxField95fc(0);
    }
    Ov025_TickPageScroll(pMenu);
    Ov025_SaveMenu_SlideArrows(pMenu);
}
