/* func_ov025_020a61fc -- Ov025_MissionList_ShowSlotArrows: count the slots of the twelve that
 * have missions (select each with Ov025_SelectMissionSlot 0208dc8c and read the entry count
 * 0208dc74), reselect the cursor's slot (+0x54) and, with two or more, show entries 4 / 5 of the
 * 4a7c block (02084a7c) and 0x47 / 0x48 of the 4a80 block (02084a8c): the slot arrows
 * (FindEntryById 0208843c / SetEntrySlotsVisible 0208884c). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008MissionList {
    int  nSelected;           /* 0x000 */
    int  nPrevSelected;       /* 0x004 */
    int  nCursorRow;          /* 0x008 */
    int  nScroll;             /* 0x00c: in pixels, 32 a row */
    u8   pad_010[0x54 - 0x10];
    u8   nCursorSlot;         /* 0x054: the accepted slot the cursor is on */
} Ov008MissionList;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

extern void  func_ov025_0208dc8c(int nSlot);                        /* Ov025_SelectMissionSlot */
extern u16   func_ov025_0208dc74(void);                             /* Ov025_MissionSlotEntryCount */
extern int   func_ov025_02084a7c(void);                             /* Ov008_GetCtxBlock4a7c */
extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */

void func_ov025_020a61fc(Ov008MissionList *pList)
{
    int nAccepted;
    int i;
    int nCtx;

    nAccepted = 0;
    for (i = 0; i < 12; i++) {
        func_ov025_0208dc8c((u16)i);
        if (func_ov025_0208dc74() != 0) {
            nAccepted++;
        }
    }
    func_ov025_0208dc8c(pList->nCursorSlot);
    if (nAccepted < 2) {
        return;
    }
    nCtx = func_ov025_02084a7c();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 4), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 5), 1);
    nCtx = func_ov025_02084a8c();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x47), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x48), 1);
}
