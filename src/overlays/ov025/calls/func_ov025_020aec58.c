/* func_ov025_020aec58 -- Ov025_ScrollList_HandleTouch: the scrolling list's stylus input
 * (page B).  The touch record of the shared block (02084a64; 02089834) is used while it is a
 * fresh press (words +4 == 1 and +6 == 0): x from 0xe0 on grabs the scroll bar (+0xc of the
 * list set; Ov025_ScrollList_TouchKnob 020ae634); otherwise, above y 0xae, the row under the
 * stylus (y less 16 plus the pixel scroll +0x2d0, 16 a row) is confirmed when it is the cursor
 * (020ae0f0) or selected with sound (020adee0), and the press flag (+0x10) set. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct TileBlock {
    u8   pad_00[0x20];
    void *pData;              /* 0x20 */
} TileBlock;

typedef struct TileSurface {
    void *pixels;             /* 0x00 */
    int  width;               /* 0x04 */
    int  height;              /* 0x08 */
    int  totalBytes;          /* 0x0c */
    int  rowBytes;            /* 0x10 */
    int  unknown14;           /* 0x14 */
    TileBlock *current;       /* 0x18 */
    void *currentData;        /* 0x1c */
    u8   pad_20[0x3c - 0x20];
} TileSurface;                /* 0x3c */

typedef struct Ov025ScrollRow {
    int  nMission;            /* 0x00 */
    int  nDay;                /* 0x04 */
    const u16 *pName;         /* 0x08 */
    int  nField0c;            /* 0x0c */
} Ov025ScrollRow;             /* 0x10 */

typedef struct Ov025ScrollList {
    int  nField000;           /* 0x000 */
    Ov025ScrollRow *pRows;    /* 0x004: the day rows */
    int  nCount;              /* 0x008 */
    int  bTouching;           /* 0x00c: the stylus holds the scroll bar */
    int  bPressed;            /* 0x010 */
    int  bRowsDirty;          /* 0x014: re-upload the row surfaces */
    int  bMarkersDirty;       /* 0x018: re-upload the marker screen */
    u8   strings[0x10];       /* 0x01c: the row name strings */
    void *pNode;              /* 0x02c: the shared UI list node */
    TileSurface aSurface[11]; /* 0x030: one text surface per row */
    int  bDirty;              /* 0x2c4 */
    int  nCursor;             /* 0x2c8 */
    int  nField2cc;           /* 0x2cc */
    int  nScroll;             /* 0x2d0: in pixels, 16 per row */
    int  nPrevScroll;         /* 0x2d4 */
    int  nScrollMax;          /* 0x2d8 */
    int  nKnob;               /* 0x2dc */
    int  nKnobHeight;         /* 0x2e0 */
    int  nKnobMax;            /* 0x2e4 */
} Ov025ScrollList;            /* 0x2e8: the day list view of page B (Ov025_GetPageB) */

typedef struct Ov025TouchState {
    u16  nX;                  /* 0x00 */
    u16  nY;                  /* 0x02 */
    u16  nTouching;           /* 0x04 */
    u16  nPhase;              /* 0x06 */
} Ov025TouchState;

extern Ov025ScrollList *func_ov025_02084b14(void);                  /* Ov025_GetPageB */
extern int   func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c */
extern void  func_ov025_02089834(int nBlock, Ov025TouchState *pOut); /* copy the touch record */
extern void  func_ov025_020ae634(Ov025ScrollList *pList);           /* Ov025_ScrollList_TouchKnob */
extern void  func_ov025_020ae0f0(Ov025ScrollList *pList);           /* Ov025_ScrollList_Confirm */
extern void  func_ov025_020adee0(Ov025ScrollList *pList, int nRow, int bSound); /* Ov025_ScrollList_SelectRow */

void func_ov025_020aec58(void)
{
    Ov025ScrollList *pList;
    Ov025TouchState touch;
    int nRow;

    pList = func_ov025_02084b14();
    func_ov025_02089834(func_ov025_02084a64(), &touch);
    if (touch.nTouching != 1 || touch.nPhase != 0) {
        return;
    }
    if (touch.nX < 0xe0) {
        nRow = (touch.nY - 0x10 + pList->nScroll) / 16;
        if (touch.nY < 0xae) {
            if (nRow < pList->nCount) {
                if (nRow == pList->nCursor) {
                    func_ov025_020ae0f0(pList);
                } else {
                    func_ov025_020adee0(pList, nRow, 1);
                }
                pList->bPressed = 1;
            }
        }
    } else {
        pList->bTouching = 1;
        func_ov025_020ae634(pList);
    }
}
