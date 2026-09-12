/* func_ov008_02064eb4 -- Ov008_DrawGridMenu: draw the grid menu's quads.  After
 * the default 3D view is set up: the cursor quad (+0x1820 / +0x1824) when shown,
 * the nine column-header cells (+0x184c), the eight row-header cells (+0x16e0),
 * then the 8 x 5 grid cells (+0x10a0); every cell is a 0x28-byte "shown" word
 * followed by its Ov008MenuQuad.  Ends with the draw flush.
 */
typedef unsigned char u8;

typedef struct Ov008MenuQuad {
    u8 pad[0x24];
} Ov008MenuQuad;

typedef struct Ov008GridDisplayCell {
    int           isActive;   /* 0x00 */
    Ov008MenuQuad quad;       /* 0x04 */
} Ov008GridDisplayCell;

#define GRID_ROWS 8
#define GRID_COLS 5
#define COL_HEADERS 9
#define ROW_HEADERS 8

typedef struct Ov008GridMenuContextView {
    u8 pad_0000[0x10a0];
    Ov008GridDisplayCell gridDisplayCells[GRID_ROWS][GRID_COLS];  /* 0x10a0 */
    Ov008GridDisplayCell rowHeaderCells[ROW_HEADERS];             /* 0x16e0 */
    Ov008GridDisplayCell cursorCell;                              /* 0x1820 */
    u8 pad_1848[0x184c - 0x1848];
    Ov008GridDisplayCell colHeaderCells[COL_HEADERS];             /* 0x184c */
} Ov008GridMenuContextView;

extern void func_ov008_02056a74(void);                     /* Ov008_SetupDefault3dView */
extern void func_ov008_02056bc0(Ov008MenuQuad *pQuad);     /* Ov008_DrawMenuQuad */
extern void func_ov008_02056bbc(void);                     /* draw flush */

void func_ov008_02064eb4(Ov008GridMenuContextView *pCtx)
{
    int i;
    int j;

    func_ov008_02056a74();
    if (pCtx->cursorCell.isActive != 0) {
        func_ov008_02056bc0(&pCtx->cursorCell.quad);
    }
    for (i = 0; i < COL_HEADERS; i++) {
        if (pCtx->colHeaderCells[i].isActive != 0) {
            func_ov008_02056bc0(&pCtx->colHeaderCells[i].quad);
        }
    }
    for (i = 0; i < ROW_HEADERS; i++) {
        if (pCtx->rowHeaderCells[i].isActive != 0) {
            func_ov008_02056bc0(&pCtx->rowHeaderCells[i].quad);
        }
    }
    for (i = 0; i < GRID_ROWS; i++) {
        for (j = 0; j < GRID_COLS; j++) {
            if (pCtx->gridDisplayCells[i][j].isActive != 0) {
                func_ov008_02056bc0(&pCtx->gridDisplayCells[i][j].quad);
            }
        }
    }
    func_ov008_02056bbc();
}
