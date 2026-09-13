/* func_ov008_02070c58 -- Ov008_UpdateMissionListArrows: show or hide the
 * mission list's page arrows.  Counts how many of the twelve cursor picks
 * (0205b720 with 0..11) leave a non-empty entry count, restores the pick to
 * the list's cursor slot (+0x54), and wants the arrows shown when at least
 * two pages have entries and the list state (0205b7b4) is not 7.  Widgets 4
 * and 5 of the context and 0x47 / 0x48 of block 4a80 are then set visible
 * only when their current visibility (field 0x84 bit 1) differs.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define PICK_COUNT     12
#define LIST_STATE_END 7

typedef struct Ov008MissionList {
    u8  pad_00[0x54];
    u8  nCursorSlot;          /* 0x54 */
} Ov008MissionList;

extern void func_ov008_0205b720(int nSlot);                              /* cursor pick */
extern u16  func_ov008_0205b708(void);                                   /* mission entry count */
extern int  func_ov008_0205b7b4(void);                                   /* list state */
extern int  func_ov008_02050c54(void);                                   /* Ov008_GetContext */
extern int  func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void *func_ov008_02054788(int nCtx, int nId);                     /* FindEntryById */
extern int  func_ov008_02054810(int nCtx, void *pEntry);                 /* ov008_GetField84Bit1: visible */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);   /* SetEntrySlotsVisible */

void func_ov008_02070c58(Ov008MissionList *pList)
{
    int bShow;
    int nPages;
    int i;
    int nCtx;
    int bVisibleA;
    int bVisibleB;

    nPages = 0;
    bShow = 1;
    for (i = 0; i < PICK_COUNT; i++) {
        func_ov008_0205b720((u16)i);
        if (func_ov008_0205b708() != 0) {
            nPages++;
        }
    }
    func_ov008_0205b720(pList->nCursorSlot);
    if (nPages < 2) {
        bShow = 0;
    }
    if (func_ov008_0205b7b4() == LIST_STATE_END) {
        bShow = 0;
    }
    nCtx = func_ov008_02050c54();
    bVisibleA = func_ov008_02054810(nCtx, func_ov008_02054788(nCtx, 4)) != 0;
    bVisibleB = func_ov008_02054810(nCtx, func_ov008_02054788(nCtx, 5)) != 0;
    if (bShow != bVisibleA) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 4), bShow);
    }
    if (bShow != bVisibleB) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 5), bShow);
    }
    nCtx = func_ov008_02050c64();
    bVisibleA = func_ov008_02054810(nCtx, func_ov008_02054788(nCtx, 0x47)) != 0;
    bVisibleB = func_ov008_02054810(nCtx, func_ov008_02054788(nCtx, 0x48)) != 0;
    if (bShow != bVisibleA) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x47), bShow);
    }
    if (bShow != bVisibleB) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, 0x48), bShow);
    }
}
