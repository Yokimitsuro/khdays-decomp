/* func_ov025_0209ce6c -- Ov008_DrawMenuPageTexts: redraw the menu page's
 * text surface (+0x10).  The entries of the current list (02069b94 on the
 * list id +0x2 and selection +0x0: first index and count) are taken from the
 * 0x14-byte entry table 02090598: each entry's slot (02069bec on its id)
 * gives the fixed-point position; its text (+0x2, or variable record 3 when
 * the entry is disabled, +0x6) is fitted to the width of the id (0x90 for
 * 0x14b, 0x2f for 0x14c / 0x14d, else 0x43, less 4) and drawn at position
 * / 4096 + (4, 2).  Each of the entry's sub entries (+0x7 of them at +0x8,
 * 4 bytes: id, text) is drawn likewise at its own slot position offset by
 * the anchor row (0208f5f8, 16 bytes each, picked by +0x4) and fitted to
 * the slot width (+0x1c) less 8 and the anchor x.  The label (+0xb4) goes
 * at (0xfa, 2) in colour 0x821.  For the selected entry (+0x4c): enabled
 * ones draw their help text (+0x3) at (8, 0x98) and the help of the sub
 * entry selected in +0x4e + 2 * entry (+0xb) at (8, 0xa4, style 4),
 * disabled ones variable record 3 at (8, 0x98); both fitted to 0xf0.  The
 * surface is queued and slot 9 marked used.  Codegen: the anchor table is a
 * 32-byte struct copy; the entry id (s16) becomes the width in a switch; the
 * selection is reached through a pointer to its {entry, subs} struct; u16
 * counters with the sub count in a u16 local; the sub position is written
 * "slot / 4096 + anchor" (division first).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define TEXT_DISABLED  3
#define COLOUR_TEXT    0x209
#define COLOUR_LABEL   0x821
#define ENTRY_ID_WIDE  0x14b
#define ENTRY_ID_NARROW_A 0x14c
#define ENTRY_ID_NARROW_B 0x14d
#define FX_ONE         0x1000

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
    u8  pad_05;
    u8  bEnabled;             /* 0x06 */
    u8  nSubCount;            /* 0x07 */
    Ov008MenuSubEntry aSub[3]; /* 0x08 */
} Ov008MenuEntryDef;

typedef struct Ov008MenuAnchor {
    int nA;                   /* 0x00 */
    int nB;                   /* 0x04 */
    int nX;                   /* 0x08 */
    int nY;                   /* 0x0c */
} Ov008MenuAnchor;

typedef struct Ov008MenuAnchorTable {
    Ov008MenuAnchor aAnchor[2];
} Ov008MenuAnchorTable;

typedef struct Ov008MenuList {
    u16 nFirst;               /* 0x00 */
    u16 nCount;               /* 0x02 */
} Ov008MenuList;

typedef struct Ov008Slot {
    u8  pad_00[0x1c];
    u16 nWidth;               /* 0x1c */
} Ov008Slot;

typedef struct Ov008SlotRef {
    s16 nId;                  /* 0x00 */
    u8  pad_02[2];
    Ov008Slot *pSlot;         /* 0x04 */
    int nX;                   /* 0x08: fx32 */
    int nY;                   /* 0x0c: fx32 */
} Ov008SlotRef;

typedef struct Ov008MenuSelection {
    s16 nEntry;               /* 0x00 */
    s16 aSub[(0xb4 - 0x4e) / 2]; /* 0x02: per entry */
} Ov008MenuSelection;

typedef struct Ov008MenuContext {
    s16 nSelection;           /* 0x000 */
    u16 nListId;              /* 0x002 */
    u8  varRecords[0xc];      /* 0x004 */
    u8  textSurface[0x3c];    /* 0x010 */
    Ov008MenuSelection selection; /* 0x04c */
    int nLabelIndex;          /* 0x0b4 */
} Ov008MenuContext;

extern const Ov008MenuAnchorTable data_ov025_020b4158;
extern Ov008MenuEntryDef data_ov025_020b4f64[];
extern Ov008MenuContext *func_ov025_02084afc(void);                     /* Ov008_GetMenuContext */
extern Ov008MenuList *func_ov025_0209bf74(int nListId, u32 nSelection); /* list of the selection */
extern int   func_ov025_02084a7c(void);                                 /* Ov008_GetContext */
extern void  func_ov025_0209c288(void *pField);                         /* reset to the narrow set */
extern void  func_02030158(void *pSurface);                             /* Obj_InvokeInnerVtable4 */
extern void  func_ov025_0209bfcc(Ov008SlotRef *pRef, s16 nId);          /* Ov008_Set_9bec: resolve a slot */
extern char *func_ov025_02089894(void *pRecords, int nIndex);           /* GetVarRecordByIndex */
extern int   func_ov025_0209c2a0(void *pField, char *pText, int nMaxWidth); /* Ov008_FitTextFieldFont */
extern void  func_ov025_0209cce8(char *pText, int nX, int nY, int nStyle, u32 nColour, int bShadow); /* Ov008_DrawPageAElementWithShadow */
extern void  func_020300f8(void *pSurface);                             /* EnqueueObjGfxCommand */
extern void  func_ov025_02084964(int nSlot);                            /* Ov008_MarkSlotUsed */

