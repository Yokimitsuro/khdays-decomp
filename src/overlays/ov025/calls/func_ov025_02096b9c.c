/* func_ov025_02096b9c -- Ov008_SettleGridNodes: let every displaced grid node
 * find its place (02064440 until it reports nothing moved), then refresh what
 * depends on the grid.  A summary of the page slots (+0x19c4) and the node
 * list (+0x1e7c) is built on the stack (hooks from +0x2090) before the
 * settling; when nothing moved it is just released.  Otherwise the context's
 * own summary (+0x1f78) is rebuilt and diffed against the snapshot
 * (Ov008_DiffGridSummary), the row block disabled, the equip panel refreshed,
 * the change set computed (0205eb6c: tag 0x48 triggered when it reports
 * something, the page-1 mission row enabled when any of its four words is
 * set), the snapshot released, the grid hits rebuilt, cursor mode 0x14
 * requested, and the cursor cell re-stepped with the drop sound.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define CURSOR_MODE_DRAG 0x14
#define SOUND_DROP_OK    0x36

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008GridChanges {
    u8  pad_00[8];
    int aChanged[4];          /* 0x08 */
    u8  pad_18[0xb8 - 0x18];
} Ov008GridChanges;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x64];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x19c4 - 0x68];
    u8  apPageSlot[0x1e7c - 0x19c4];  /* 0x19c4 */
    u8  trackedNodeList[12];          /* 0x1e7c */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary;         /* 0x1f78 */
    u8  pad_2078[0x2090 - 0x2078];
    u8  summaryHooks[8];              /* 0x2090 */
} Ov008MenuContext;

extern void func_ov025_020871d4(Ov008GridSummary *pSummary, void *pHooks);        /* init a summary */
extern void func_ov025_02087260(Ov008GridSummary *pSummary, void *pSlots, void *pList); /* RebuildViewAndCountCells */
extern int  func_ov025_0209696c(Ov008MenuContext *pCtx);                          /* settle one node */
extern void WM_EndKeySharing_0x02087254(Ov008GridSummary *pSummary);                      /* release a summary */
extern void func_ov025_020913fc(Ov008GridSummary *pNew, Ov008GridSummary *pOld);  /* Ov008_DiffGridSummary */
extern void func_ov025_020a4264(void);                                            /* Ov008_DisableRowBlock */
extern void func_ov025_020a4408(Ov008GridSummary *pSummary);                      /* Ov008_RefreshEquipPanel */
extern int  func_ov025_020910e0(Ov008GridChanges *pOut, Ov008GridSummary *pOld, Ov008GridSummary *pNew);
extern void func_ov025_020a4c80(void);                                            /* Ov008_TriggerTag48IfState0 */
extern void func_ov025_020a4c30(void);                                            /* Ov008_EnableMissionRowOnPage1 */
extern void func_ov025_02093038(Ov008MenuContext *pCtx);                          /* Ov008_RebuildGridHits */
extern int  func_ov025_020a41f0(int nMode, int nA, int nB);                       /* cursor mode request */
extern int  func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep);
extern void func_02033b78(int nKind, int nSound);                                 /* PlaySound */

void func_ov025_02096b9c(Ov008MenuContext *pCtx)
{
    Ov008GridSummary snapshot;
    Ov008GridChanges changes;
    int bMoved;
    int bAgain;

    bMoved = 0;
    func_ov025_020871d4(&snapshot, pCtx->summaryHooks);
    func_ov025_02087260(&snapshot, pCtx->apPageSlot, pCtx->trackedNodeList);
    do {
        bAgain = func_ov025_0209696c(pCtx);
        if (bAgain != 0) {
            bMoved = 1;
        }
    } while (bAgain != 0);
    if (bMoved == 0) {
        WM_EndKeySharing_0x02087254(&snapshot);
        return;
    }
    func_ov025_02087260(&pCtx->summary, pCtx->apPageSlot, pCtx->trackedNodeList);
    func_ov025_020913fc(&pCtx->summary, &snapshot);
    func_ov025_020a4264();
    func_ov025_020a4408(&pCtx->summary);
    if (func_ov025_020910e0(&changes, &snapshot, &pCtx->summary) != 0) {
        func_ov025_020a4c80();
    }
    if (changes.aChanged[0] != 0 || changes.aChanged[1] != 0 || changes.aChanged[2] != 0 || changes.aChanged[3] != 0) {
        func_ov025_020a4c30();
    }
    WM_EndKeySharing_0x02087254(&snapshot);
    func_ov025_02093038(pCtx);
    func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 0);
    if (bMoved != 0) {
        func_ov025_02094988(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        func_02033b78(0, SOUND_DROP_OK);
    }
}
