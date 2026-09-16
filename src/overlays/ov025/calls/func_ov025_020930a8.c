/* func_ov025_020930a8 -- Ov008_PlaceTrackedNode: place item record pRecord on
 * page nPage with its anchor cell at (nCol, nRow) as a new tracked node.  A
 * record without a shape (+0x24 < 0) needs no node and answers 1.  Otherwise
 * a 0x34-byte node is allocated and zeroed, its links (+0x20/+0x22) set to
 * -1 and its shape (+0x24, from the shape table at +0x2080, 0x18 each)
 * bound; a node id is assigned (failure frees the node and answers 0).  The
 * box origin is the anchor minus the shape's anchor offsets (+0x28/+0x29);
 * when the node cannot be placed on the visible page (020604e4) it is
 * unlinked (answer 0).  Otherwise the node records page, origin and anchor,
 * and every cell of the shape mask (bit col + 8 * row) other than the anchor
 * has its grid slot cleared.  Returns 1.
 * Codegen: the counters are declared before nLeft / nTop -- the spill slots
 * follow the declaration order (nTop [sp+8], nLeft [sp+0xc], the row counter
 * [sp+0x10]); with the counters declared last the two outer slots swap.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define GRID_ROWS 8
#define GRID_COLS 5

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008Message15Record {
    u8  pad_00[0x24];
    int nShapeIndex;          /* 0x24: -1 = none */
    u8  nAnchorColOff;        /* 0x28 */
    u8  nAnchorRowOff;        /* 0x29 */
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00: grid cell id */
    u8  pad_01[9];
    u16 nPage;                /* 0x0a */
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u8  pad_14[0xc];
    int nLinks;               /* 0x20: nLinkA / nListIndex shorts, both -1 */
    Ov008ShapeEntry *pEntry;  /* 0x24 */
    u8  pad_28[0x34 - 0x28];
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x2080 - 0x1c];
    Ov008ShapeEntry *pShapes; /* 0x2080 */
} Ov008MenuContext;

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                 /* AllocDefault */
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern u8    func_ov025_02092e94(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode); /* Ov008_AssignTrackedNodeId */
extern int   func_ov025_02092a34(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, u32 nPage, int nLeft, int nTop, int nArg); /* place the node */
extern void  func_ov025_02092f34(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode); /* unlink a tracked node */
extern void  func_ov025_02094390(Ov008MenuContext *pCtx, u16 nPage, u16 nX, u16 nY); /* Ov008_ClearGridSlot */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);

int func_ov025_020930a8(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, int nCol, int nRow)
{
    int nResult;
    Ov008TrackedNode *pNode;
    int i;
    int j;
    int nLeft;
    int nTop;

    nResult = 0;
    if (pRecord->nShapeIndex >= 0) {
        pNode = NNSi_FndAllocFromDefaultExpHeap(sizeof(Ov008TrackedNode));
        MI_CpuFill8(pNode, 0, sizeof(Ov008TrackedNode));
        pNode->nLinks = -1;
        pNode->pEntry = &pCtx->pShapes[pRecord->nShapeIndex];
        if (func_ov025_02092e94(pCtx, pNode) != 0) {
            nLeft = nCol - pRecord->nAnchorColOff;
            nTop = nRow - pRecord->nAnchorRowOff;
            if (func_ov025_02092a34(pCtx, pNode, pCtx->nVisiblePage, nLeft, nTop, 0) != 0) {
                pNode->nPage = nPage;
                pNode->nLeft = nLeft;
                pNode->nTop = nTop;
                pNode->nAnchorCol = nCol;
                pNode->nAnchorRow = nRow;
                for (i = 0; i < GRID_ROWS; i++) {
                    for (j = 0; j < GRID_COLS; j++) {
                        if ((pNode->pEntry->nCellMask & (1ULL << (j + i * 8))) != 0) {
                            if (pNode->nAnchorCol != nLeft + j || pNode->nAnchorRow != nTop + i) {
                                func_ov025_02094390(pCtx, (u16)nPage, (u16)(nLeft + j), (u16)(nTop + i));
                            }
                        }
                    }
                }
                nResult = 1;
            } else {
                func_ov025_02092f34(pCtx, pNode);
            }
        } else {
            if (pNode != 0) {
                NNSi_FndFreeFromDefaultHeap(pNode);
            }
        }
    } else {
        nResult = 1;
    }
    return nResult;
}
