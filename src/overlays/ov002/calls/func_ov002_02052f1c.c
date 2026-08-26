/*
 * Ov002_BlitTileRegion - copy a rectangle of tiles from a source image into one
 * of the panel's tile maps, one row at a time.
 *
 * The request carries where to put the rectangle, where to take it from, and how
 * much of it to take; a copy extent of -1 means "all of the source in that
 * direction". A negative destination slides the rectangle off the top or left
 * edge, which is handled by moving the source origin the same amount and
 * shrinking the extent, and the far edges are clipped against the screen's
 * 32 by 24 tiles. Nothing is drawn when the clipping leaves no rows.
 *
 * Each row is fetched through the caller's row function, which reads the source
 * and hands back a run of map entries, and that run is written straight into the
 * destination map at the row's offset.
 *
 * The two destination coordinates are held narrow, as the request stores them.
 * That is not decoration: with a plain int destination row the compiler turns the
 * row offset into an induction variable and advances it by a row's worth of bytes
 * each pass, where the original recomputes it from the row and the column.
 *
 * Two details of the shape are load-bearing. The clipped destination is a variable
 * of its own, taken from the request in the guard's else arm rather than clipped in
 * place: that fourth assignment is what keeps the guard a real branch instead of a
 * predicated run, and it costs nothing, because the two coalesce afterwards. And
 * the destinations are held narrow, as the request stores them, which stops the row
 * offset from being turned into a stepping variable.
 *
 * The same clipping, written the same way, appears in the main-layer blit of
 * overlay 000.
 *
 * Four details of the shape are load-bearing, and none of them is decoration. The
 * clipped destination is a variable of its own, taken from the request in the
 * guard's else arm rather than clipped in place: that fourth assignment is what
 * keeps each guard a real branch instead of a predicated run, and it costs nothing
 * because the two coalesce afterwards. The destinations are held narrow, as the
 * request stores them, which stops the row offset from becoming a stepping
 * variable. The height's default is a conditional expression while the width's is
 * a statement. And the column's clamp is written out in full while the row's goes
 * through a temporary. The last two asymmetries are the original's: written the
 * other way round the code is the same instruction for instruction, and only the
 * registers move.
 *
 * The same clipping, written the same way, appears in the main-layer blit of
 * overlay 000.
 *
 * ARM.
 */

typedef struct {
    char pad00[8];
    unsigned short *pTile;
} Ov002TileSource;

typedef struct {
    char pad00[2];
    short nDstX;
    short nDstY;
    unsigned short nSrcX;
    unsigned short nSrcY;
    short nCopyW;
    short nCopyH;
    char pad0e[2];
    int nDest;
    char pad14[4];
    Ov002TileSource *pSource;
} Ov002BlitRequest;

typedef void *(*Ov002RowFn)(unsigned short *pTile, short nSrcX, short nSrcY,
                            unsigned short nWidth);

extern unsigned int func_ov002_02052db4(int nDest);
extern int func_ov002_02053c18(int nDest, int nOffset, void *pRow,
                               unsigned int nBytes);

void func_ov002_02052f1c(Ov002BlitRequest *pReq, Ov002RowFn pfnRow, int nFlag)
{
    unsigned short *pTile = pReq->pSource->pTile;
    int nWidth = (unsigned int)pTile[0] >> 3;
    int i;
    int nSrcY;
    int nCopyW;
    short nDstX;
    short nDstY;
    int nCopyH;
    int nOver;
    void *pRow;
    int nSrcX;

    nCopyW = pReq->nCopyW;
    if (nCopyW == -1) {
        nCopyW = nWidth;
    }
    nCopyH = pReq->nCopyH == -1 ? (unsigned int)pTile[1] >> 3 : pReq->nCopyH;
    nSrcX = pReq->nSrcX;
    nSrcY = pReq->nSrcY;
    if (pReq->nDstX < 0) {
        nSrcX -= pReq->nDstX;
        nCopyW += pReq->nDstX;
        nDstX = 0;
    } else {
        nDstX = pReq->nDstX;
    }
    if (nDstX + nCopyW > 32) {
        nCopyW -= nDstX + nCopyW - 32;
    }
    if (pReq->nDstY < 0) {
        nSrcY -= pReq->nDstY;
        nCopyH += pReq->nDstY;
        nDstY = 0;
    } else {
        nDstY = pReq->nDstY;
    }
    nOver = nDstY + nCopyH;
    if (nOver > 24) {
        nCopyH -= nOver - 24;
    }
    func_ov002_02052db4(pReq->nDest);
    for (i = 0; i < nCopyH; i++) {
        pRow = pfnRow(pReq->pSource->pTile + 6, (short)nSrcX,
                      (short)(nSrcY + i), (unsigned short)nWidth);
        func_ov002_02053c18(pReq->nDest, (nDstX + (nDstY + i) * 32) * 2, pRow,
                            nCopyW * 2);
    }
}
