/* func_ov008_02065ce8 -- Ov008_DestroyGridMenu: tear the panel grid menu down.
 * The tracked grid cells are cleared, the text loader (+0x1e68) shut, the
 * widget lists and the embedded sub-objects (0205f8d0) freed, the reveal mask
 * rebuilt and every tracked node unlinked (list at +0x1e7c).  The item ids of
 * the 3 x 40 page slots (+0x19c4) are then saved to GameState equippedItems
 * (0xee0, 0 for an empty slot); the summary (+0x1f78) and the variable text
 * records (+0x28c) are released, the main display's mode bits (DISPCNT bits
 * 13-15) cleared, the icon texture archive (+0x364) freed, block 9500 and the
 * context reset, the scratch buffers freed, resource slots 0x15, 0x14, 0x1b,
 * 0x16, 0x13 and the slot at +0x209c dereferenced, the pending bit ranges
 * forwarded and the context callback word cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES 3
#define PAGE_SLOTS 40
#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define DISPCNT_MODE_BITS 0xe000

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    u8  pad_18[0x9c - 0x18];
} Ov008Message15Record;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x28c];
    u8  records[0x364 - 0x28c];                   /* 0x028c: variable text records */
    void *pIconArchive;                           /* 0x0364 */
    u8  pad_0368[0x19c4 - 0x368];
    Ov008Message15Record *apPageSlot[GRID_PAGES][PAGE_SLOTS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e68 - 0x1ba4];
    u8  textLoader[0x14];                         /* 0x1e68 */
    u8  trackedNodeList[12];                      /* 0x1e7c */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary;                     /* 0x1f78 */
    u8  pad_2078[0x209c - 0x2078];
    int nResourceSlot;                            /* 0x209c */
} Ov008MenuContext;

typedef struct GameState {
    u8  pad_0000[0xee0];
    u16 equippedItems[GRID_PAGES][PAGE_SLOTS];    /* 0x0ee0 */
} GameState;

extern GameState *data_0204be18;
extern void  func_ov008_0205cb08(Ov008MenuContext *pCtx);                /* Ov008_ClearTrackedGridCells */
extern void  func_ov008_0208e650(void *pObject);                          /* ov008_InvokeMethod8 */
extern void  func_ov008_0205ea18(Ov008MenuContext *pCtx);                /* Ov008_FreeAllWidgetLists */
extern void  func_ov008_0205f8d0(Ov008MenuContext *pCtx);                /* free the embedded sub-objects */
extern void  func_ov008_02060a0c(Ov008MenuContext *pCtx);                /* Ov008_RebuildPanelRevealMask */
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void  func_ov008_020609e4(Ov008MenuContext *pCtx, void *pNode);   /* unlink a tracked node */
extern void  WM_EndKeySharing_0x02053464(Ov008GridSummary *pSummary);    /* release a summary */
extern void  func_ov008_02055c74(void *pRecords);                         /* release a text cache */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *func_ov008_02050c28(void);                                   /* Ov008_GetCtxBlock9500 */
extern void *func_ov008_02050c54(void);                                   /* Ov008_GetContext */
extern void  func_ov008_020559a8(void *pBlock);
extern void  func_ov008_020546ec(void *pContext);                         /* Ov008_Set_46ec */
extern void  func_ov008_02054720(void *pContext);
extern void  func_ov008_0205c968(Ov008MenuContext *pCtx);                /* Ov008_FreeScratchBuffers */
extern void  func_ov008_020510f8(int nSlot);                              /* Ov008_DecRefSlot */
extern void  func_ov008_02065540(Ov008MenuContext *pCtx);                /* Ov008_ForwardSetBitsInRange */
extern void  func_ov008_0205477c(void *pContext, void *pCallback);        /* ov008_StoreWordAt0x4a50 */

void func_ov008_02065ce8(Ov008MenuContext *pCtx)
{
    void *pNode;
    void *pNext;
    int nPage;
    int i;
    Ov008Message15Record *pRecord;
    void *pBlock;
    void *pContext;

    func_ov008_0205cb08(pCtx);
    func_ov008_0208e650(pCtx->textLoader);
    func_ov008_0205ea18(pCtx);
    func_ov008_0205f8d0(pCtx);
    func_ov008_02060a0c(pCtx);
    pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0);
    while (pNode != 0) {
        pNext = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode);
        func_ov008_020609e4(pCtx, pNode);
        pNode = pNext;
    }
    for (nPage = 0; nPage < GRID_PAGES; nPage++) {
        for (i = 0; i < PAGE_SLOTS; i++) {
            pRecord = pCtx->apPageSlot[nPage][i];
            if (pRecord != 0) {
                data_0204be18->equippedItems[nPage][i] = pRecord->nItemId;
            } else {
                data_0204be18->equippedItems[nPage][i] = 0;
            }
        }
    }
    WM_EndKeySharing_0x02053464(&pCtx->summary);
    func_ov008_02055c74(pCtx->records);
    REG_DISPCNT &= ~DISPCNT_MODE_BITS;
    if (pCtx->pIconArchive != 0) {
        NNSi_FndFreeFromDefaultHeap(pCtx->pIconArchive);
        pCtx->pIconArchive = 0;
    }
    pBlock = func_ov008_02050c28();
    pContext = func_ov008_02050c54();
    func_ov008_020559a8(pBlock);
    func_ov008_020546ec(pContext);
    func_ov008_02054720(pContext);
    func_ov008_0205c968(pCtx);
    func_ov008_020510f8(0x15);
    func_ov008_020510f8(0x14);
    func_ov008_020510f8(0x1b);
    func_ov008_020510f8(0x16);
    func_ov008_020510f8(0x13);
    func_ov008_020510f8(pCtx->nResourceSlot);
    func_ov008_02065540(pCtx);
    func_ov008_0205477c(pContext, 0);
}
