/* func_ov025_020a920c -- Ov008_MissionListConfirm: the mission list's "confirm"
 * handler.  Ignored while the list is animating.  With nothing selected and no
 * selection pending it opens the detail panel (confirm sound) and clears the two
 * scroll counters; with a selection pending but not yet armed it closes the panel
 * again (cancel sound); otherwise, unless a transfer is in flight but not
 * acknowledged, it runs the selection step.
 */
typedef unsigned char u8;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000: -1 = none */
    u8  pad_004[0x30 - 0x04];
    int nScrollA;             /* 0x030 */
    int nScrollB;             /* 0x034 */
    u8  pad_038[0x40 - 0x38];
    int bTransfer;            /* 0x040 */
    int bTransferAcked;       /* 0x044 */
    u8  pad_048[0x68 - 0x48];
    int bAnimating;           /* 0x068 */
    u8  pad_06c[0x4f8 - 0x6c];
    int bSelectionPending;    /* 0x4f8 */
    int bSelectionArmed;      /* 0x4fc */
} Ov008MissionList;

#define NO_SELECTION  -1
#define SOUND_CONFIRM 1
#define SOUND_CANCEL  3

extern void func_ov025_020a6fec(Ov008MissionList *pList, int bExpand);   /* detail panel slide */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov025_020a73e0(Ov008MissionList *pList);                 /* selection step */

void func_ov025_020a920c(Ov008MissionList *pList)
{
    if (pList->bAnimating != 0) {
        return;
    }
    if (pList->bSelectionPending == 0 && pList->nSelected == NO_SELECTION) {
        func_ov025_020a6fec(pList, 1);
        func_02033b78(0, SOUND_CONFIRM);
        pList->nScrollA = 0;
        pList->nScrollB = 0;
        return;
    }
    if (pList->bSelectionPending != 0 && pList->bSelectionArmed == 0) {
        func_ov025_020a6fec(pList, 0);
        func_02033b78(0, SOUND_CANCEL);
        return;
    }
    if (pList->bTransfer != 0 && pList->bTransferAcked == 0) {
        return;
    }
    func_ov025_020a73e0(pList);
}
