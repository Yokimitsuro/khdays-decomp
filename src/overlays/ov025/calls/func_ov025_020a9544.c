/* func_ov025_020a9544 -- Ov008_MissionListTouchConfirm: confirm the mission list
 * from a fresh touch.  Only while the list is idle (not animating, no selection
 * pending, no lock), the pad/touch record reports a fresh touch (touching == 1,
 * phase 0), no modal object is up and the list accepts touches: with nothing
 * selected it runs the confirm handler, otherwise it commits word -1 with target 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000: -1 = none */
    u8  pad_004[0x38 - 0x04];
    int bTouchEnabled;        /* 0x038 */
    u8  pad_03c[0x68 - 0x3c];
    int bAnimating;           /* 0x068 */
    u8  pad_06c[0x4f8 - 0x6c];
    int bSelectionPending;    /* 0x4f8 */
    int bSelectionArmed;      /* 0x4fc */
    int bLocked;              /* 0x500 */
} Ov008MissionList;

typedef struct Ov008TouchState {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
    u16 nPhase;               /* 0x06 */
} Ov008TouchState;

#define NO_SELECTION -1

extern Ov008MissionList *func_ov025_02084b14(void);                       /* Ov008_GetPageB */
extern int func_ov025_02084a64(void);                                     /* Ov008_GetCtxBlock954c */
extern void func_ov025_02089834(int nBlock, void *pOut);                  /* copy the touch record */
extern int func_ov025_02084e08(void);                                     /* Ov008_GetCtxObject9630 */
extern void func_ov025_020a920c(Ov008MissionList *pList);                 /* Ov008_MissionListConfirm */
extern void func_ov025_020a6b10(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov025_020a9544(void)
{
    Ov008TouchState touch;
    Ov008MissionList *pList;

    pList = func_ov025_02084b14();
    if (pList->bAnimating != 0 || pList->bSelectionPending != 0 || pList->bLocked != 0) {
        return;
    }
    func_ov025_02089834(func_ov025_02084a64(), &touch);
    if (touch.nTouching != 1 || touch.nPhase != 0) {
        return;
    }
    if (func_ov025_02084e08() != 0) {
        return;
    }
    if (pList->bTouchEnabled == 0) {
        return;
    }
    if (pList->nSelected == NO_SELECTION) {
        func_ov025_020a920c(pList);
    } else {
        func_ov025_020a6b10(pList, -1, 1);
    }
}
