/* func_ov025_02090854 -- Ov008_RefreshInventoryRows: redraw the eight
 * visible inventory rows from list position nScroll (list +0x300).  Each
 * row cell (+0x16e0, 0x28 each) is activated and takes the texture of the
 * record's 1-based tag (+0x20); a fixed record (category 2) is drawn with
 * colour 0xf5 and its counts (-1 / owned), the row state (+0x24) cleared;
 * any other record is drawn with 0xf5 (state 1) once every copy is placed,
 * else 0xf3 (state 0), and its placed / owned counts drawn.  The row's
 * widget 400 + row is hidden while flag 0x37c9 + item id is set, else reset
 * to the item's bitset bit and shown; widget 500 + row shows while a copy is
 * placed.  Rows past the list are drawn empty (0xf3), deactivated and both
 * widgets hidden.  The grid surface (+0xac) is queued, the scroll (+0x74)
 * stored, and the two arrows (widgets 1 / 2) shown while the list can scroll
 * up / down (count +0x78).  Codegen: do-while under an `if (pItem)` guard
 * with nRow = 0 before the context call; the arrow flags are if/else locals
 * (an inline bool is folded into the call after the entry lookup).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT       8
#define WIDGET_ROW_BASE 400
#define WIDGET_MARK_BASE 500
#define WIDGET_ARROW_UP 1
#define WIDGET_ARROW_DOWN 2
#define CATEGORY_FIXED  2
#define COLOUR_ACTIVE   0xf3
#define COLOUR_DONE     0xf5
#define FLAG_ITEM_HIDDEN 0x37c9

typedef struct Ov008Message15Record {
    u8   pad_00[0xc];
    void *pName;              /* 0x0c */
    u8   pad_10[4];
    int  nItemId;             /* 0x14 */
    int  nCategory;           /* 0x18 */
    u8   pad_1c[4];
    u16  nTag;                /* 0x20: 1-based texture entry tag */
} Ov008Message15Record;

typedef struct Ov008InventoryItem {
    Ov008Message15Record *pRecord;  /* 0x00 */
    u8  nCount;               /* 0x04 */
    u8  nPlaced;              /* 0x05 */
} Ov008InventoryItem;

typedef struct Ov008TextureEntry {
    u8  pad_00[4];
    int *pTexture;            /* 0x04 */
} Ov008TextureEntry;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    int aTexParams[2];        /* 0x04 */
    u8  pad_0c[0x24 - 0xc];
    int nState;               /* 0x24 */
} Ov008GridDisplayCell;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x74];
    int nScrollRow;           /* 0x0074 */
    int nListCount;           /* 0x0078 */
    u8  pad_007c[0xac - 0x7c];
    u8  gridSurface[0x300 - 0xac]; /* 0x00ac */
    void *pList;              /* 0x0300 */
    u8  pad_0304[0x16e0 - 0x304];
    Ov008GridDisplayCell aRowCell[ROW_COUNT]; /* 0x16e0 */
} Ov008MenuContext;

extern int   func_ov025_02084a7c(void);                                  /* Ov008_GetContext */
extern Ov008InventoryItem *func_02010154(void *pList, int nIndex);       /* List_GetNthObject */
extern Ov008InventoryItem *NNS_FndGetNextListObject(void *pList, void *pObject);
extern Ov008TextureEntry *func_ov025_0208ffc4(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void  func_ov025_0208a5f8(int *pParams, int *pTexture);           /* Ov008_GetTextureParams */
extern void  func_ov025_020905cc(Ov008MenuContext *pCtx, int nRow, void *pText, int nColour); /* Ov008_UploadTileSlot */
extern void  func_ov025_02090668(Ov008MenuContext *pCtx, int nRow, int nPlaced, int nOwned); /* draw the counts */
extern int   func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void *func_ov025_0208843c(int nCtx, int nId);                     /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern int   func_ov025_0209010c(Ov008MenuContext *pCtx, int nItemId);   /* TestBitInBitset */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);    /* Ov008_ReleaseTwoSlotsEx */
extern void  func_020300f8(void *pSurface);                              /* EnqueueObjGfxCommand */

void func_ov025_02090854(Ov008MenuContext *pCtx, int nArg, int nScroll)
{
    int nRow;
    Ov008InventoryItem *pItem;
    int nCtx;
    int bVisible;
    Ov008Message15Record *pRecord;
    void *pEntry;

    nRow = 0;
    nCtx = func_ov025_02084a7c();
    pItem = func_02010154(pCtx->pList, (u16)nScroll);
    if (pItem != 0) {
        do {
            pCtx->aRowCell[nRow].isActive = 1;
            func_ov025_0208a5f8(pCtx->aRowCell[nRow].aTexParams, func_ov025_0208ffc4(pCtx, pItem->pRecord->nTag)->pTexture);
            pRecord = pItem->pRecord;
            if (pRecord->nCategory == CATEGORY_FIXED) {
                func_ov025_020905cc(pCtx, nRow, pRecord->pName, COLOUR_DONE);
                func_ov025_02090668(pCtx, nRow, -1, pItem->nCount);
                pCtx->aRowCell[nRow].nState = 0;
            } else {
                if (pItem->nPlaced >= pItem->nCount) {
                    func_ov025_020905cc(pCtx, nRow, pRecord->pName, COLOUR_DONE);
                    pCtx->aRowCell[nRow].nState = 1;
                } else {
                    func_ov025_020905cc(pCtx, nRow, pRecord->pName, COLOUR_ACTIVE);
                    pCtx->aRowCell[nRow].nState = 0;
                }
                func_ov025_02090668(pCtx, nRow, pItem->nPlaced, pItem->nCount);
            }
            if (func_02023588(pItem->pRecord->nItemId + FLAG_ITEM_HIDDEN) != 0) {
                func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_ROW_BASE), 0);
            } else {
                pEntry = func_ov025_0208843c(nCtx, nRow + WIDGET_ROW_BASE);
                func_ov025_02088928(nCtx, pEntry, (u16)(func_ov025_0209010c(pCtx, pItem->pRecord->nItemId) != 0));
                func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_ROW_BASE), 1);
            }
            if (pItem->nPlaced != 0) {
                func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_MARK_BASE), 1);
            } else {
                func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_MARK_BASE), 0);
            }
            nRow++;
            pItem = NNS_FndGetNextListObject(pCtx->pList, pItem);
        } while (nRow < ROW_COUNT && pItem != 0);
    }
    for (; nRow < ROW_COUNT; nRow++) {
        func_ov025_020905cc(pCtx, nRow, 0, COLOUR_ACTIVE);
        pCtx->aRowCell[nRow].isActive = 0;
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_ROW_BASE), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, nRow + WIDGET_MARK_BASE), 0);
    }
    func_020300f8(pCtx->gridSurface);
    pCtx->nScrollRow = nScroll;
    if (nScroll > 0) {
        bVisible = 1;
    } else {
        bVisible = 0;
    }
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_ARROW_UP), bVisible);
    if (nScroll + ROW_COUNT < pCtx->nListCount) {
        bVisible = 1;
    } else {
        bVisible = 0;
    }
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_ARROW_DOWN), bVisible);
}
