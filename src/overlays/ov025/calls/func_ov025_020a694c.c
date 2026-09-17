/* func_ov025_020a694c -- Ov025_MissionList_PlaceCursor: put entry 1 of the 4a80 block (02084a8c),
 * the selection cursor, on the selected row of the mission list: y = (row * 32 - the pixel
 * scroll +0xc) << 12, one row higher while a page transition is active (02084e38); with no
 * selection (+0 < 0) the cursor takes the off-screen offset data_ov025_020b4578
 * (Ov025_SetEntryOffset 02088564). */
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

extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_02088564(int nCtx, void *pEntry, UiLayoutPos *pOffset); /* Ov025_SetEntryOffset */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern const UiLayoutPos data_ov025_020b4578;                       /* the off-screen cursor offset */

void func_ov025_020a694c(Ov008MissionList *pList)
{
    int nCtx;

    nCtx = func_ov025_02084a8c();
    if (pList->nSelected >= 0) {
        UiLayoutPos pos = {0, 0};
        pos.y = (pList->nSelected * 32 - pList->nScroll) << 12;
        if (func_ov025_02084e38() != 0) {
            pos.y -= 32 << 12;
        }
        func_ov025_02088564(nCtx, func_ov025_0208843c(nCtx, 1), &pos);
    } else {
        UiLayoutPos hidden = data_ov025_020b4578;
        func_ov025_02088564(nCtx, func_ov025_0208843c(nCtx, 1), &hidden);
    }
}
