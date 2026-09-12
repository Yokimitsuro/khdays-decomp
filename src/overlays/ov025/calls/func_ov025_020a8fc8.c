/* func_ov025_020a8fc8 -- Ov008_MissionListKeyUp: move the mission list's
 * selection up one entry when UP is the only direction key held.  Ignored
 * while animating, with a selection pending or while either scroll counter is
 * live; with touch disabled the list needs at least two entries.  Above the first
 * entry the selection wraps to the last one: from "none" (-1) with touch enabled,
 * from entry 0 with touch disabled, and from either when a modal object is up.
 * Nothing happens if the target is the current selection.
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
#define KEY_UP       0x40

extern u16 data_0204c18c;                                                 /* held keys */
extern u16 func_ov025_0208dc74(void);                                     /* mission entry count */
extern int func_ov025_02084e08(void);                                     /* Ov008_GetCtxObject9630 */
extern void func_ov025_020a6b10(Ov008MissionList *pList, u32 nWord, int nTarget);

void func_ov025_020a8fc8(Ov008MissionList *pList)
{
    int nNext;
    int nCurrent;
    int nCount;

    nCurrent = pList->nSelected;
    nNext = nCurrent - 1;
    if (pList->bAnimating != 0 || pList->bSelectionPending != 0 || pList->nScrollA != 0 || pList->nScrollB != 0) {
        return;
    }
    if ((data_0204c18c & KEY_DIR_MASK) != KEY_UP) {
        return;
    }
    nCount = func_ov025_0208dc74();
    if (pList->bTouchEnabled == 0 && nCount <= 1) {
        return;
    }
    if (func_ov025_02084e08() == 0) {
        if ((pList->bTouchEnabled != 0 && nNext < NO_SELECTION) || (pList->bTouchEnabled == 0 && nNext < 0)) {
            nNext = nCount - 1;
        }
    } else if (nNext < 0) {
        nNext = nCount - 1;
    }
    if (nCurrent != nNext) {
        func_ov025_020a6b10(pList, nNext, 0);
    }
}
