/* func_ov008_02071508 -- Ov008_UpdateListCursorCells: refresh the mission list's
 * cursor cells on the ctx tracker (block 954c).  Without a modal object and with
 * touch enabled: a selection shows the cursor cell (tag 1), none (and not
 * animating) shows the idle cell (tag 9).  A valid word-1 shows tag 8 with frame
 * 2 at row * 4 (as a short); a selection (not animating) puts tag 7 at
 * (selection - scroll / 32) * 4, remembering that row at +8.  Always marks
 * the cells refreshed (+0x4c).
 */
typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    int nWord1;               /* 0x004 */
    int nCursorRow;           /* 0x008 */
    int nScroll;              /* 0x00c */
    u8  pad_010[0x38 - 0x10];
    int bTouchEnabled;        /* 0x038 */
    u8  pad_03c[0x4c - 0x3c];
    int bCellsRefreshed;      /* 0x04c */
    u8  pad_050[0x68 - 0x50];
    int bAnimating;           /* 0x068 */
} Ov008MissionList;

#define ROW_HEIGHT 32
#define TAG_CURSOR 1
#define TAG_IDLE   9
#define TAG_WORD   8
#define TAG_SELECT 7

extern int  func_ov008_02050c64(void);                                    /* Ov008_GetCtxBlock4a80 */
extern int  func_ov008_02050c3c(void);                                    /* Ov008_GetCtxBlock954c */
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern int  func_ov008_02055808(int nTracker, int nTag);                  /* ov008_FindEntryByTag */
extern void func_ov008_0205589c(int nTracker, int nCell);                 /* Ov008_TagTracker_InvokeCallback */
extern void func_ov008_020558b8(int nTracker, int nCell, int nFrame, short nY); /* Ov008_ApplyTempFieldsAndRestore */

void func_ov008_02071508(Ov008MissionList *pList)
{
    int nTracker;
    int nFirst;
    int nRow;

    func_ov008_02050c64();
    nTracker = func_ov008_02050c3c();
    if (func_ov008_02050ff8() == 0 && pList->bTouchEnabled != 0) {
        if (pList->nSelected >= 0) {
            func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, TAG_CURSOR));
        }
        if (pList->nSelected < 0 && pList->bAnimating == 0) {
            func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, TAG_IDLE));
        }
    }
    if (pList->nWord1 >= 0) {
        func_ov008_020558b8(nTracker, func_ov008_02055808(nTracker, TAG_WORD), 2, (short)(pList->nCursorRow * 4));
    }
    nFirst = pList->nScroll / ROW_HEIGHT;
    if (pList->nSelected >= 0 && pList->bAnimating == 0) {
        nRow = pList->nSelected - nFirst;
        func_ov008_020558b8(nTracker, func_ov008_02055808(nTracker, TAG_SELECT), 2, (short)(nRow * 4));
        pList->nCursorRow = nRow;
    }
    pList->bCellsRefreshed = 1;
}
