/* func_ov008_0206a8e0 -- Ov008_MenuSelectionRight: the "right" action on the
 * highlighted item (ctx->sel at 0x4c).  The selection block is backed up first
 * (0x4c -> 0x80, 0x34 bytes).  A locked item (data_ov008_0209059d[sel*0x14] == 0)
 * moves the highlight to the next selectable item via func_ov008_0206a788
 * (sel + 1, wrapping, step 1) when one exists; kind 1 increments the item's count
 * and re-clamps it against func_ov008_02069bc8(sel) through func_ov008_0206a76c.
 * Either way the cursor cue plays and the menu refreshes.
 */
typedef unsigned char  u8;
typedef signed short   s16;
typedef unsigned short u16;

typedef struct Ov008SelCtx {
    s16 nSelection;     /* 0x00 */
    u16 nListId;        /* 0x02 */
    u8  pad_0004[0x4c - 0x04];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

#define ITEM_STRIDE 0x14
#define KIND_LOCKED 0
#define KIND_COUNT  1

extern Ov008SelCtx *func_ov008_02050cd4(void);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void *func_ov008_02069b94(int nListId, int nSelection);        /* item ring lookup (result unused) */
extern int  func_ov008_02069bc8(int nIndex);                         /* item max count */
extern int  func_ov008_0206a76c(int nValue, int nMin, int nMax);     /* ClampWrapIndex */
extern int  func_ov008_0206a788(s16 nFrom, int nStep);               /* next selectable item, -1 if none */
extern void func_02033b78(int nKind, int nSound);                    /* PlaySound */
extern void func_ov008_0206b1f4(void);                               /* menu refresh */
extern u8   data_ov008_0209059d[];

void func_ov008_0206a8e0(void)
{
    Ov008SelCtx *ctx = func_ov008_02050cd4();
    s16 *p = &ctx->sel;
    s16 sel;
    int nNext;

    func_ov008_02069b94(ctx->nListId, (u16)ctx->nSelection);
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    sel = ctx->sel;
    switch (data_ov008_0209059d[sel * ITEM_STRIDE]) {
    case KIND_COUNT:
        (p + 1)[sel] += 1;
        *(p + p[0] + 1) = func_ov008_0206a76c(*(p + p[0] + 1), 0, func_ov008_02069bc8((u16)*p));
        break;
    case KIND_LOCKED:
        nNext = func_ov008_0206a788((s16)(sel + 1), 1);
        if (nNext >= 0) {
            *p = nNext;
        }
        break;
    }
    func_02033b78(0, 0);
    func_ov008_0206b1f4();
}