void func_ov025_0209ce6c(void)
{
    Ov008SlotRef ref;
    Ov008SlotRef subRef;
    Ov008MenuAnchorTable anchors;
    u16 i;
    Ov008MenuSelection *pSel;
    Ov008MenuList *pList;
    int nText;
    s16 nId;
    u16 j;
    u16 nSubCount;
    Ov008MenuContext *pCtx;
    Ov008MenuEntryDef *pEntry;
    Ov008MenuAnchor *pAnchor;
    char *pText;
    int nSubText;

    anchors = data_ov025_020b4158;
    pCtx = func_ov025_02084afc();
    pSel = &pCtx->selection;
    pList = func_ov025_0209bf74(pCtx->nListId, (u16)pCtx->nSelection);
    func_ov025_02084a7c();
    func_ov025_0209c288(pCtx->textSurface);
    func_02030158(pCtx->textSurface);
    for (i = 0; i < pList->nCount; i++) {
        pEntry = &data_ov025_020b4f64[pList->nFirst + i];
        nId = pEntry->nId;
        pAnchor = &anchors.aAnchor[pEntry->nAnchor];
        nText = pEntry->nText;
        func_ov025_0209bfcc(&ref, nId);
        switch (nId) {
        case ENTRY_ID_WIDE:
            nId = 0x90;
            break;
        case ENTRY_ID_NARROW_A:
            nId = 0x2f;
            break;
        case ENTRY_ID_NARROW_B:
            nId = 0x2f;
            break;
        default:
            nId = 0x43;
            break;
        }
        if (pEntry->bEnabled == 0) {
            nText = TEXT_DISABLED;
        }
        pText = func_ov025_02089894(pCtx->varRecords, nText);
        func_ov025_0209c2a0(pCtx->textSurface, pText, nId - 4);
        func_ov025_0209cce8(pText, ref.nX / FX_ONE + 4, ref.nY / FX_ONE + 2, 2, COLOUR_TEXT, 1);
        nSubCount = pEntry->nSubCount;
        for (j = 0; j < nSubCount; j++) {
            nSubText = pEntry->aSub[j].nText;
            func_ov025_0209bfcc(&subRef, pEntry->aSub[j].nId);
            if (pEntry->bEnabled == 0) {
                nSubText = TEXT_DISABLED;
            }
            pText = func_ov025_02089894(pCtx->varRecords, nSubText);
            func_ov025_0209c2a0(pCtx->textSurface, pText, (subRef.pSlot->nWidth - 8) - pAnchor->nX);
            func_ov025_0209cce8(pText, subRef.nX / FX_ONE + pAnchor->nX, subRef.nY / FX_ONE + pAnchor->nY, 2, COLOUR_TEXT, 1);
        }
    }
    pText = func_ov025_02089894(pCtx->varRecords, pCtx->nLabelIndex);
    func_ov025_0209c288(pCtx->textSurface);
    func_ov025_0209cce8(pText, 0xfa, 2, 2, COLOUR_LABEL, 1);
    if (data_ov025_020b4f64[pSel->nEntry].bEnabled != 0) {
        pText = func_ov025_02089894(pCtx->varRecords, data_ov025_020b4f64[pSel->nEntry].nHelpText);
        func_ov025_0209c2a0(pCtx->textSurface, pText, 0xf0);
        func_ov025_0209cce8(pText, 8, 0x98, 2, COLOUR_TEXT, 1);
        pText = func_ov025_02089894(pCtx->varRecords, data_ov025_020b4f64[pSel->nEntry].aSub[pSel->aSub[pSel->nEntry]].nHelpText);
        func_ov025_0209c2a0(pCtx->textSurface, pText, 0xf0);
        func_ov025_0209cce8(pText, 8, 0xa4, 4, COLOUR_TEXT, 1);
    } else {
        pText = func_ov025_02089894(pCtx->varRecords, TEXT_DISABLED);
        func_ov025_0209c2a0(pCtx->textSurface, pText, 0xf0);
        func_ov025_0209cce8(pText, 8, 0x98, 2, COLOUR_TEXT, 1);
    }
    func_020300f8(pCtx->textSurface);
    func_ov025_02084964(9);
}
