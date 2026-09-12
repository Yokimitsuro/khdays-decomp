/* func_ov008_02073cec -- Ov008_MissionListBack: the mission list's "back" handler.
 * Ignored while the list is animating (+0x68).  With a selection pending (+0x4f8)
 * it drops the armed flag, collapses the detail panel and plays the cancel sound.
 * Otherwise, unless a transfer is in flight but not acknowledged, it resets the
 * shared mode record (flag bytes 0, timer 10000, extra 0), marks the save record's
 * byte 0x4f, clears the target slot and plays the cancel sound.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008MissionList {
    u8  pad_000[0x40];
    int bTransfer;            /* 0x040 */
    int bTransferAcked;       /* 0x044 */
    u8  pad_048[0x68 - 0x48];
    int bAnimating;           /* 0x068 */
    u8  pad_06c[0x4f8 - 0x6c];
    int bSelectionPending;    /* 0x4f8 */
    int bSelectionArmed;      /* 0x4fc */
} Ov008MissionList;

typedef struct GameMode {
    u8  nFlags;               /* 0x00: bit 2 = story mode */
    u8  nSub;                 /* 0x01 */
    u16 nTimer;               /* 0x02 */
    u16 nExtra;               /* 0x04 */
} GameMode;

#define MODE_TIMER_RESET 10000
#define SOUND_CANCEL     3

extern GameMode data_0204c240;
extern u8 data_0204c300[];
extern void func_ov008_02071ac8(Ov008MissionList *pList, int bExpand);   /* detail panel slide */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov008_02050970(int nEntry, int nTarget);                 /* Ov008_SetTargetSlot */

void func_ov008_02073cec(Ov008MissionList *pList)
{
    if (pList->bAnimating != 0) {
        return;
    }
    if (pList->bSelectionPending != 0) {
        pList->bSelectionArmed = 0;
        func_ov008_02071ac8(pList, 0);
        func_02033b78(0, SOUND_CANCEL);
        return;
    }
    if (pList->bTransfer != 0 && pList->bTransferAcked == 0) {
        return;
    }
    data_0204c240.nTimer = MODE_TIMER_RESET;
    data_0204c240.nExtra = 0;
    data_0204c240.nSub = 0;
    data_0204c240.nFlags = 0;
    data_0204c300[0x4f] = 1;
    func_ov008_02050970(0, -1);
    func_02033b78(0, SOUND_CANCEL);
}
