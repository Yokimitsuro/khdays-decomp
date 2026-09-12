/* func_ov025_020972d8 -- Ov008_LayoutSecondaryList: place the secondary list's
 * quads from the layout of widget 3: the list origin (+0x182c/+0x182e, in
 * pixels, offset (-3, -11)); when the list's node (+0x19b4) is placed (+0x24
 * >= 0) widget 0xc9 is moved to the origin minus the node's (col, row) cell
 * offset (16 px cells); then every tracked grid node in the list at +0x19b8 gets
 * its column-header cell (+0x1858/+0x185a, 0x28 apart) at origin + 16 * (col, row).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008TrackedGridNode {
    void *pEntry;             /* 0x00 */
    int   columnOffset;       /* 0x04 */
    int   rowOffset;          /* 0x08 */
} Ov008TrackedGridNode;

typedef struct Ov008PlacedNode {
    u8  pad_00[0x24];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nCol;                 /* 0x28 */
    u8  nRow;                 /* 0x29 */
} Ov008PlacedNode;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    u8  pad_04[8];
    s16 nX;                   /* 0x0c */
    s16 nY;                   /* 0x0e */
    u8  pad_10[0x28 - 0x10];
} Ov008GridDisplayCell;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x182c];
    s16 nListOriginX;         /* 0x182c */
    s16 nListOriginY;         /* 0x182e */
    u8  pad_1830[0x184c - 0x1830];
    Ov008GridDisplayCell colHeaderCells[9];  /* 0x184c */
    Ov008PlacedNode *pListNode; /* 0x19b4 */
    u8  trackedNodeList[12];  /* 0x19b8 */
} Ov008MenuContext;

#define CELL_PX 16
#define ORIGIN_DX 3
#define ORIGIN_DY 11
#define WIDGET_LIST_FRAME 3
#define WIDGET_LIST_CURSOR 0xc9

extern int func_ov025_02084a7c(void);                               /* Ov008_GetContext */
extern int func_ov025_0208843c(int nCtx, int nId);                  /* FindEntryById */
extern UiLayoutPos *func_ov025_020884c8(int nCtx, int nEntry);      /* Ov008_GetEntryPos */
extern void func_ov025_02088500(int nCtx, int nEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);

void func_ov025_020972d8(Ov008MenuContext *pCtx)
{
    int nCtx;
    UiLayoutPos *pPos;
    UiLayoutPos pos;
    int nOriginX;
    int nOriginY;
    Ov008TrackedGridNode *pNode;
    u8 *pWalk;

    nCtx = func_ov025_02084a7c();
    pPos = func_ov025_020884c8(nCtx, func_ov025_0208843c(nCtx, WIDGET_LIST_FRAME));
    nOriginX = (pPos->nX >> 12) - ORIGIN_DX;
    nOriginY = (pPos->nY >> 12) - ORIGIN_DY;
    pCtx->nListOriginX = nOriginX;
    pCtx->nListOriginY = nOriginY;
    if (pCtx->pListNode->nPlacedSlot >= 0) {
        pos.nX = pPos->nX - ((pCtx->pListNode->nCol * CELL_PX + ORIGIN_DX) << 12);
        pos.nY = pPos->nY - ((pCtx->pListNode->nRow * CELL_PX + ORIGIN_DY) << 12);
        func_ov025_02088500(nCtx, func_ov025_0208843c(nCtx, WIDGET_LIST_CURSOR), &pos);
    }
    /* the ROM walks the context pointer itself in cell steps (0x28) and folds the
     * first column-header cell's x/y (ctx+0x1858/0x185a) into the offsets */
    pWalk = (u8 *)pCtx;
    for (pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0); pNode != 0;
         pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode)) {
        *(s16 *)(pWalk + 0x1858) = nOriginX + pNode->columnOffset * CELL_PX;
        *(s16 *)(pWalk + 0x185a) = nOriginY + pNode->rowOffset * CELL_PX;
        pWalk += sizeof(Ov008GridDisplayCell);
    }
}
