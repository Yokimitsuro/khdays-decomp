/* func_ov025_0209d2d8 -- Ov008_ShowItemList: show or hide every widget of
 * item list nListId (item ring from 02069b7c: first item and count).  When
 * showing, the highlight (+0x4c) moves to the first selectable item from the
 * ring's first (or the first itself when none) and the first is backed up
 * (+0x80).  For each entry of the ring (table data_ov025_020b4f64, 0x14 per
 * entry) the entry's own widget and its nSubCount sub-widgets (columns from
 * the 2D table) are set visible / hidden; while showing, an enabled entry
 * also gets its current column (+0x4e + 2 * entry) re-picked and applied
 * (02069c68).
 * Codegen: the entry pointer is declared before the entry index and computed
 * before the pick call, whose id argument carries an (int) cast -- the
 * conversion node keeps &pick out of the outer loop's invariants (the ROM
 * recomputes it for the first call and hoists it only over the inner loop).
 *
 * PROVENANCE: byte-identical twin of func_ov008_0206b208 (ov008), propagated with this
 * overlay's own callees and globals and verified byte-exact here.
 */
typedef unsigned char  u8;
typedef signed short   s16;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008ItemRing {
    u16 nFirst;               /* 0x00 */
    u16 nCount;               /* 0x02 */
} Ov008ItemRing;

typedef struct Ov008WidgetPick {
    s16   nId;                /* 0x00 */
    u8    pad_02[2];
    void *pEntry;             /* 0x04 */
    u8    pos[8];             /* 0x08 */
} Ov008WidgetPick;

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

typedef struct Ov008MenuContext {
    u8  pad_0000[0x4c];
    s16 sel;                  /* 0x4c: highlighted item */
    s16 aItemColumn[25];      /* 0x4e: current column per item */
    s16 selBackup;            /* 0x80: backed-up highlight */
} Ov008MenuContext;

extern Ov008MenuEntryDef data_ov025_020b4f64[];                  /* the menu entry table */

extern Ov008MenuContext *func_ov025_02084afc(void);               /* Ov008_GetMenuContext */
extern int  func_ov025_02084a7c(void);                            /* Ov008_GetContext */
extern Ov008ItemRing *func_ov025_0209bf5c(u16 nListId);           /* item ring of a list */
extern int  func_ov025_0209c858(s16 nFrom, int nStep);            /* Ov008_FindSelectableItem */
extern void func_ov025_0209bfcc(Ov008WidgetPick *pPick, s16 nId); /* Ov008_Set_9bec: pick a widget */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void func_ov025_0209c00c(Ov008WidgetPick *pPick, s16 nItem, s16 nColumn); /* pick from the 2D table */
extern void func_ov025_0209c048(Ov008WidgetPick *pPick);          /* Ov008_Set_9c68 */

void func_ov025_0209d2d8(u32 nListId, int bShow)
{
    Ov008MenuContext *pCtx;
    int nCtx;
    Ov008ItemRing *pRing;
    Ov008WidgetPick pick;
    int nSel;
    u16 i;
    u16 j;
    Ov008MenuEntryDef *pItem;
    s16 nItem;

    pCtx = func_ov025_02084afc();
    nCtx = func_ov025_02084a7c();
    pRing = func_ov025_0209bf5c(nListId);
    if (bShow != 0) {
        nSel = func_ov025_0209c858(pRing->nFirst, 1);
        if (nSel >= 0) {
            pCtx->sel = nSel;
        } else {
            pCtx->sel = pRing->nFirst;
        }
        pCtx->selBackup = pRing->nFirst;
    }
    for (i = 0; i < pRing->nCount; i++) {
        nItem = pRing->nFirst + i;
        pItem = &data_ov025_020b4f64[nItem];
        func_ov025_0209bfcc(&pick, (int)pItem->nId);
        func_ov025_0208884c(nCtx, pick.pEntry, bShow);
        for (j = 0; j < pItem->nSubCount; j++) {
            func_ov025_0209c00c(&pick, nItem, (s16)j);
            func_ov025_0208884c(nCtx, pick.pEntry, bShow);
            if (bShow != 0 && pItem->bEnabled != 0) {
                func_ov025_0209c00c(&pick, nItem, pCtx->aItemColumn[nItem]);
                func_ov025_0209c048(&pick);
            }
        }
    }
}
