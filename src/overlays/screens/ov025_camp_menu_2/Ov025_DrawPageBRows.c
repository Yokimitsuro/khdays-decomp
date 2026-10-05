/* Ov025_DrawPageBRows -- Ov008_DrawPageBRows: redraw page B's seven text
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

#include "nitro/types.h"

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

extern Ov008PageB *Ov025_GetPageB(void);                             /* Ov008_GetPageB */
extern void  Obj_InvokeInnerVtable4(void *pSurface);                               /* Obj_InvokeInnerVtable4: clear */
extern u16  *Ov025_Res_GetDataBlock(void *pList);                            /* entry name */
extern void  Ov025_DrawStyledTextWithShadow(void *pSurface, const u16 *pText, int nX, int nY, u8 nStyle, int bShadow); /* Ov008_DrawStyledTextWithShadow */
extern u16  *Ov025_GetVarRecordByIndex(void *pRecords, int nIndex);             /* GetVarRecordByIndex */
extern short Ov025_Res_GetCount(void *pList);                            /* list entry count */
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...); /* Text_FormatUtf16 */
extern u16  *Ov025_NextStreamRecord(void *pList);                            /* entry text */
extern int   Ov025_CountWideStringLines(const u16 *pText);                       /* CountWideStringLines */
extern void  Ov025_ForwardConfigured(void *pSurface, const u16 *pText, int nX, int nY); /* Ov008_ForwardConfigured */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GXS_LoadBG3Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  Ov025_MarkSlotUsed(int nSlot);                              /* Ov008_MarkSlotUsed */

void Ov025_DrawPageBRows(void)
{
    u16 text[TEXT_CAP];
    u8 i;
    u16 *pText;
    Ov008PageB *pPage;
    int nY;

    pPage = Ov025_GetPageB();
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
        Obj_InvokeInnerVtable4(&pPage->aRow[i]);
        switch (i) {
        case 0:
            Ov025_DrawStyledTextWithShadow(&pPage->aRow[i], Ov025_Res_GetDataBlock(pPage->list), 0x58, 6, 2, 1);
            break;
        case 1:
            Text_FormatUtf16(text, TEXT_CAP, Ov025_GetVarRecordByIndex(pPage->textCache, 0), pPage->nRow + 1, Ov025_Res_GetCount(pPage->list));
            Ov025_DrawStyledTextWithShadow(&pPage->aRow[i], text, 3, 6, 2, 0);
            break;
        case 2:
            pText = Ov025_NextStreamRecord(pPage->list);
            nY = Ov025_CountWideStringLines(pText) > 1 ? 0 : 5;
            Ov025_ForwardConfigured(&pPage->aRow[i], pText, 0, nY + 4);
            break;
        case 3:
            pText = Ov025_NextStreamRecord(pPage->list);
            nY = Ov025_CountWideStringLines(pText) > 1 ? 0 : 5;
            Ov025_ForwardConfigured(&pPage->aRow[i], pText, 0, nY + 2);
            break;
        case 4:
            Ov025_ForwardConfigured(&pPage->aRow[i], Ov025_NextStreamRecord(pPage->list), 5, 2);
            break;
        case 5:
            Ov025_ForwardConfigured(&pPage->aRow[i], Ov025_NextStreamRecord(pPage->list), 5, 6);
            break;
        case 6:
            Ov025_ForwardConfigured(&pPage->aRow[i], Ov025_NextStreamRecord(pPage->list), 5, 2);
            break;
        }
        DC_FlushRange(pPage->aRow[i].pCurrent->pPixels, pPage->aRow[i].nTotalBytes);
        GXS_LoadBG3Char(pPage->aRow[i].pCurrent->pPixels, pPage->aRow[i].nRowBytes, pPage->aRow[i].nTotalBytes);
    }
    Ov025_MarkSlotUsed(0x1b);
}
