/* func_ov025_0209ab08 -- Ov008_SaveMenuConfirm: the save menu's "confirm"
 * handler.  Nothing while a card state (+0x23c) is pending.  Phase 0 (slot
 * pick): shows the confirm prompt (02068d58 0,1), lays the menu out for phase
 * 1, clears the yes/no choice (+0x64), parks every slot other than the chosen
 * one (+0x0) at x = 0x100000 (fx32) and enters phase 1.  Phase 1 with "no"
 * (+0x64 == 0): hides the prompt, brings the three slots back to x = 0, lays
 * out for phase 0 and returns to it (cancel sound).  Phase 1 with "yes": bumps
 * the save counter, starts the save into the chosen slot (a refused start sets
 * card state / sub-state 1), refreshes button 5, enters phase 2 with its
 * layout, hides the prompt and clears context field 95fc.  Phase 4: releases
 * the target slot (entry 0, -1).  Sound 1 for yes / other phases, 3 for no.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define SLOT_COUNT     3
#define SLOT_HIDDEN_X  0x100000
#define PHASE_PICK     0
#define PHASE_CONFIRM  1
#define PHASE_SAVING   2
#define PHASE_DONE     4
#define SOUND_SELECT   1
#define SOUND_CANCEL   3

typedef struct Ov008SaveSlotPos {
    int nX;                   /* 0x00 */
    int nPad;                 /* 0x04 */
} Ov008SaveSlotPos;

typedef struct Ov008SaveMenu {
    int nSlot;                /* 0x000: chosen slot */
    int nPhase;               /* 0x004 */
    u8  pad_008[0x64 - 0x8];
    int bConfirmYes;          /* 0x064 */
    u8  pad_068[0x140 - 0x68];
    Ov008SaveSlotPos aSlotPos[SLOT_COUNT]; /* 0x140 */
    u8  pad_158[0x23c - 0x158];
    int nState;               /* 0x23c */
    int nSubState;            /* 0x240 */
} Ov008SaveMenu;

extern int  func_ov025_02084a7c(void);                                   /* Ov008_GetContext */
extern void func_ov025_0209b138(int bPrompt, int bShow);                 /* confirm prompt */
extern void func_ov025_0209b7a4(Ov008SaveMenu *pMenu, int nPhase);       /* lay the menu out */
extern void func_02020904(void);                                         /* IncGlobalShort_0204bda0 */
extern int  func_ov025_02099b90(Ov008SaveMenu *pMenu, u32 nSlot);        /* Ov008_BeginSaveToSlot */
extern void func_ov025_020a4d94(int nArg);                               /* Ov008_UpdateMenuButton5 */
extern void func_ov025_02084868(int nValue);                             /* Ov008_SetCtxField95fc */
extern void func_ov025_02084798(int nEntry, int nTarget);                /* Ov008_SetTargetSlot */
extern void func_02033b78(int nKind, int nSound);                        /* PlaySound */

void func_ov025_0209ab08(Ov008SaveMenu *pMenu)
{
    int bYes;
    int i;

    bYes = 1;
    func_ov025_02084a7c();
    if (pMenu->nState != 0) {
        return;
    }
    switch (pMenu->nPhase) {
    case PHASE_PICK:
        func_ov025_0209b138(0, 1);
        func_ov025_0209b7a4(pMenu, PHASE_CONFIRM);
        pMenu->bConfirmYes = 0;
        for (i = 0; i < SLOT_COUNT; i++) {
            if (i == pMenu->nSlot) {
                pMenu->aSlotPos[i].nX = 0;
            } else {
                pMenu->aSlotPos[i].nX = SLOT_HIDDEN_X;
            }
        }
        pMenu->nPhase = PHASE_CONFIRM;
        break;
    case PHASE_CONFIRM:
        bYes = pMenu->bConfirmYes;
        if (bYes != 0) {
            func_02020904();
            if (func_ov025_02099b90(pMenu, pMenu->nSlot) == 0) {
                pMenu->nState = 1;
                pMenu->nSubState = 1;
            }
            func_ov025_020a4d94(0);
            pMenu->nPhase = PHASE_SAVING;
            func_ov025_0209b138(0, 0);
            func_ov025_0209b7a4(pMenu, PHASE_SAVING);
            func_ov025_02084868(0);
        } else {
            func_ov025_0209b138(1, 0);
            for (i = 0; i < SLOT_COUNT; i++) {
                pMenu->aSlotPos[i].nX = 0;
            }
            func_ov025_0209b7a4(pMenu, PHASE_PICK);
            pMenu->nPhase = PHASE_PICK;
        }
        break;
    case PHASE_DONE:
        func_ov025_02084798(0, -1);
        break;
    }
    func_02033b78(0, bYes != 0 ? SOUND_SELECT : SOUND_CANCEL);
}
