/* func_ov008_02064924 -- Ov008_UpdateGridDrag: one step of dragging a node with
 * the stylus.  While the pen is down the drag position (+0x60/+0x62) follows the
 * touch and widget 3 is moved there (fx32).  On release the position is mapped
 * to a grid cell: no cell -> the grid is reset (cue 0x37); a cell -> it becomes
 * the cursor cell (+0x64/+0x66) and the drop is attempted (cue 0x36, or 4 when
 * refused).  Either way mode 2 is entered, menu button 5 refreshed and the drag
 * flag (+0x28) cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008TouchRecord {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
} Ov008TouchRecord;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x28];
    int bDrag;                /* 0x0028 */
    u8  pad_002c[0x60 - 0x2c];
    u16 nDragX;               /* 0x0060 */
    u16 nDragY;               /* 0x0062 */
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
} Ov008MenuContext;

#define WIDGET_DRAG 3
#define SOUND_DROP_OK   0x36
#define SOUND_DROP_NONE 0x37
#define SOUND_REFUSED   4

extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern int  func_ov008_020620ec(u16 *pCol, u16 *pRow, u16 nX, u16 nY);    /* Ov008_PixelToTileCell */
extern int  func_ov008_020617e0(Ov008MenuContext *pCtx, int nArg);        /* drop the dragged node */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void func_ov008_020631cc(Ov008MenuContext *pCtx, int nMode);
extern void func_ov008_0206f7b0(int nArg);                                /* Ov008_UpdateMenuButton5 */

void func_ov008_02064924(Ov008MenuContext *pCtx)
{
    u16 nCol;
    u16 nRow;
    Ov008TouchRecord touch;
    UiLayoutPos pos = { 0, 0 };
    int nCtx;

    func_ov008_02055dcc(&touch);
    nCtx = func_ov008_02050c54();
    if (touch.nTouching != 0) {
        pos.nX = touch.nX << 12;
        pos.nY = touch.nY << 12;
        pCtx->nDragX = touch.nX;
        pCtx->nDragY = touch.nY;
        func_ov008_02054858(nCtx, func_ov008_02054788(nCtx, WIDGET_DRAG), &pos);
        return;
    }
    if (func_ov008_020620ec(&nCol, &nRow, pCtx->nDragX, pCtx->nDragY) != 0) {
        pCtx->nColumn = nCol;
        pCtx->nRowSel = nRow;
        if (func_ov008_020617e0(pCtx, 0) != 0) {
            func_02033b78(0, SOUND_DROP_OK);
        } else {
            func_02033b78(0, SOUND_REFUSED);
        }
    } else {
        func_ov008_020615dc(pCtx, 0);
        func_02033b78(0, SOUND_DROP_NONE);
    }
    func_ov008_020631cc(pCtx, 2);
    func_ov008_0206f7b0(1);
    pCtx->bDrag = 0;
}
