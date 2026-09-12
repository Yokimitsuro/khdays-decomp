/* func_ov025_020986c0 -- Ov008_MenuKeyLeft: the menu's "left" key handler.
 * Ignored while a touch is down or while another key (other than left, bit 5)
 * is latched in the key word (+0x2098); latches left.  In modes 0/1 it moves the
 * cursor one column left (func_ov025_02094988) and, if that took, clears the
 * hold counter, arms the move and plays cue 0x35.  In mode 2 with nothing
 * pending it resets the column to 4 and closes the secondary list (mode 1
 * unless the list at +0x19b4 is up, then 0) with cue 0.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define KEY_LEFT   0x20
#define SOUND_MOVE 0x35

typedef struct Ov008MenuContext {
    u8   pad_0000[0x8];
    int  nPending;            /* 0x0008 */
    u8   pad_000c[4];
    u32  nMode;               /* 0x0010 */
    u8   pad_0014[0x38 - 0x14];
    int  bMoveArmed;          /* 0x0038 */
    u8   pad_003c[8];
    int  nHoldCount;          /* 0x0044 */
    u8   pad_0048[0x64 - 0x48];
    u16  nColumn;             /* 0x0064 */
    u16  nRowSel;             /* 0x0066 */
    u8   pad_0068[0x19b4 - 0x68];
    int  bListUp;             /* 0x19b4 */
    u8   pad_19b8[0x2098 - 0x19b8];
    u16  nKeyLatch;           /* 0x2098 */
} Ov008MenuContext;

extern void func_ov025_020899dc(void *pOut);                              /* touch record */
extern int  func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep);
extern void func_ov025_020956f8(Ov008MenuContext *pCtx, int nMode);
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */

void func_ov025_020986c0(Ov008MenuContext *pCtx)
{
    u16 touch[3];

    func_ov025_020899dc(touch);
    if (touch[2] != 0) {
        return;
    }
    if (pCtx->nKeyLatch != 0 && (pCtx->nKeyLatch & KEY_LEFT) == 0) {
        return;
    }
    pCtx->nKeyLatch = KEY_LEFT;
    switch (pCtx->nMode) {
    case 2:
        if (pCtx->nPending != 0) {
            return;
        }
        pCtx->nColumn = 4;
        if (pCtx->bListUp == 0) {
            func_ov025_020956f8(pCtx, 1);
        } else {
            func_ov025_020956f8(pCtx, 0);
        }
        func_02033b78(0, 0);
        break;
    case 0:
    case 1:
        if (func_ov025_02094988(pCtx, pCtx->nColumn - 1, pCtx->nRowSel, 1) == 0) {
            return;
        }
        pCtx->nHoldCount = 0;
        pCtx->bMoveArmed = 1;
        func_02033b78(0, SOUND_MOVE);
        break;
    }
}
