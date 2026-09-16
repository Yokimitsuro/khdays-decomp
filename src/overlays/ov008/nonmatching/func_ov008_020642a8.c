/* NOT MATCHING -- 248 of 408 bytes, 74 of 102 instructions aligned.
 *
 * Exact size and exact relocations; the head, the list search, the entry
 * lookup and the switch are byte identical. The residue is the inner grid loop:
 * the ROM keeps two separate `row * 5` induction variables (lr for the grid
 * byte pointer, r5 for the page slot, `mov r5, lr` in the outer preheader,
 * both stepped by 5) and computes the slot address as
 * `add sl, ip, r5 ; add sl, r0, sl, lsl #2 ; add sl, sl, #0x1000` with the
 * page-slot base kept in scratch r0 and the context spilled; build 139 merges
 * the two induction variables and reassociates `base + (col + row5) << 2` into
 * a per-row base plus `[base, col, lsl #2]`. `nRow * 5u` here splits the CSE
 * (a second `add r0, r3, r3, lsl #2` per row) but the reassociation stays;
 * `opt_loop_invariants off` does not touch it and `opt_strength_reduction off`
 * changes everything else.
 *
 * Swept: walking / byte / 3-D grid forms, page-slot locals (full and byte
 * bases), shared cell index, explicit compound row IVs, index spellings and
 * casts, 49 pragmas, the C++ lane, a 2000-cell random cross product over 17
 * axes. Left for decomp.me.
 */
/* func_ov008_020642a8 -- Ov008_FillNodeGap: try to fill an empty cell of the
 * tracked node under the cursor.  The cursor cell's grid id (aGrid at the
 * visible page) selects the node from the node list (+0x1e7c, id byte at +0);
 * the node's anchor slot (page slots at +0x19c4, from the node's +0x10/+0x12
 * cell) must hold an entry.  The node's box (+0xc/+0xe, +0x14 x +0x16) is
 * scanned for a cell carrying the id whose page slot is empty; the first one
 * is filled by the entry's kind (+0x18): 1 -> 02063cac(node), 4 ->
 * 02063e58(node, entry), else Ov008_FindBestSpareItemForNode(entry).
 * Returns 1 when the fill succeeded, 0 otherwise.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_PAGE_BYTES 0x28
#define GRID_COLS  5
#define ENTRY_KIND_SINGLE 1
#define ENTRY_KIND_PAIR   4

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x18];
    int nKind;                /* 0x18 */
} Ov008ShapeEntry;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00: grid cell id */
    u8  pad_01[0xb];
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x64 - 0x1c];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x19c4 - 0x68];
    Ov008ShapeEntry *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    u8  trackedNodeList[12];  /* 0x1e7c */
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
} Ov008MenuContext;

extern Ov008TrackedNode *NNS_FndGetNextListObject(void *pList, void *pObject);
extern int func_ov008_02063cac(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode);
extern int func_ov008_02063e58(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, Ov008ShapeEntry *pEntry);
extern void *func_ov008_020641cc(Ov008MenuContext *pCtx, Ov008ShapeEntry *pEntry); /* Ov008_FindBestSpareItemForNode */

int func_ov008_020642a8(Ov008MenuContext *pCtx)
{
    u8 nId;
    Ov008TrackedNode *pNode;
    Ov008ShapeEntry *pEntry;
    u32 nPage;
    int nRow;
    int nCol;
    int nRowEnd;
    int nColEnd;
    int nResult;
    u8 *pGrid;

    nId = pCtx->aGrid[pCtx->nVisiblePage][pCtx->nRowSel][pCtx->nColumn];
    for (pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0); pNode != 0;
         pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode)) {
        if (pNode->nId == nId) {
            break;
        }
    }
    if (pNode == 0) {
        return 0;
    }
    nPage = pCtx->nVisiblePage;
    pEntry = pCtx->apPageSlot[nPage][pNode->nAnchorRow * GRID_COLS + pNode->nAnchorCol];
    if (pEntry == 0) {
        return 0;
    }
    nRowEnd = pNode->nTop + pNode->nHeight;
    for (nRow = pNode->nTop; nRow < nRowEnd; nRow++) {
        nColEnd = pNode->nLeft + pNode->nWidth;
        pGrid = (u8 *)pCtx + nPage * GRID_PAGE_BYTES + nRow * GRID_COLS + pNode->nLeft;
        for (nCol = pNode->nLeft; nCol < nColEnd; nCol++) {
            if (nId == pGrid[0x1e88] && pCtx->apPageSlot[nPage][nCol + nRow * 5u] == 0) {
                goto found;
            }
            pGrid++;
        }
    }
    return 0;
found:
    switch (pEntry->nKind) {
    case ENTRY_KIND_SINGLE:
        nResult = func_ov008_02063cac(pCtx, pNode);
        break;
    case ENTRY_KIND_PAIR:
        nResult = func_ov008_02063e58(pCtx, pNode, pEntry);
        break;
    default:
        nResult = (int)func_ov008_020641cc(pCtx, pEntry);
        break;
    }
    return nResult != 0;
}
