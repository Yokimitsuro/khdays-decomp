/* func_ov008_02061f40 -- Ov008_RemoveGridNode: take the entry out of page
 * slot (nPage, nCol, nRow).  Nothing (0) when the slot is empty.  Otherwise a
 * summary snapshot is built (hooks +0x2090; slots +0x19c4, node list
 * +0x1e7c); unless bSilent or the grid busy word (+0x8) is set, the entry's
 * row counter (+0x14) is bumped down and the grid surface (+0xac) queued;
 * on the visible page the display cell is deactivated; the slot is cleared,
 * the node found there (Ov008_FindGridHit) has its cells cleared and is
 * unlinked (020609e4).  Unless bSilent the context summary (+0x1f78) is
 * rebuilt and diffed against the snapshot, the change set computed (tag 0x48
 * trigger, page-1 mission row when any change word is set), the row block
 * disabled and the equip panel refreshed.  The snapshot is released and the
 * grid hits rebuilt; returns 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAGE_COLS 5

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
} Ov008ShapeEntry;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    u8  pad_04[0x28 - 4];
} Ov008GridDisplayCell;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008GridChanges {
    u8  pad_00[8];
    int aChanged[4];          /* 0x08 */
    u8  pad_18[0xb8 - 0x18];
} Ov008GridChanges;

typedef struct Ov008MenuContext {
    u8  pad_0000[8];
    int nBusy;                /* 0x0008 */
    u8  pad_000c[0x18 - 0xc];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0xac - 0x1c];
    u8  gridSurface[0x10a0 - 0xac];     /* 0x00ac */
    Ov008GridDisplayCell gridDisplayCells[8][PAGE_COLS]; /* 0x10a0 */
    u8  pad_16e0[0x19c4 - 0x16e0];
    Ov008ShapeEntry *apPageSlot[3][8 * PAGE_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    u8  trackedNodeList[12];            /* 0x1e7c */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary;           /* 0x1f78 */
    u8  pad_2078[0x2090 - 0x2078];
    u8  summaryHooks[8];                /* 0x2090 */
} Ov008MenuContext;

extern void func_ov008_020533e4(Ov008GridSummary *pSummary, void *pHooks);        /* init a summary */
extern void func_ov008_02053470(Ov008GridSummary *pSummary, void *pSlots, void *pList); /* RebuildViewAndCountCells */
extern void func_ov008_0205e790(Ov008MenuContext *pCtx, int nItemId, char nDelta); /* Ov008_BumpRowCounter */
extern void func_020300f8(void *pSurface);                                        /* EnqueueObjGfxCommand */
extern void *func_ov008_0205fdac(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern void func_ov008_02060850(Ov008MenuContext *pCtx, void *pNode);             /* Ov008_ClearNodeCells */
extern void func_ov008_020609e4(Ov008MenuContext *pCtx, void *pNode);             /* unlink the node */
extern void func_ov008_0205eeac(Ov008GridSummary *pNew, Ov008GridSummary *pOld);  /* Ov008_DiffGridSummary */
extern int  func_ov008_0205eb6c(Ov008GridChanges *pOut, Ov008GridSummary *pOld, Ov008GridSummary *pNew);
extern void func_ov008_0206f694(void);                                            /* Ov008_TriggerTag48IfState0 */
extern void func_ov008_0206f644(void);                                            /* Ov008_EnableMissionRowOnPage1 */
extern void func_ov008_0206ebd8(void);                                            /* Ov008_DisableRowBlock */
extern void func_ov008_0206ed7c(Ov008GridSummary *pSummary);                      /* Ov008_RefreshEquipPanel */
extern void WM_EndKeySharing_0x02053464(Ov008GridSummary *pSummary);              /* release a summary */
extern void func_ov008_02060ae8(Ov008MenuContext *pCtx);                          /* Ov008_RebuildGridHits */

int func_ov008_02061f40(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent)
{
    Ov008GridSummary snapshot;
    Ov008GridChanges changes;
    Ov008ShapeEntry **pSlot;
    void *pNode;

    pSlot = &pCtx->apPageSlot[nPage][nRow * PAGE_COLS + nCol];
    if (*pSlot == 0) {
        return 0;
    }
    func_ov008_020533e4(&snapshot, pCtx->summaryHooks);
    func_ov008_02053470(&snapshot, pCtx->apPageSlot, pCtx->trackedNodeList);
    if (bSilent == 0 && pCtx->nBusy == 0) {
        func_ov008_0205e790(pCtx, (*pSlot)->nItemId, -1);
        func_020300f8(pCtx->gridSurface);
    }
    if (nPage == pCtx->nVisiblePage) {
        pCtx->gridDisplayCells[nRow][nCol].isActive = 0;
    }
    *pSlot = 0;
    pNode = func_ov008_0205fdac(pCtx, nPage, nCol, nRow);
    if (pNode != 0) {
        func_ov008_02060850(pCtx, pNode);
        func_ov008_020609e4(pCtx, pNode);
    }
    if (bSilent == 0) {
        func_ov008_02053470(&pCtx->summary, pCtx->apPageSlot, pCtx->trackedNodeList);
        func_ov008_0205eeac(&pCtx->summary, &snapshot);
        if (func_ov008_0205eb6c(&changes, &snapshot, &pCtx->summary) != 0) {
            func_ov008_0206f694();
        }
        if (changes.aChanged[0] != 0 || changes.aChanged[1] != 0 || changes.aChanged[2] != 0 || changes.aChanged[3] != 0) {
            func_ov008_0206f644();
        }
        func_ov008_0206ebd8();
        func_ov008_0206ed7c(&pCtx->summary);
    }
    WM_EndKeySharing_0x02053464(&snapshot);
    func_ov008_02060ae8(pCtx);
    return 1;
}
