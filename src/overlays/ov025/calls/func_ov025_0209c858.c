/* func_ov025_0209c858 -- Ov008_FindSelectableItem: starting at item nFrom, walk
 * the current list's item ring (first item, count from func_ov025_0209bf74) in
 * steps of nStep, wrapping with a modulo, until an item whose table byte +7 is
 * set (selectable) is found; returns its index or -1 after a full turn.
 *
 * nFrom is a short parameter and the table index is `(short)nIndex * 0x14`: the
 * cast is absorbed into the ROM's smlabb while the implicit narrowing of
 * `nFrom = nIndex` stays a separate lsl/asr (an explicit (s16) on both would be
 * CSE'd into one truncation and an mla).
 */
typedef unsigned char  u8;
typedef signed short   s16;
typedef unsigned short u16;

typedef struct Ov008MenuContext {
    s16 nSelection;           /* 0x000 */
    u16 nListId;              /* 0x002 */
} Ov008MenuContext;

typedef struct Ov008ItemRing {
    u16 nFirst;               /* 0x00 */
    u16 nCount;               /* 0x02 */
} Ov008ItemRing;

#define ITEM_STRIDE 0x14

extern u8 data_ov025_020b4f64[];                                  /* item table, byte +7 = selectable */

extern Ov008MenuContext *func_ov025_02084afc(void);               /* Ov008_GetMenuContext */
extern Ov008ItemRing *func_ov025_0209bf74(int nListId, int nSelection);
extern long long func_02020400(int nNum, int nDen);               /* _s32_div_f: quotient, remainder in the high word */

int func_ov025_0209c858(s16 nFrom, int nStep)
{
    Ov008MenuContext *pCtx;
    Ov008ItemRing *pRing;
    int nIndex;
    int i;
    int nFirst;
    int nCount;
    int nSel;

    pCtx = func_ov025_02084afc();
    pRing = func_ov025_0209bf74(pCtx->nListId, (u16)pCtx->nSelection);
    nCount = pRing->nCount;
    i = 0;
    if (nCount > 0) {
        nFirst = pRing->nFirst;
        do {
            nIndex = nFirst + (int)(func_02020400(nCount + (nFrom - nFirst), nCount) >> 32);
            nSel = data_ov025_020b4f64[(short)nIndex * ITEM_STRIDE + 7];
            nFrom = nIndex;
            if (nSel != 0) {
                break;
            }
            nFrom = nFrom + nStep;
            i = (s16)(i + 1);
        } while (i < nCount);
    }
    if (i == nCount) {
        nFrom = -1;
    }
    return nFrom;
}
