/* Ov011_StepPaneScroll -- move one title pane along its scripted scroll: interpolate the
 * position between (nStartX, nStartY) and (nEndX, nEndY) over [wStartTime, wEndTime] of the
 * scene clock, publish it for the VBlank task, and when it crosses a tile boundary blit the
 * tile column and/or row that just came into view.
 *
 * The edge offsets are read from 0x0205dc7c (+0 and +0xc): the six bytes between them belong to
 * a table of func_ov011_0205cda0 that mwcc laid out inside this one, so both are externs here.
 * Levers: both positions as ternaries (the X if/else scheduled the join differently), the row
 * flag in its own block (otherwise it and nY swap r7/sl), and the declaration order below. */
typedef signed char    s8;
typedef short          s16;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Pane {
    void *pBuffer;
    u8    pad_00004[0x1091a - 4];
    u16   wScrollPhase;
    s16   nStartX;
    s16   nStartY;
    s16   nEndX;
    s16   nEndY;
    s16   nDrawnX;
    s16   nDrawnY;
    u8    pad_10928[0x1092c - 0x10928];
    u16   wStartTime;
    u16   wEndTime;
    u8    pad_10930[0x10934 - 0x10930];
    s16   nScrollX;
    s16   nScrollY;
    u8    pad_10938[0x10940 - 0x10938];
} Ov011Pane;

typedef struct Ov011Scene {
    int       nA;
    int       nMode;
    u8        pad_00008[4];
    u32       nArchiveBase;
    u8        pad_00010[4];
    Ov011Pane aPane[2];
} Ov011Scene;

typedef struct Ov011Globals {
    u32         nClock;
    Ov011Scene *pScene;
} Ov011Globals;

/* Tile offset of the column/row to blit, indexed by scroll direction (0: towards negative,
 * 1: still, 2: towards positive). */
typedef struct Ov011EdgeOffsets {
    s8 aColumn[3];
    s8 aRow[3];
} Ov011EdgeOffsets;

typedef struct Ov011EdgeTable {
    Ov011EdgeOffsets x;
    u8               pad_06[6];
    Ov011EdgeOffsets y;
} Ov011EdgeTable;

extern Ov011Globals data_ov011_0205e960;
extern const Ov011EdgeTable data_ov011_0205dc7c;

extern int  func_0202060c(int nNum, int nDen);
extern void func_ov011_0205b8f8(int nPane, int nSrcX, int nSrcY, int nDstCol, int nDstRow);
extern void func_ov011_0205b814(int nPane, int nSrcX, int nSrcY, int nDstCol, int nDstRow);

void func_ov011_0205bb58(int nPane)
{
    Ov011Pane *pPane = &data_ov011_0205e960.pScene->aPane[nPane];
    int nToY;
    int nSpan;
    u16 nDuration;
    u16 nElapsed;
    Ov011EdgeOffsets xOff;
    Ov011EdgeOffsets yOff;
    int nFromX;
    int nToX;
    int nFromY;
    s16 nX;
    s16 nY;
    u8 bColumn;
    s16 nDirX;
    s16 nDirY;

    nSpan = pPane->wEndTime - pPane->wStartTime;
    nDuration = nSpan;
    if (data_ov011_0205e960.nClock < pPane->wEndTime) {
        nSpan = data_ov011_0205e960.nClock - pPane->wStartTime;
    }
    nElapsed = nSpan;
    xOff = data_ov011_0205dc7c.x;
    yOff = data_ov011_0205dc7c.y;

    nToX = pPane->nEndX;
    nFromX = pPane->nStartX;
    nDirX = nFromX < nToX ? 2 : (nFromX > nToX ? 0 : 1);
    nToY = pPane->nEndY;
    nFromY = pPane->nStartY;
    nDirY = nFromY < nToY ? 2 : (nFromY > nToY ? 0 : 1);

    nX = nDirX == 2 ? nFromX + func_0202060c(nElapsed * (nToX - nFromX), nDuration)
                    : nFromX - func_0202060c(nElapsed * (nFromX - nToX), nDuration);
    nY = nDirY == 2 ? nFromY + func_0202060c(nElapsed * (nToY - nFromY), nDuration)
                    : nFromY - func_0202060c(nElapsed * (nFromY - nToY), nDuration);
    pPane->nScrollX = nX;
    pPane->nScrollY = nY;

    bColumn = (pPane->nDrawnX >> 3) != (nX >> 3);
    {
        u8 bRow = (pPane->nDrawnY >> 3) != (nY >> 3);

        if (bColumn || bRow) {
            s16 nTileX = nX >> 3;
            s16 nTileY = nY >> 3;

            if (bColumn) {
                int nRow = yOff.aColumn[nDirY] + nTileY;
                int nCol = xOff.aColumn[nDirX] + nTileX;

                func_ov011_0205b8f8(nPane, nCol, nRow, nCol, nRow);
            }
            if (bRow) {
                int nRow = yOff.aRow[nDirY] + nTileY;
                int nCol = xOff.aRow[nDirX] + nTileX;

                func_ov011_0205b814(nPane, nCol, nRow, nCol, nRow);
            }
        }
    }
    pPane->nDrawnX = nX;
    pPane->nDrawnY = nY;
}
