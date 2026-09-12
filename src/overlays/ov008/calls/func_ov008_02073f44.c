/* func_ov008_02073f44 -- Ov008_MissionListTouchConfirm: confirm the mission list
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

extern Ov008MissionList *func_ov008_02050cec(void);                       /* Ov008_GetPageB */
extern int func_ov008_02050c3c(void);                                     /* Ov008_GetCtxBlock954c */
extern void func_ov008_02055c24(int nBlock, void *pOut);                  /* copy the touch record */
extern int func_ov008_02050ff8(void);                                     /* Ov008_GetCtxObject9630 */
extern void func_ov008_02073c48(Ov008MissionList *pList);                 /* Ov008_MissionListConfirm */
extern void func_ov008_02071618(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov008_02073f44(void)
{
    Ov008TouchState touch;
    Ov008MissionList *pList;

    pList = func_ov008_02050cec();
    if (pList->bAnimating != 0 || pList->bSelectionPending != 0 || pList->bLocked != 0) {
        return;
    }
    func_ov008_02055c24(func_ov008_02050c3c(), &touch);
    if (touch.nTouching != 1 || touch.nPhase != 0) {
        return;
    }
    if (func_ov008_02050ff8() != 0) {
        return;
    }
    if (pList->bTouchEnabled == 0) {
        return;
    }
    if (pList->nSelected == NO_SELECTION) {
        func_ov008_02073c48(pList);
    } else {
        func_ov008_02071618(pList, -1, 1);
    }
}
