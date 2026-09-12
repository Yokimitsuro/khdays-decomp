/* func_ov008_02083118 -- Ov008_InitColumnCells: create the 48 cells of the
 * two three-row columns of the panel at ctx+0xc254 (six rows of eight cells):
 * for each of the eight positions, three cells of kinds 0/3/2 at x = 0xa3 for
 * the left column and kinds 1/3/2 at x = 0xb5 for the right, all at
 * y = 0x4d - 8 * (8 - i) (fx32).  Then clears both selected-row and base
 * words (+0xc0..+0xcc) and redraws both columns.
 */
typedef unsigned char u8;

#define ROW_CELLS   8
#define LEFT_X      (0xa3 << 12)
#define RIGHT_X     (0xb5 << 12)

typedef struct Ov008ColumnPanel {
    int aCell[6][ROW_CELLS];  /* 0x00: rows 0..2 left column, 3..5 right column */
    int nLeftSelected;        /* 0xc0 */
    int nRightSelected;       /* 0xc4 */
    int nLeftBase;            /* 0xc8 */
    int nRightBase;           /* 0xcc */
} Ov008ColumnPanel;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xbfb4];
    int *hSlotsB;             /* 0xbfb4 */
    u8   pad_bfb8[0xc254 - 0xbfb8];
    Ov008ColumnPanel columns; /* 0xc254 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern int  func_ov008_02082ecc(int *hSlots, unsigned int nKind, int nSlot, int nY, int nX); /* create a cell */
extern void func_ov008_02083360(void);                                  /* Ov008_RedrawBothColumns */

void func_ov008_02083118(void)
{
    Ov008PanelContext *ctx;
    Ov008ColumnPanel *pPanel;
    int *hSlots;
    int i;
    int nY;

    ctx = data_ov008_02090fac;
    pPanel = &ctx->columns;
    hSlots = ctx->hSlotsB;
    for (i = 0; i < ROW_CELLS; i++) {
        nY = (0x4d - (8 - i) * 8) << 12;
        pPanel->aCell[0][i] = func_ov008_02082ecc(hSlots, 0, 0, nY, LEFT_X);
        pPanel->aCell[1][i] = func_ov008_02082ecc(hSlots, 3, 0, nY, LEFT_X);
        pPanel->aCell[2][i] = func_ov008_02082ecc(hSlots, 2, 0, nY, LEFT_X);
        pPanel->aCell[3][i] = func_ov008_02082ecc(hSlots, 1, 0, nY, RIGHT_X);
        pPanel->aCell[4][i] = func_ov008_02082ecc(hSlots, 3, 0, nY, RIGHT_X);
        pPanel->aCell[5][i] = func_ov008_02082ecc(hSlots, 2, 0, nY, RIGHT_X);
    }
    pPanel->nLeftSelected = 0;
    pPanel->nRightSelected = 0;
    pPanel->nLeftBase = 0;
    pPanel->nRightBase = 0;
    func_ov008_02083360();
}
