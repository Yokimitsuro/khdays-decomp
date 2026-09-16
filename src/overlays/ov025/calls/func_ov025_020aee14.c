/* func_ov025_020aee14 -- Ov008_DrawPageBRows: redraw page B's seven text
 * rows (+0x38, 0x3c each) into the sub engine's BG3 characters.  In mode
 * 0x11 (+0x0) every row but 3 is drawn, in any other mode only rows 0..3.
 * Each drawn row is cleared and filled from the ov025 list (+0x200): row 0
 * the entry name (0848) at x = 0x58 with shadow, row 1 "row / total"
 * (variable record 0 formatted with +0x1e8 + 1 and the list count) at x =
 * 3, rows 2 / 3 the entry text (0864) at y = 4 / 2 plus 5 while it has a
 * single line, rows 4..6 the entry text at x = 5, y = 2 / 6 / 2.  The row's
 * pixels are flushed and uploaded at its character offset; slot 0x1b is
 * then marked used.
 * Codegen: the row-1 text pointer is passed straight from the cache call
 * (a pText local there ages the page pointer's register); pPage is declared
 * after the counter, the text buffer and pText (20 of 120 orders match).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT   7
#define MODE_FULL   0x11
#define TEXT_CAP    0x80

typedef struct TileSurfaceObj {
    u8    pad_00[0x20];
    void *pPixels;            /* 0x20 */
} TileSurfaceObj;

typedef struct TileSurface {
    u8   pad_00[0xc];
    int  nTotalBytes;         /* 0x0c */
    int  nRowBytes;           /* 0x10: upload offset */
    u8   pad_14[4];
    TileSurfaceObj *pCurrent; /* 0x18 */
    u8   pad_1c[0x3c - 0x1c];
} TileSurface;

typedef struct Ov008PageB {
    int nMode;                /* 0x000 */
    u8  pad_004[0x38 - 0x4];
    TileSurface aRow[ROW_COUNT]; /* 0x038 */
    u8  textCache[0xc];       /* 0x1dc */
    int nRow;                 /* 0x1e8 */
    u8  pad_1ec[0x200 - 0x1ec];
    u8  list[4];              /* 0x200: ov025 list */
} Ov008PageB;

extern Ov008PageB *func_ov025_02084b14(void);                             /* Ov008_GetPageB */
extern void  func_02030158(void *pSurface);                               /* Obj_InvokeInnerVtable4: clear */
extern u16  *func_ov025_020b0848(void *pList);                            /* entry name */
extern void  func_ov025_020aed34(void *pSurface, const u16 *pText, int nX, int nY, u8 nStyle, int bShadow); /* Ov008_DrawStyledTextWithShadow */
extern u16  *func_ov025_02089894(void *pRecords, int nIndex);             /* GetVarRecordByIndex */
extern short func_ov025_020b0850(void *pList);                            /* list entry count */
extern void  func_020262a0(u16 *pDst, int nCap, const u16 *pTemplate, ...); /* Text_FormatUtf16 */
extern u16  *func_ov025_020b0864(void *pList);                            /* entry text */
extern int   func_ov025_020aedbc(const u16 *pText);                       /* CountWideStringLines */
extern void  func_ov025_020aede8(void *pSurface, const u16 *pText, int nX, int nY); /* Ov008_ForwardConfigured */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GXS_LoadBG3Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  func_ov025_02084964(int nSlot);                              /* Ov008_MarkSlotUsed */

void func_ov025_020aee14(void)
{
    u16 text[TEXT_CAP];
    u8 i;
    u16 *pText;
    Ov008PageB *pPage;
    int nY;

    pPage = func_ov025_02084b14();
    for (i = 0; i < ROW_COUNT; i++) {
        if (pPage->nMode == MODE_FULL) {
            if (i != 3) {
                goto draw;
            }
        } else if (i < 4 || i > 6) {
            goto draw;
        }
        continue;
    draw:
        func_02030158(&pPage->aRow[i]);
        switch (i) {
        case 0:
            func_ov025_020aed34(&pPage->aRow[i], func_ov025_020b0848(pPage->list), 0x58, 6, 2, 1);
            break;
        case 1:
            func_020262a0(text, TEXT_CAP, func_ov025_02089894(pPage->textCache, 0), pPage->nRow + 1, func_ov025_020b0850(pPage->list));
            func_ov025_020aed34(&pPage->aRow[i], text, 3, 6, 2, 0);
            break;
        case 2:
            pText = func_ov025_020b0864(pPage->list);
            nY = func_ov025_020aedbc(pText) > 1 ? 0 : 5;
            func_ov025_020aede8(&pPage->aRow[i], pText, 0, nY + 4);
            break;
        case 3:
            pText = func_ov025_020b0864(pPage->list);
            nY = func_ov025_020aedbc(pText) > 1 ? 0 : 5;
            func_ov025_020aede8(&pPage->aRow[i], pText, 0, nY + 2);
            break;
        case 4:
            func_ov025_020aede8(&pPage->aRow[i], func_ov025_020b0864(pPage->list), 5, 2);
            break;
        case 5:
            func_ov025_020aede8(&pPage->aRow[i], func_ov025_020b0864(pPage->list), 5, 6);
            break;
        case 6:
            func_ov025_020aede8(&pPage->aRow[i], func_ov025_020b0864(pPage->list), 5, 2);
            break;
        }
        DC_FlushRange(pPage->aRow[i].pCurrent->pPixels, pPage->aRow[i].nTotalBytes);
        GXS_LoadBG3Char(pPage->aRow[i].pCurrent->pPixels, pPage->aRow[i].nRowBytes, pPage->aRow[i].nTotalBytes);
    }
    func_ov025_02084964(0x1b);
}
