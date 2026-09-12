/* func_ov008_02073e58 -- Ov008_MissionListTouchRow: pick a mission row from a
 * fresh touch.  Only while the list is idle (not animating, no selection
 * pending, not locked) and the touch record reports a fresh touch.  A touch at
 * x >= 0xe0 flags the scroll-bar drag (nScrollA) instead.  Otherwise the row is
 * (scroll + y - top) / 32, provided the touch is above the list's bottom margin
 * (top + height - 2) and the row exists: touching the selected row confirms it,
 * any other row selects it; nScrollB is flagged either way.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000: -1 = none */
    u8  pad_004[0x0c - 0x04];
    int nScroll;              /* 0x00c */
    u8  pad_010[4];
    int nTop;                 /* 0x014 */
    int nHeight;              /* 0x018 */
    u8  pad_01c[0x30 - 0x1c];
    int nScrollA;             /* 0x030 */
    int nScrollB;             /* 0x034 */
    u8  pad_038[0x68 - 0x38];
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

#define SCROLLBAR_X 0xe0
#define ROW_HEIGHT  32

extern Ov008MissionList *func_ov008_02050cec(void);                       /* Ov008_GetPageB */
extern int func_ov008_02050c3c(void);                                     /* Ov008_GetCtxBlock954c */
extern void func_ov008_02055c24(int nBlock, void *pOut);                  /* copy the touch record */
extern u16 func_ov008_0205b708(void);                                     /* mission entry count */
extern void func_ov008_02073c48(Ov008MissionList *pList);                 /* Ov008_MissionListConfirm */
extern void func_ov008_02071618(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov008_02073e58(void)
{
    Ov008TouchState touch;
    Ov008MissionList *pList;
    int nRow;

    pList = func_ov008_02050cec();
    if (pList->bAnimating != 0 || pList->bSelectionPending != 0 || pList->bLocked != 0) {
        return;
    }
    func_ov008_02055c24(func_ov008_02050c3c(), &touch);
    if (touch.nTouching != 1 || touch.nPhase != 0) {
        return;
    }
    if (touch.nX < SCROLLBAR_X) {
        nRow = (pList->nScroll + (touch.nY - pList->nTop)) / ROW_HEIGHT;
        if (touch.nY < pList->nTop + pList->nHeight - 2) {
            if (nRow < func_ov008_0205b708()) {
                if (pList->nSelected == nRow) {
                    func_ov008_02073c48(pList);
                } else {
                    func_ov008_02071618(pList, nRow, 0);
                }
                pList->nScrollB = 1;
            }
        }
    } else {
        pList->nScrollA = 1;
    }
}
