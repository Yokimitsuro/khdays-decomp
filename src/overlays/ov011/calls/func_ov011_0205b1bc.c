/* func_ov011_0205b1bc -- place a window against one of eight anchors.
 *
 * The anchor is the 3x3 grid without its centre, numbered in reading order: 0..2 across
 * the top, 3 and 4 down the sides, 5..7 across the bottom. Horizontally 0/3/5 hug the
 * left, 2/4/7 the right and 1/6 centre; vertically 0..2 hug the top, 5..7 the bottom and
 * 3/4 centre. Hugging an edge means one corner offset is zero and the opposite one is the
 * window's overhang -- its size in tiles times eight, less the screen extent, less a
 * per-anchor nudge. Centring zeroes both, and the third point is always cleared.
 *
 * The nudge is two 4-bit fields packed in one byte, and they have to be spelled as
 * bitfields. As `b & 0xf` and `b >> 4` mwcc emits `and #0xf` and folds the shift into the
 * subtraction, which is one instruction shorter than the ROM in each vertical arm; a
 * 4-bit bitfield read is exactly the shift-left/shift-right pair the ROM uses. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov011Size {
    u16 wRows;
    u16 wCols;
} Ov011Size;

typedef struct Ov011Point {
    s16 x;
    s16 y;
} Ov011Point;

typedef struct Ov011Window {
    u8               pad_00000[8];
    const Ov011Size *pSize;
    u8               pad_0000c[0x1091c - 0xc];
    Ov011Point       aCorner[2];
    Ov011Point       ptExtra;
} Ov011Window;

typedef struct Ov011Placement {
    u8  pad_00[4];
    int nAnchor;
    u8  nNudgeX : 4;
    u8  nNudgeY : 4;
} Ov011Placement;

void func_ov011_0205b1bc(Ov011Window *pWnd, const Ov011Placement *pPlace)
{
    switch (pPlace->nAnchor) {
    case 0:
    case 3:
    case 5:
        pWnd->aCorner[0].x = 0;
        pWnd->aCorner[1].x = (s16)(pWnd->pSize->wCols * 8 - 0x46 - pPlace->nNudgeX);
        break;
    case 2:
    case 4:
    case 7:
        pWnd->aCorner[0].x = (s16)(pWnd->pSize->wCols * 8 - 0x46 - pPlace->nNudgeX);
        pWnd->aCorner[1].x = 0;
        break;
    default:
        pWnd->aCorner[1].x = 0;
        pWnd->aCorner[0].x = 0;
        break;
    }
    switch (pPlace->nAnchor) {
    case 0:
    case 1:
    case 2:
        pWnd->aCorner[0].y = 0;
        pWnd->aCorner[1].y = (s16)(pWnd->pSize->wRows * 8 - 0xc0 - pPlace->nNudgeY);
        break;
    case 5:
    case 6:
    case 7:
        pWnd->aCorner[0].y = (s16)(pWnd->pSize->wRows * 8 - 0xc0 - pPlace->nNudgeY);
        pWnd->aCorner[1].y = 0;
        break;
    default:
        pWnd->aCorner[1].y = 0;
        pWnd->aCorner[0].y = 0;
        break;
    }
    pWnd->ptExtra.x = 0;
    pWnd->ptExtra.y = 0;
}
