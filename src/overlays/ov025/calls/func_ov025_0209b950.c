/* func_ov025_0209b950 -- Ov008_DrawSaveSlotTexts: draw the text of the three
 * save slots on the slot text surface (+0x1dc).  A slot's origin is its layout
 * position (+0x128, 12.4) plus its animation offset (+0x68, 0x40 apart,
 * 12.4), 0x20 rows up.  A slot entry (+0x10, 0x1c each) in mode 2 (empty)
 * draws var record 0xc at (+0x37, +0xc) in style 4; in mode 1 (saved) seven
 * texts go on the row at +0x17 in style 2 at column 0x1b + offset: the day
 * (record 9, entry +2) at +2, the munny (record 4, entry +4) at +0x70, the
 * play time split into hours / minutes / seconds (entry +0xc, format
 * data_ov025_020b4ec4) at +0x89 / +0x92 / +0xa0, and the separator (record
 * 8) at +0x8c and +0x9a; shadows 0 / 1 / 1 / 2 / 2 / 1 / 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define SLOT_COUNT     3
#define TEXT_CAP       0x80
#define SLOT_COL_BASE  0x1b
#define MODE_SAVED     1
#define MODE_EMPTY     2

typedef struct MenuEntry {
    u16 wAt0;                 /* 0x00 */
    u16 nDay;                 /* 0x02 */
    int nMunny;               /* 0x04 */
    int nAt8;                 /* 0x08 */
    u32 nPlayTime;            /* 0x0c */
    int nMode;                /* 0x10 */
    int nAt14;                /* 0x14 */
    u32 nTier;                /* 0x18 */
} MenuEntry;

typedef struct Ov008SaveSlotAnim {
    int nX;                   /* 0x00: 12.4 */
    int nY;                   /* 0x04: 12.4 */
    u8  pad_08[0x40 - 8];
} Ov008SaveSlotAnim;

typedef struct Ov008SaveSlotPos {
    int nX;                   /* 0x00: 12.4 */
    int nY;                   /* 0x04: 12.4 */
} Ov008SaveSlotPos;

typedef struct Ov008SaveMenu {
    u8  pad_0000[0x10];
    MenuEntry aEntry[SLOT_COUNT]; /* 0x0010 */
    u8  pad_0064[4];
    Ov008SaveSlotAnim aSlotAnim[SLOT_COUNT]; /* 0x0068 */
    Ov008SaveSlotPos aSlotOrigin[SLOT_COUNT]; /* 0x0128 */
    u8  pad_0140[0x158 - 0x140];
    u8  varRecords[0xc];      /* 0x0158 */
    u8  pad_0164[0x1dc - 0x164];
    u8  slotTextSurface[0x3c];  /* 0x01dc */
} Ov008SaveMenu;

extern const u16 data_ov025_020b4ec4[];                                  /* "%d"-style number format */
extern int   func_ov025_02084a7c(void);                                  /* Ov008_GetContext */
extern void  func_02030158(void *pSurface);                              /* Obj_InvokeInnerVtable4 */
extern u16  *func_ov025_02089894(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern void  func_ov025_0209a500(void *pSurface, int nX, int nY, int nStyle, const u16 *pText, int nShadow); /* Ov008_DrawWithShadow */
extern void  func_ov025_02099cb4(u32 nTime, u16 *pHours, u8 *pMinutes, u8 *pSeconds); /* ov008_SplitTimeUnitsHMS */
extern void  func_020262a0(u16 *pDst, int nCap, const u16 *pFormat, ...); /* Text_FormatUtf16 */

void func_ov025_0209b950(Ov008SaveMenu *pMenu)
{
    u16 aText[TEXT_CAP];
    u16 nHours;
    u8  nSeconds;
    u8  nMinutes;
    int nSlot;
    MenuEntry *pEntry;
    int nX;
    int nY;
    int i;
    int nCol;
    int nShadow;
    int nOffset;

    nShadow = 0;
    func_ov025_02084a7c();
    func_02030158(pMenu->slotTextSurface);
    pEntry = pMenu->aEntry;
    for (nSlot = 0; nSlot < SLOT_COUNT; nSlot++, pEntry++) {
        nX = (pMenu->aSlotAnim[nSlot].nX >> 12) + (pMenu->aSlotOrigin[nSlot].nX >> 12);
        nY = (pMenu->aSlotAnim[nSlot].nY >> 12) + (pMenu->aSlotOrigin[nSlot].nY >> 12) - 0x20;
        if (pEntry->nMode == MODE_EMPTY) {
            func_ov025_0209a500(pMenu->slotTextSurface, nX + 0x37, nY + 0xc, 4, func_ov025_02089894(pMenu->varRecords, 0xc), 0);
        } else if (pEntry->nMode == MODE_SAVED) {
            func_ov025_02099cb4(pEntry->nPlayTime, &nHours, &nMinutes, &nSeconds);
            for (i = 0; i < 7; i++) {
                nCol = SLOT_COL_BASE;
                switch (i) {
                case 0:
                    func_020262a0(aText, TEXT_CAP, func_ov025_02089894(pMenu->varRecords, 9), pEntry->nDay);
                    nCol += 2;
                    nShadow = 0;
                    break;
                case 1:
                    func_020262a0(aText, TEXT_CAP, func_ov025_02089894(pMenu->varRecords, 4), pEntry->nMunny);
                    nCol += 0x70;
                    nShadow = 1;
                    break;
                case 2:
                    nCol += 0x89;
                    func_020262a0(aText, TEXT_CAP, data_ov025_020b4ec4, nHours);
                    nShadow = 1;
                    break;
                case 3:
                    nCol += 0x92;
                    func_020262a0(aText, TEXT_CAP, data_ov025_020b4ec4, nMinutes);
                    nShadow = 2;
                    break;
                case 4:
                    nCol += 0xa0;
                    func_020262a0(aText, TEXT_CAP, data_ov025_020b4ec4, nSeconds);
                    nShadow = 2;
                    break;
                case 5:
                case 6:
                    if (i == 5) {
                        nOffset = 0x8c;
                    } else {
                        nOffset = 0x9a;
                    }
                    func_020262a0(aText, TEXT_CAP, func_ov025_02089894(pMenu->varRecords, 8));
                    nCol += nOffset;
                    nShadow = 1;
                    break;
                }
                func_ov025_0209a500(pMenu->slotTextSurface, nX + nCol, nY + 0x17, 2, aText, nShadow);
            }
        }
    }
}
