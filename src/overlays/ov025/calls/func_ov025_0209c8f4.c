/* func_ov025_0209c8f4 -- Ov008_MenuSelectionLeft: the "left" action on the
 * highlighted item (ctx->sel at 0x4c).  The selection block is backed up first
 * (0x4c -> 0x80, 0x34 bytes).  A locked item (data_ov025_020b4f69[sel*0x14] == 0)
 * moves the highlight to the previous selectable item via func_ov025_0209c858
 * (sel - 1, wrapping, step -1) when one exists; kind 1 decrements the item's count
 * and re-clamps it against func_ov025_0209bfa8(sel) through func_ov025_0209c83c.
 * Either way the cursor cue plays and the menu refreshes.
 */
typedef unsigned char  u8;
typedef signed short   s16;
typedef unsigned short u16;

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

#define ITEM_STRIDE 0x14
#define KIND_LOCKED 0
#define KIND_COUNT  1

extern Ov008SelCtx *func_ov025_02084afc(void);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern int  func_ov025_0209bfa8(int nIndex);                         /* item max count */
extern int  func_ov025_0209c83c(int nValue, int nMin, int nMax);     /* ClampWrapIndex */
extern int  func_ov025_0209c858(s16 nFrom, int nStep);               /* next selectable item, -1 if none */
extern void func_02033b78(int nKind, int nSound);                    /* PlaySound */
extern void func_ov025_0209d2c4(void);                               /* menu refresh */
extern u8   data_ov025_020b4f69[];

void func_ov025_0209c8f4(void)
{
    Ov008SelCtx *ctx = func_ov025_02084afc();
    s16 *p = &ctx->sel;
    s16 sel;
    int nNext;

    MI_CpuCopy8(p, &ctx->field80, 0x34);
    sel = ctx->sel;
    switch (data_ov025_020b4f69[sel * ITEM_STRIDE]) {
    case KIND_COUNT:
        (p + 1)[sel] -= 1;
        *(p + p[0] + 1) = func_ov025_0209c83c(*(p + p[0] + 1), 0, func_ov025_0209bfa8((u16)*p));
        break;
    case KIND_LOCKED:
        nNext = func_ov025_0209c858((s16)(sel - 1), -1);
        if (nNext >= 0) {
            *p = nNext;
        }
        break;
    }
    func_02033b78(0, 0);
    func_ov025_0209d2c4();
}
