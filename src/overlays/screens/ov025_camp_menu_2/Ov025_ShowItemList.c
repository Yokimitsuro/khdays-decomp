/* Ov025_ShowItemList -- Ov008_ShowItemList: show or hide every widget of
 * item list nListId (item ring from 02069b7c: first item and count).  When
 * showing, the highlight (+0x4c) moves to the first selectable item from the
 * ring's first (or the first itself when none) and the first is backed up
 * (+0x80).  For each entry of the ring (table gOv025ConfigSettings, 0x14 per
 * entry) the entry's own widget and its nSubCount sub-widgets (columns from
 * the 2D table) are set visible / hidden; while showing, an enabled entry
 * also gets its current column (+0x4e + 2 * entry) re-picked and applied
 * (02069c68).
 * Codegen: the entry pointer is declared before the entry index and computed
 * before the pick call, whose id argument carries an (int) cast -- the
 * conversion node keeps &pick out of the outer loop's invariants (the ROM
 * recomputes it for the first call and hoists it only over the inner loop).
 *
 * PROVENANCE: byte-identical twin of Ov008_ShowItemList (ov008), propagated with this
 * overlay's own callees and globals and verified byte-exact here.
 */

#include "nitro/types.h"

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

typedef struct Ov008ConfigValue {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
} Ov008ConfigValue;

typedef struct Ov008ConfigSetting {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06: 0 shows it as "?" */
    u8  nSubCount;            /* 0x07: its values; 0 for a heading */
    Ov008ConfigValue aSub[3]; /* 0x08 */
} Ov008ConfigSetting;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x4c];
    s16 sel;                  /* 0x4c: highlighted item */
    s16 aItemColumn[25];      /* 0x4e: current column per item */
    s16 selBackup;            /* 0x80: backed-up highlight */
} Ov008MenuContext;

extern Ov008ConfigSetting gOv025ConfigSettings[];                  /* the Preferences page's settings */

extern Ov008MenuContext *Ov025_GetPageA(void);               /* Ov008_GetMenuContext */
extern int  Ov025_GetContext(void);                            /* Ov008_GetContext */
extern Ov008ItemRing *Ov025_GetItemTableEntry(int nListId);           /* item ring of a list */
extern int  Ov025_FindSelectableItem(s16 nFrom, int nStep);            /* Ov008_FindSelectableItem */
extern void Ov025_WidgetRef_Init(Ov008WidgetPick *pPick, s16 nId); /* Ov008_Set_9bec: pick a widget */
extern void Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void Ov025_DispatchFrom2DTable(Ov008WidgetPick *pPick, s16 nItem, int nColumn); /* pick from the 2D table */
extern void Ov025_WidgetRef_Hide(Ov008WidgetPick *pPick);          /* Ov008_Set_9c68 */

void Ov025_ShowItemList(u32 nListId, int bShow)
{
    Ov008MenuContext *pCtx;
    int nCtx;
    Ov008ItemRing *pRing;
    Ov008WidgetPick pick;
    int nSel;
    u16 i;
    u16 j;
    Ov008ConfigSetting *pItem;
    s16 nItem;

    pCtx = Ov025_GetPageA();
    nCtx = Ov025_GetContext();
    pRing = Ov025_GetItemTableEntry((u16)nListId);
    if (bShow != 0) {
        nSel = Ov025_FindSelectableItem(pRing->nFirst, 1);
        if (nSel >= 0) {
            pCtx->sel = nSel;
        } else {
            pCtx->sel = pRing->nFirst;
        }
        pCtx->selBackup = pRing->nFirst;
    }
    for (i = 0; i < pRing->nCount; i++) {
        nItem = pRing->nFirst + i;
        pItem = &gOv025ConfigSettings[nItem];
        Ov025_WidgetRef_Init(&pick, (int)pItem->nId);
        Ov025_SetEntrySlotsVisible(nCtx, pick.pEntry, bShow);
        for (j = 0; j < pItem->nSubCount; j++) {
            Ov025_DispatchFrom2DTable(&pick, nItem, (s16)j);
            Ov025_SetEntrySlotsVisible(nCtx, pick.pEntry, bShow);
            if (bShow != 0 && pItem->bEnabled != 0) {
                Ov025_DispatchFrom2DTable(&pick, nItem, (s16)pCtx->aItemColumn[nItem]);
                Ov025_WidgetRef_Hide(&pick);
            }
        }
    }
}
