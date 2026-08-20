/* Stamps one 4-by-8 block of cells onto the map at a screen position.
 *
 * The position is converted to cell coordinates, biased by the view's origin
 * and pulled back four cells on each axis so the block is centred on it. Each
 * of the eight rows paints four cells two columns apart, and the source pointer
 * walks forward one row of four bytes per pass.
 *
 * The tail cursor below is load-bearing, not style: reading the fourth cell
 * through its own pointer is what frees the scheduler to advance the row
 * pointer after that read rather than immediately before it. */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[8];
    int nOriginX;                   /* +0x08 */
    int nOriginY;                   /* +0x0c */
} Ov002MapView;

extern int data_ov002_0207f638;

extern void func_ov002_02064cd8(int *aCell, const void *pPos);
extern void func_ov002_02064d24(int x, int y, int nCell);

void func_ov002_02064e5c(u8 *pCells, const void *pPos) {
    int aCell[2];
    Ov002MapView *pView;
    int i;
    int x;
    int y;
    u8 *pTail;

    pView = (Ov002MapView *)data_ov002_0207f638;

    func_ov002_02064cd8(aCell, pPos);
    x = ((aCell[0] + 0x800) >> 12) - pView->nOriginX - 4;
    y = ((aCell[1] + 0x800) >> 12) - pView->nOriginY - 4;

    for (i = 0; i < 8; i++) {
        func_ov002_02064d24(x, y + i, pCells[0]);
        func_ov002_02064d24(x + 2, y + i, pCells[1]);
        func_ov002_02064d24(x + 4, y + i, pCells[2]);
        pTail = pCells;
        pCells += 4;
        func_ov002_02064d24(x + 6, y + i, pTail[3]);
    }
}
