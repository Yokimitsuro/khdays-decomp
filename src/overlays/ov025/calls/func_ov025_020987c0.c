/* func_ov025_020987c0 -- Ov008_MenuKeyRight: the menu's "right" key handler.
 * Ignored while a touch is down or while another key (other than right, bit 4)
 * is latched in the key word (+0x2098); latches right.  In modes 0/1 it moves
 * the cursor one column right (func_ov025_02094988): if that took it arms the
 * move, clears the hold counter and plays cue 0x35; past the last column, when a
 * secondary panel exists (+0x4c), it clears the busy word, resets the grid
 * (func_ov025_02093b08), opens mode 2, rebuilds the grid hits, disables the row
 * block, refreshes the equip panel (+0x1f78) and plays cue 0x35.  Mode 2 does
 * nothing (an empty case the compiler still tests).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define KEY_RIGHT  0x10
#define SOUND_MOVE 0x35

typedef struct Ov008MenuContext {
    u8   pad_0000[0x10];
    u32  nMode;               /* 0x0010 */
    u8   pad_0014[0x30 - 0x14];
    int  nBusy;               /* 0x0030 */
    u8   pad_0034[4];
    int  bMoveArmed;          /* 0x0038 */
    u8   pad_003c[8];
    int  nHoldCount;          /* 0x0044 */
    u8   pad_0048[4];
    int  bSecondaryPanel;     /* 0x004c */
    u8   pad_0050[0x64 - 0x50];
    u16  nColumn;             /* 0x0064 */
    u16  nRowSel;             /* 0x0066 */
    u8   pad_0068[0x1f78 - 0x68];
    u8   equipPanel[0x2098 - 0x1f78]; /* 0x1f78 */
    u16  nKeyLatch;           /* 0x2098 */
} Ov008MenuContext;

extern void func_ov025_020899dc(void *pOut);                              /* touch record */
extern int  func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep);
extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int nArg);       /* grid reset */
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nMode);
extern void func_ov025_02093038(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void func_ov025_020a4264(void);                                    /* Ov008_DisableRowBlock */
extern void func_ov025_020a4408(void *pPanel);                            /* Ov008_RefreshEquipPanel */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */

void func_ov025_020987c0(Ov008MenuContext *pCtx)
{
    u16 touch[3];

    func_ov025_020899dc(touch);
    if (touch[2] != 0) {
        return;
    }
    if (pCtx->nKeyLatch != 0 && (pCtx->nKeyLatch & KEY_RIGHT) == 0) {
        return;
    }
    pCtx->nKeyLatch = KEY_RIGHT;
    switch (pCtx->nMode) {
    case 0:
    case 1:
        if (func_ov025_02094988(pCtx, pCtx->nColumn + 1, pCtx->nRowSel, 1) != 0) {
            pCtx->bMoveArmed = 1;
            pCtx->nHoldCount = 0;
            func_02033b78(0, SOUND_MOVE);
        } else if (pCtx->bSecondaryPanel != 0) {
            pCtx->nBusy = 0;
            func_ov025_02093b08(pCtx, 0);
            func_ov025_020956f8(pCtx, 2);
            func_ov025_02093038(pCtx);
            func_ov025_020a4264();
            func_ov025_020a4408(pCtx->equipPanel);
            func_02033b78(0, SOUND_MOVE);
        }
        break;
    case 2:
        break;
    }
}
