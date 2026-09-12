/* func_ov025_020a9090 -- Ov008_MissionListKeyDown: move the mission list's
 * selection down one entry when DOWN is the only direction key held.  Ignored
 * while animating, with a selection pending or while either scroll counter is
 * live; with touch disabled the list needs at least two entries.  Past the last
 * entry the selection wraps to "none" (-1), or to the first entry when a modal
 * object is up or touch is disabled.  Nothing happens if the target is the
 * current selection.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000: -1 = none */
    u8  pad_004[0x30 - 0x04];
    int nScrollA;             /* 0x030 */
    int nScrollB;             /* 0x034 */
    int bTouchEnabled;        /* 0x038 */
    u8  pad_03c[0x68 - 0x3c];
    int bAnimating;           /* 0x068 */
    u8  pad_06c[0x4f8 - 0x6c];
    int bSelectionPending;    /* 0x4f8 */
} Ov008MissionList;

#define NO_SELECTION -1
#define KEY_DIR_MASK 0xf0
#define KEY_DOWN     0x80

extern u16 data_0204c18c;                                                 /* held keys */
extern u16 func_ov025_0208dc74(void);                                     /* mission entry count */
extern int func_ov025_02084e08(void);                                     /* Ov008_GetCtxObject9630 */
extern void func_ov025_020a6b10(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov025_020a9090(Ov008MissionList *pList)
{
    int nNext;
    int nCurrent;
    int nCount;

    nCurrent = pList->nSelected;
    nNext = nCurrent + 1;
    if (pList->bAnimating != 0 || pList->bSelectionPending != 0 || pList->nScrollA != 0 || pList->nScrollB != 0) {
        return;
    }
    if ((data_0204c18c & KEY_DIR_MASK) != KEY_DOWN) {
        return;
    }
    nCount = func_ov025_0208dc74();
    if (pList->bTouchEnabled == 0 && nCount <= 1) {
        return;
    }
    if (nNext >= nCount) {
        nNext = NO_SELECTION;
        if (func_ov025_02084e08() == 0) {
            if (pList->bTouchEnabled == 0) {
                nNext = 0;
            }
        } else {
            nNext = 0;
        }
    }
    if (nCurrent != nNext) {
        func_ov025_020a6b10(pList, nNext, 0);
    }
}
