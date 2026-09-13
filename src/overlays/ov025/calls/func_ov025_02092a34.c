/* func_ov025_02092a34 -- Ov008_PlaceNodeShape: place tracked node pNode with
 * its top-left cell at (nLeft, nTop) of page nPage; returns 1 when it fits.
 * Negative coordinates refuse.  The 8 x 5 box of the node's entry cell mask
 * (bit col + 8 * row) is walked, tracking the shape's used width and height;
 * a covered page grid byte (+0x1e88) holding another node's id refuses at
 * once, and the shape must fit inside the 5 x 8 page.  Unless bDryRun is set
 * every covered cell then takes the node's id (+0x0) and, on the visible page
 * (+0x18), a free slot id (02060484) is bound to the node (+0x20): its entry
 * gets the node's subitem set (+0x4), the cell offset (16.16 fixed point), the
 * shape's frame (entry +0xc) and is shown, and the slot's bit (id - 0x65) is
 * set in the 64-bit slot mask (+0x58).  The node's width / height (+0x14 /
 * +0x16) are stored.  Every refusal refreshes the "count" text pointer
 * (+0x2078) from variable record 0x1b of the records at +0x28c.  Codegen:
 * bDone = 0 is the first zero of the function -- every other zero (the
 * offset pair's initialiser, nHeight, the row counter) is a copy of its
 * register; the grid is indexed naturally (the invariant part is hoisted by
 * the compiler, walked in a register by the first loop and in its spill slot
 * by the second); the refusals share a static inline refresh and exit via
 * goto done.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define TEXT_COUNT 0x1b
#define SLOT_ID_BASE 0x65

typedef struct Ov008ShapeEntry {
    u8  pad_00[0xc];
    int nFrame;               /* 0x0c */
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00 */
    u8  pad_01[3];
    int nSubitemSet;          /* 0x04 */
    u8  pad_08[0x14 - 8];
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
    u8  pad_18[0x20 - 0x18];
    int nSlotId;              /* 0x20 */
    Ov008ShapeEntry *pEntry;  /* 0x24 */
} Ov008TrackedNode;

typedef struct Ov008CellOffset {
    int nX;                   /* 16.16 */
    int nY;
} Ov008CellOffset;

typedef struct Ov008MenuContext {
    u8    pad_0000[0x18];
    u32   nVisiblePage;                                   /* 0x0018 */
    u8    pad_001c[0x58 - 0x1c];
    u64   nSlotMask;                                      /* 0x0058: bit id - 0x65 */
    u8    pad_0060[0x28c - 0x60];
    u8    records[0x1e88 - 0x28c];                        /* 0x028c: variable text records */
    u8    aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];        /* 0x1e88 */
    u8    pad_1f00[0x2078 - 0x1f00];
    void *pCountText;                                     /* 0x2078 */
} Ov008MenuContext;

extern void *func_ov025_02089894(void *pRecords, int nIndex);           /* GetVarRecordByIndex */
extern int   func_ov025_020929d4(Ov008MenuContext *pCtx);               /* Ov008_FindFreeSlotId */
extern int   func_ov025_02084a7c(void);                                 /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                    /* FindEntryById */
extern void  func_ov025_020887c0(int nCtx, void *pEntry, int nSet);     /* Ov008_PushSubitemSet */
extern void  func_ov025_02088564(int nCtx, void *pEntry, Ov008CellOffset *pOffset); /* Ov008_ApplyOffsetSum */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);   /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */

static inline void Ov008_RefreshCountText(Ov008MenuContext *pCtx)
{
    pCtx->pCountText = func_ov025_02089894(pCtx->records, TEXT_COUNT);
}

int func_ov025_02092a34(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, int nPage, int nLeft, int nTop, int bDryRun)
{
    int nWidth;
    int nHeight;
    int bDone;
    Ov008CellOffset offset = {0, 0};
    int nRow;
    int nCol;
    int nId;
    int nSlotId;
    int nCtx;
    void *pEntry;

    bDone = 0;
    nWidth = 0;
    nHeight = 0;
    if (nLeft >= 0 && nTop >= 0) {
        for (nRow = 0; nRow < GRID_ROWS; nRow++) {
            for (nCol = 0; nCol < GRID_COLS; nCol++) {
                if ((pNode->pEntry->nCellMask & (1ULL << (nCol + nRow * 8))) != 0) {
                    if (nCol + 1 > nWidth) {
                        nWidth = nCol + 1;
                    }
                    nId = pCtx->aGrid[nPage][nTop + nRow][nLeft + nCol];
                    if (nRow + 1 > nHeight) {
                        nHeight = nRow + 1;
                    }
                    if (nId > 0 && nId != pNode->nId) {
                        Ov008_RefreshCountText(pCtx);
                        goto done;
                    }
                }
            }
        }
        if (nLeft + nWidth <= GRID_COLS && nTop + nHeight <= GRID_ROWS) {
            for (nRow = 0; nRow < GRID_ROWS; nRow++) {
                for (nCol = 0; nCol < GRID_COLS; nCol++) {
                    if (bDryRun == 0 && (pNode->pEntry->nCellMask & (1ULL << (nCol + nRow * 8))) != 0) {
                        pCtx->aGrid[nPage][nTop + nRow][nLeft + nCol] = pNode->nId;
                    }
                }
            }
        } else {
            Ov008_RefreshCountText(pCtx);
            goto done;
        }
        if (bDryRun == 0 && pCtx->nVisiblePage == nPage) {
            nSlotId = func_ov025_020929d4(pCtx);
            if (nSlotId >= 0) {
                nCtx = func_ov025_02084a7c();
                pEntry = func_ov025_0208843c(nCtx, nSlotId);
                func_ov025_020887c0(nCtx, pEntry, pNode->nSubitemSet);
                offset.nX = nLeft << 16;
                offset.nY = nTop << 16;
                func_ov025_02088564(nCtx, pEntry, &offset);
                func_ov025_02088928(nCtx, pEntry, (u16)pNode->pEntry->nFrame);
                func_ov025_0208884c(nCtx, pEntry, 1);
                pCtx->nSlotMask |= 1ULL << (nSlotId - SLOT_ID_BASE);
            }
            pNode->nSlotId = nSlotId;
        }
        pNode->nWidth = nWidth;
        pNode->nHeight = nHeight;
        bDone = 1;
    } else {
        Ov008_RefreshCountText(pCtx);
    }
done:
    return bDone;
}
