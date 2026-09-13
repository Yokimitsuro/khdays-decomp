/* func_ov008_02064a34 -- Ov008_UpdateNodeDrag: one step of dragging a placed
 * node with the stylus (the list-item twin of Ov008_UpdateGridDrag).  While
 * the pen is down the drag position (+0x60/+0x62) follows the touch and widget
 * 3 is moved there (fx32).  On release the position is mapped to a grid cell:
 * a cell becomes the cursor cell (+0x64/+0x66) and the node is dropped there
 * (02062848; cue 0x36, or grid reset 1 + hit rebuild + cue 4 when refused);
 * no cell puts the node back where it came from (02061f40 with +0x68 and the
 * +0x6c/+0x6e cell, cue 0x37) after a grid reset.  Either way the drag
 * position is cleared to 0xffff, mode 2 entered, the layout refreshed
 * (020631cc 1), the scroll flag (+0x2c) cleared and menu button 5 refreshed.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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
    u8  pad_0000[0x10];
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x2c - 0x14];
    int bScroll;              /* 0x002c */
    u8  pad_0030[0x60 - 0x30];
    u16 nDragX;               /* 0x0060 */
    u16 nDragY;               /* 0x0062 */
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u32 nDragNode;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
} Ov008MenuContext;

#define WIDGET_DRAG 3
#define SOUND_DROP_OK   0x36
#define SOUND_DROP_NONE 0x37
#define SOUND_REFUSED   4
#define DRAG_NONE       0xffff

extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern int  func_ov008_020620ec(u16 *pCol, u16 *pRow, u16 nX, u16 nY);    /* Ov008_PixelToTileCell */
extern int  func_ov008_02062848(Ov008MenuContext *pCtx);                  /* drop the dragged node */
extern void func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void func_ov008_02060ae8(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern int  func_ov008_02061f40(Ov008MenuContext *pCtx, u32 nNode, u32 nCol, u32 nRow, int nArg); /* put the node back */
extern void func_ov008_020631cc(Ov008MenuContext *pCtx, int nMode);
extern void func_ov008_0206f7b0(int nArg);                                /* Ov008_UpdateMenuButton5 */

void func_ov008_02064a34(Ov008MenuContext *pCtx)
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
        if (func_ov008_02062848(pCtx) == 0) {
            func_ov008_020615dc(pCtx, 1);
            func_ov008_02060ae8(pCtx);
            func_02033b78(0, SOUND_REFUSED);
        } else {
            func_02033b78(0, SOUND_DROP_OK);
        }
    } else {
        func_ov008_02061f40(pCtx, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow, 0);
        func_ov008_020615dc(pCtx, 0);
        func_02033b78(0, SOUND_DROP_NONE);
    }
    pCtx->nDragX = DRAG_NONE;
    pCtx->nDragY = DRAG_NONE;
    pCtx->menuState = 2;
    func_ov008_020631cc(pCtx, 1);
    pCtx->bScroll = 0;
    func_ov008_0206f7b0(1);
}
