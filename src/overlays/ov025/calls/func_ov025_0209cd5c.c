/* func_ov025_0209cd5c -- Ov008_RaiseSelectedItemWidget: lift the highlighted
 * item's widget.  Resolves the widget of the highlighted item's current column
 * (id from the table row `sel`, column = the item's count) into a pick, swaps
 * its parameter overrides and either releases its two slots (item available)
 * or pushes its sub-item set; when the highlight differs from the backed-up
 * one (+0x80) and that item is both available and enabled, its widget is resolved
 * too and reset.  Then the pick is re-resolved with id 1 and the widget moved
 * to its layout position raised by 8 px (fx32 0x8000).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008WidgetPick {
    s16   nId;                /* 0x00 */
    u8    pad_02[2];
    void *pEntry;             /* 0x04 */
    UiLayoutPos pos;          /* 0x08 */
} Ov008WidgetPick;

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;                  /* 0x4c: highlighted item */
    s16 counts[0x19];         /* 0x4e */
    s16 selBackup;            /* 0x80: backed-up highlight */
    s16 countsBackup[0x19];   /* 0x82 */
} Ov008SelCtx;

#define ITEM_STRIDE 0x14
#define RAISE_FX32  0x8000

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

extern Ov008MenuEntryDef data_ov025_020b4f64[];                    /* the menu entry table */

extern Ov008SelCtx *func_ov025_02084afc(void);                     /* Ov008_GetMenuContext */
extern int  func_ov025_02084a7c(void);                             /* Ov008_GetContext */
extern void func_ov025_0209c00c(Ov008WidgetPick *pPick, s16 nItem, int nColumn); /* Ov008_DispatchFrom2DTable */
extern void func_ov025_0208896c(int nCtx, void *pEntry);           /* Ov008_SwapParamOverrides */
extern void func_ov025_020888ec(int nCtx, void *pEntry);           /* Ov008_ReleaseTwoSlots */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue); /* Ov008_PushSubitemSet */
extern void func_ov025_0209c048(Ov008WidgetPick *pPick);           /* Ov008_Set_9c68 */
extern void func_ov025_0209bfcc(Ov008WidgetPick *pPick, s16 nId);  /* Ov008_Set_9bec */
extern void func_ov025_02088500(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */

void func_ov025_0209cd5c(void)
{
    Ov008SelCtx *ctx = func_ov025_02084afc();
    int nCtx;
    s16 *p = &ctx->sel;
    s16 *pBackup = &ctx->selBackup;
    UiLayoutPos pos;
    Ov008WidgetPick pick;
    int nBackup;

    nCtx = func_ov025_02084a7c();
    func_ov025_0209c00c(&pick, ctx->sel, (p + 1)[ctx->sel]);
    pos = pick.pos;
    func_ov025_0208896c(nCtx, pick.pEntry);
    if (data_ov025_020b4f64[ctx->sel].bEnabled != 0) {
        func_ov025_020888ec(nCtx, pick.pEntry);
    } else {
        func_ov025_020887c0(nCtx, pick.pEntry, 0);
    }
    nBackup = *pBackup;
    if (*p != nBackup) {
        if (data_ov025_020b4f64[nBackup].bEnabled != 0 && data_ov025_020b4f64[nBackup].nSubCount != 0) {
            func_ov025_0209c00c(&pick, *pBackup, (pBackup + 1)[nBackup]);
            func_ov025_0209c048(&pick);
        }
    }
    func_ov025_0209bfcc(&pick, 1);
    pos.nY += RAISE_FX32;
    func_ov025_02088500(nCtx, pick.pEntry, &pos);
}
