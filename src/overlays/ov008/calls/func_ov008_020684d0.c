/* func_ov008_020684d0 -- Ov008_StepSaveSlotLoad: drive one save slot's load
 * phase (byte +0x244).  Phase 0 clears the slot's menu entry, marks its mode
 * unknown (-1), starts the card read for the slot and moves to phase 1.  Phase 1
 * polls the read: result 3 (no card) ends the load with the menu forced to
 * entry 3 and the "back" state armed; any other non-negative result builds the
 * entry from it.  Either way phase 2 is "done".  Returns the phase.
 */
typedef unsigned char u8;

#define ENTRY_COUNT 3

typedef struct Ov008SaveEntry {
    u8  pad_00[0x10];
    int nMode;                /* 0x10: -1 = unknown */
    u8  pad_14[0x1c - 0x14];
} Ov008SaveEntry;

typedef struct Ov008SaveMenu {
    u8  pad_000[0x8];
    int nCursor;              /* 0x008 */
    u8  pad_00c[4];
    Ov008SaveEntry aEntry[ENTRY_COUNT]; /* 0x010 */
    u8  pad_064[0x23c - 0x64];
    int nState;               /* 0x23c */
    int nSubState;            /* 0x240 */
    u8  nLoadPhase;           /* 0x244 */
} Ov008SaveMenu;

#define LOAD_PHASE_START 0
#define LOAD_PHASE_WAIT  1
#define LOAD_PHASE_DONE  2
#define READ_NO_CARD     3
#define MODE_UNKNOWN     -1

extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void func_ov008_02067794(Ov008SaveMenu *pMenu, int nSlot);             /* start the slot read */
extern int func_ov008_020676b4(Ov008SaveMenu *pMenu, int nSlot, int nPhase, int nArg); /* poll the slot read */
extern void func_ov008_0206836c(Ov008SaveMenu *pMenu, int nSlot, int nResult); /* Ov008_BuildSaveSlotEntry */

u8 func_ov008_020684d0(Ov008SaveMenu *pMenu, int nSlot, int nUnused, int nArg)
{
    int nResult;
    u8 nPhase;

    nPhase = pMenu->nLoadPhase;
    switch (nPhase) {
    case LOAD_PHASE_START:
        MI_CpuFill8(&pMenu->aEntry[nSlot], 0, sizeof(Ov008SaveEntry));
        pMenu->aEntry[nSlot].nMode = MODE_UNKNOWN;
        func_ov008_02067794(pMenu, nSlot);
        pMenu->nLoadPhase = LOAD_PHASE_WAIT;
        break;
    case LOAD_PHASE_WAIT:
        nResult = func_ov008_020676b4(pMenu, nSlot, nPhase, nArg);
        if (nResult == READ_NO_CARD) {
            pMenu->nLoadPhase = LOAD_PHASE_DONE;
            pMenu->nCursor = 3;
            pMenu->nState = 1;
            pMenu->nSubState = 0;
        } else if (nResult >= 0) {
            func_ov008_0206836c(pMenu, nSlot, nResult);
            pMenu->nLoadPhase = LOAD_PHASE_DONE;
        }
        break;
    }
    return pMenu->nLoadPhase;
}
