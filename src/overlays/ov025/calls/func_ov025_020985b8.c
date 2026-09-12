/* func_ov025_020985b8 -- Ov008_MenuKeyDown: the menu's "down" key handler.
 * Ignored while a touch is down or while another key (other than down, bit 7)
 * is latched in the key word (+0x2098); latches down.  In modes 0/1 it moves the
 * cursor one row down (func_ov025_02094988) and, if that took, arms the move,
 * clears the hold counter and plays cue 0x35.  In mode 2 with nothing pending it
 * flips to the next page ((page + 1) mod page count) and, when that took and
 * there is more than one page, plays cue 0.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define KEY_DOWN   0x80
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
    u8   pad_0068[0x78 - 0x68];
    int  nPageCount;          /* 0x0078 */
    u8   pad_007c[0x9c - 0x7c];
    int  nPage;               /* 0x009c */
    u8   pad_00a0[0x2098 - 0xa0];
    u16  nKeyLatch;           /* 0x2098 */
} Ov008MenuContext;

extern void func_ov025_020899dc(void *pOut);                              /* touch record */
extern int  func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep);
extern long long func_02020400(int nNum, int nDen);                       /* _s32_div_f: remainder in the high word */
extern int  func_ov025_020947b4(Ov008MenuContext *pCtx, int nPage);       /* switch page */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */

void func_ov025_020985b8(Ov008MenuContext *pCtx)
{
    u16 touch[3];

    func_ov025_020899dc(touch);
    if (touch[2] != 0) {
        return;
    }
    if (pCtx->nKeyLatch != 0 && (pCtx->nKeyLatch & KEY_DOWN) == 0) {
        return;
    }
    pCtx->nKeyLatch = KEY_DOWN;
    switch (pCtx->nMode) {
    case 0:
    case 1:
        if (func_ov025_02094988(pCtx, pCtx->nColumn, pCtx->nRowSel + 1, 1) == 0) {
            return;
        }
        pCtx->bMoveArmed = 1;
        pCtx->nHoldCount = 0;
        func_02033b78(0, SOUND_MOVE);
        break;
    case 2:
        if (pCtx->nPending != 0) {
            return;
        }
        if (func_ov025_020947b4(pCtx, (int)(func_02020400(pCtx->nPage + 1, pCtx->nPageCount) >> 32)) == 0) {
            return;
        }
        if (pCtx->nPageCount > 1) {
            func_02033b78(0, 0);
        }
        break;
    }
}
