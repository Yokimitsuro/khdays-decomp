/* func_ov025_02090e44 -- Ov008_BuildInventoryLists: fill the eight category
 * lists (+0x304, 12 bytes each) of the grid inventory.  The per-category
 * filter table data_ov025_020b3d68 (8 ints, 7 = any category) is copied to the
 * stack; for each category and every item id 1..0x276 that is grid-eligible,
 * owned (GameState count at 0x810 + id) and whose message-15 record (+0x207c,
 * 0x9c each) matches the filter, a 0x14-byte inventory item is allocated and
 * zeroed: the record, the owned count (+4), the count already placed on the
 * grid (+5, also cached at +0x1bf0 + item id); it is appended (0205e868) and
 * the category's count (+0x7c) bumped.  The word at +0x78 is cleared once per
 * category.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define CATEGORY_COUNT 8
#define CATEGORY_ANY   7
#define ITEM_ID_END    0x277

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
    u8  pad_1c[0x9c - 0x1c];
} Ov008Message15Record;

typedef struct Ov008InventoryItem {
    Ov008Message15Record *pRecord;  /* 0x00 */
    u8  nCount;               /* 0x04: copies owned */
    u8  nPlaced;              /* 0x05: copies on the grid */
    u8  pad_06[0x14 - 0x6];
} Ov008InventoryItem;

typedef struct NNSFndList {
    u8 pad[12];
} NNSFndList;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x78];
    int nTotal;               /* 0x0078 */
    int aCount[CATEGORY_COUNT]; /* 0x007c */
    u8  pad_009c[0x304 - 0x9c];
    NNSFndList aList[CATEGORY_COUNT]; /* 0x0304 */
    u8  pad_0364[0x1bf0 - 0x364];
    u8  aPlaced[0x48c];       /* 0x1bf0: placed count per item id */
    Ov008Message15Record *pRecords; /* 0x207c */
} Ov008MenuContext;

typedef struct Ov008CategoryFilter {
    int aCategory[CATEGORY_COUNT];
} Ov008CategoryFilter;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern const Ov008CategoryFilter data_ov025_020b3d68;
extern GameState *data_0204be18;
extern int   func_ov025_0208f26c(int nItemId);                          /* Ov008_IsGridItemEligible */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                /* AllocDefault */
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern char  func_ov025_02090ca8(Ov008MenuContext *pCtx, int nItemId);  /* Ov008_CountGridEntriesForOwner */
extern void  func_ov025_02090ddc(Ov008MenuContext *pCtx, NNSFndList *pList, Ov008InventoryItem *pItem); /* append */

void func_ov025_02090e44(Ov008MenuContext *pCtx)
{
    Ov008CategoryFilter filter;
    int i;
    int nItemId;
    Ov008Message15Record *pRecord;
    Ov008InventoryItem *pItem;

    filter = data_ov025_020b3d68;
    for (i = 0; i < CATEGORY_COUNT; i++) {
        pCtx->nTotal = 0;
        for (nItemId = 1; nItemId < ITEM_ID_END; nItemId++) {
            if (func_ov025_0208f26c(nItemId) != 0 && data_0204be18->aItemCount[nItemId] != 0) {
                pRecord = &pCtx->pRecords[nItemId];
                if (filter.aCategory[i] == CATEGORY_ANY || pRecord->nCategory == filter.aCategory[i]) {
                    pItem = NNSi_FndAllocFromDefaultExpHeap(sizeof(Ov008InventoryItem));
                    MI_CpuFill8(pItem, 0, sizeof(Ov008InventoryItem));
                    pItem->pRecord = pRecord;
                    pItem->nCount = data_0204be18->aItemCount[pRecord->nItemId];
                    pItem->nPlaced = func_ov025_02090ca8(pCtx, pItem->pRecord->nItemId);
                    pCtx->aPlaced[pItem->pRecord->nItemId] = pItem->nPlaced;
                    func_ov025_02090ddc(pCtx, &pCtx->aList[i], pItem);
                    pCtx->aCount[i]++;
                }
            }
        }
    }
}
