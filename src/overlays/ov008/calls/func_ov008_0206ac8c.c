/* func_ov008_0206ac8c -- Ov008_RaiseSelectedItemWidget: lift the highlighted
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

extern u8 data_ov008_0209059e[];                                   /* item available (stride 0x14) */
extern u8 data_ov008_0209059f[];                                   /* item enabled (stride 0x14) */

extern Ov008SelCtx *func_ov008_02050cd4(void);                     /* Ov008_GetMenuContext */
extern int  func_ov008_02050c54(void);                             /* Ov008_GetContext */
extern void func_ov008_02069c2c(Ov008WidgetPick *pPick, s16 nItem, int nColumn); /* Ov008_DispatchFrom2DTable */
extern void func_ov008_02054cc4(int nCtx, void *pEntry);           /* Ov008_SwapParamOverrides */
extern void func_ov008_02054c44(int nCtx, void *pEntry);           /* Ov008_ReleaseTwoSlots */
extern void func_ov008_02054b18(int nCtx, void *pEntry, int nValue); /* Ov008_PushSubitemSet */
extern void func_ov008_02069c68(Ov008WidgetPick *pPick);           /* Ov008_Set_9c68 */
extern void func_ov008_02069bec(Ov008WidgetPick *pPick, s16 nId);  /* Ov008_Set_9bec */
extern void func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */

void func_ov008_0206ac8c(void)
{
    Ov008SelCtx *ctx = func_ov008_02050cd4();
    int nCtx;
    s16 *p = &ctx->sel;
    s16 *pBackup = &ctx->selBackup;
    UiLayoutPos pos;
    Ov008WidgetPick pick;
    int nBackup;

    nCtx = func_ov008_02050c54();
    func_ov008_02069c2c(&pick, ctx->sel, (p + 1)[ctx->sel]);
    pos = pick.pos;
    func_ov008_02054cc4(nCtx, pick.pEntry);
    if (data_ov008_0209059e[ctx->sel * ITEM_STRIDE] != 0) {
        func_ov008_02054c44(nCtx, pick.pEntry);
    } else {
        func_ov008_02054b18(nCtx, pick.pEntry, 0);
    }
    nBackup = *pBackup;
    if (*p != nBackup) {
        if (data_ov008_0209059e[nBackup * ITEM_STRIDE] != 0 && data_ov008_0209059f[nBackup * ITEM_STRIDE] != 0) {
            func_ov008_02069c2c(&pick, *pBackup, (pBackup + 1)[nBackup]);
            func_ov008_02069c68(&pick);
        }
    }
    func_ov008_02069bec(&pick, 1);
    pos.nY += RAISE_FX32;
    func_ov008_02054858(nCtx, pick.pEntry, &pos);
}
