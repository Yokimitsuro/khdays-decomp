/* func_ov025_020970bc -- Ov008_GridMenuCancel: the grid menu's cancel
 * button, by state (+0x10).  State 0 (list): with the A key held (held-key
 * word bit 0) the dragged node is dropped (020617e0 1; sound 0x36, or 4 when
 * refused, only while +0x44 is still clear) and +0x44 set; otherwise state 1
 * is entered, the +0x30 word cleared and the cursor moved to the cursor cell.
 * State 1 (grid): while +0x34 is set the same A-key drop applies, else the
 * drag is reset (020615dc 0) with +0x30 cleared and the cursor moved; without
 * +0x34, the B key (bit 1) removes the node under the cursor from the visible
 * page (+0x18) setting +0x38 with sound 0x37, and without B the +0x30 word is
 * cleared and, unless +0x38, a secondary panel (+0x4c) enters state 2 with
 * sound 0x35.  State 2 (drag): +0x30 cleared and the selected row (+0x9c)
 * re-selected; failure highlights row 0 and clears the selection.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define STATE_LIST 0
#define STATE_GRID 1
#define STATE_DRAG 2
#define KEY_A      1
#define KEY_B      2
#define SOUND_REFUSE 4
#define SOUND_ENTER  0x35
#define SOUND_DROP   0x36
#define SOUND_REMOVE 0x37

typedef struct Ov008MenuContext {
    u8  pad_0000[0x10];
    int menuState;            /* 0x0010 */
    u8  pad_0014[4];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x30 - 0x1c];
    int nBusyWord;            /* 0x0030 */
    int bHolding;             /* 0x0034 */
    int bMoveArmed;           /* 0x0038 */
    u8  pad_003c[8];
    int nHoldCount;           /* 0x0044 */
    u8  pad_0048[4];
    int bSecondaryPanel;      /* 0x004c */
    u8  pad_0050[0x64 - 0x50];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x9c - 0x68];
    int nSelectedRow;         /* 0x009c */
} Ov008MenuContext;

extern u16  data_0204c18c;                                                /* held keys */
extern int  func_ov025_02093d0c(Ov008MenuContext *pCtx, int nArg);        /* drop the dragged node */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nState);      /* Ov008_EnterMenuState */
extern int  func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int bRestore);    /* Ov008_ResetGridDrag */
extern int  func_ov025_0209446c(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent); /* Ov008_RemoveGridNode */
extern int  func_ov025_020947b4(Ov008MenuContext *pCtx, int nRow);        /* Ov008_SelectListRow */
extern void func_ov025_020915d4(Ov008MenuContext *pCtx, int nRow);        /* Ov008_HighlightListRow */

void func_ov025_020970bc(Ov008MenuContext *pCtx)
{
    switch (pCtx->menuState) {
    case STATE_LIST:
        if (data_0204c18c & KEY_A) {
            if (func_ov025_02093d0c(pCtx, 1) != 0) {
                if (pCtx->nHoldCount == 0) {
                    func_02033b78(0, SOUND_DROP);
                }
            } else if (pCtx->nHoldCount == 0) {
                func_02033b78(0, SOUND_REFUSE);
            }
            pCtx->nHoldCount = 1;
        } else {
            func_ov025_020956f8(pCtx, STATE_GRID);
            pCtx->nBusyWord = 0;
            func_ov025_02094988(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        }
        break;
    case STATE_GRID:
        if (pCtx->bHolding != 0) {
            if (data_0204c18c & KEY_A) {
                if (func_ov025_02093d0c(pCtx, 1) != 0) {
                    if (pCtx->nHoldCount == 0) {
                        func_02033b78(0, SOUND_DROP);
                    }
                } else if (pCtx->nHoldCount == 0) {
                    func_02033b78(0, SOUND_REFUSE);
                }
                pCtx->nHoldCount = 1;
            } else {
                func_ov025_02093b08(pCtx, 0);
                pCtx->nBusyWord = 0;
                func_ov025_02094988(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
            }
        } else if (data_0204c18c & KEY_B) {
            if (func_ov025_0209446c(pCtx, pCtx->nVisiblePage, pCtx->nColumn, pCtx->nRowSel, 0) != 0) {
                pCtx->bMoveArmed = 1;
                func_02033b78(0, SOUND_REMOVE);
            }
        } else {
            pCtx->nBusyWord = 0;
            if (pCtx->bMoveArmed != 0) {
                return;
            }
            if (pCtx->bSecondaryPanel != 0) {
                func_ov025_020956f8(pCtx, STATE_DRAG);
                func_02033b78(0, SOUND_ENTER);
            }
        }
        break;
    case STATE_DRAG:
        pCtx->nBusyWord = 0;
        if (func_ov025_020947b4(pCtx, pCtx->nSelectedRow) == 0) {
            func_ov025_020915d4(pCtx, 0);
            pCtx->nSelectedRow = 0;
        }
        break;
    }
}
