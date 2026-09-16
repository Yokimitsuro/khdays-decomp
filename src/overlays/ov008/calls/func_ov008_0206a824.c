/* func_ov008_0206a824 -- Ov008_MenuSelectionLeft: the "left" action on the
 * highlighted item (ctx->sel at 0x4c).  The selection block is backed up first
 * (0x4c -> 0x80, 0x34 bytes).  A locked item (the entry's lock state (data_ov008_02090598[sel].nState) == 0)
 * moves the highlight to the previous selectable item via func_ov008_0206a788
 * (sel - 1, wrapping, step -1) when one exists; kind 1 decrements the item's count
 * and re-clamps it against func_ov008_02069bc8(sel) through func_ov008_0206a76c.
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

extern Ov008SelCtx *func_ov008_02050cd4(void);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern int  func_ov008_02069bc8(int nIndex);                         /* item max count */
extern int  func_ov008_0206a76c(int nValue, int nMin, int nMax);     /* ClampWrapIndex */
extern int  func_ov008_0206a788(s16 nFrom, int nStep);               /* next selectable item, -1 if none */
extern void func_02033b78(int nKind, int nSound);                    /* PlaySound */
extern void func_ov008_0206b1f4(void);                               /* menu refresh */
typedef struct Ov008MenuSubEntry {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
} Ov008MenuSubEntry;

typedef struct Ov008MenuEntryDef {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06 */
    u8  nSubCount;            /* 0x07 */
    Ov008MenuSubEntry aSub[3]; /* 0x08 */
} Ov008MenuEntryDef;

extern Ov008MenuEntryDef data_ov008_02090598[];

void func_ov008_0206a824(void)
{
    Ov008SelCtx *ctx = func_ov008_02050cd4();
    s16 *p = &ctx->sel;
    s16 sel;
    int nNext;

    MI_CpuCopy8(p, &ctx->field80, 0x34);
    sel = ctx->sel;
    switch (data_ov008_02090598[sel].nState) {
    case KIND_COUNT:
        (p + 1)[sel] -= 1;
        *(p + p[0] + 1) = func_ov008_0206a76c(*(p + p[0] + 1), 0, func_ov008_02069bc8((u16)*p));
        break;
    case KIND_LOCKED:
        nNext = func_ov008_0206a788((s16)(sel - 1), -1);
        if (nNext >= 0) {
            *p = nNext;
        }
        break;
    }
    func_02033b78(0, 0);
    func_ov008_0206b1f4();
}
