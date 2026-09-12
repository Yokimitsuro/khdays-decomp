/* func_ov025_020966f8 -- Ov008_FindBestSpareItemForNode: from the slot's item
 * list record (db 0x16, index = the node's short at +0x22, slot 0xe) pick the
 * panel item record (0x9c each, table at ctx+0x207c) the player still has spare
 * copies of (stock above the grid count) that is not yet placed (+0x24 < 0) and
 * has the highest u16 rank at +0x92.  Returns the record, or 0 when the node has
 * no list or nothing qualifies.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define DB_ITEM_LISTS 0x16
#define DB_SLOT_LISTS 0xe

typedef struct Ov008ItemListRecord {
    u8   pad_00[0x10];
    u32  nCount;              /* 0x10 */
    int *aItemId;             /* 0x14 */
} Ov008ItemListRecord;

typedef struct Ov008Message15Record {
    u8  pad_00[0x24];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  pad_28[0x92 - 0x28];
    u16 nRank;                /* 0x92 */
    u8  pad_94[0x9c - 0x94];
} Ov008Message15Record;

typedef struct Ov008MessageCacheContextView {
    u8 pad_0000[0x207c];
    Ov008Message15Record *pMessage15Records;   /* 0x207c */
} Ov008MessageCacheContextView;

typedef struct Ov008TrackedNode {
    u8    pad_00[0x22];
    short nListIndex;         /* 0x22: -1 = none */
} Ov008TrackedNode;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern void func_020342e8(Ov008ItemListRecord **ppRecord, int nDbId, int nIndex, int nSlot); /* MsgDb_FetchRecord */
extern void func_020343cc(Ov008ItemListRecord **ppRecord);                    /* release the record */
extern char func_ov025_02090ca8(Ov008MessageCacheContextView *pCtx, int nItemId); /* Ov008_CountGridEntriesForOwner */

Ov008Message15Record *func_ov025_020966f8(Ov008MessageCacheContextView *pCtx, Ov008TrackedNode *pNode)
{
    Ov008Message15Record *pBest = 0;
    Ov008ItemListRecord *pList = 0;
    u32 i;
    int nItemId;
    Ov008Message15Record *pItem;

    if (pNode->nListIndex < 0) {
        return 0;
    }
    func_020342e8(&pList, DB_ITEM_LISTS, pNode->nListIndex, DB_SLOT_LISTS);
    for (i = 0; i < pList->nCount; i++) {
        nItemId = pList->aItemId[i];
        if ((u32)func_ov025_02090ca8(pCtx, nItemId) < data_0204be18->aItemCount[nItemId]) {
            pItem = &pCtx->pMessage15Records[nItemId];
            if (pItem->nPlacedSlot < 0 && (pBest == 0 || pBest->nRank < pItem->nRank)) {
                pBest = pItem;
            }
        }
    }
    func_020343cc(&pList);
    return pBest;
}
