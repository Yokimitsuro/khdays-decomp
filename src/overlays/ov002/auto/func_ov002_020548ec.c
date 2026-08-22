/*
 * Ov002_StampTileMode - rewrite the mode nibble across a rectangle of tiles.
 *
 * Walks the request's rectangle in the source's tile map and replaces the top
 * four bits of every entry with the mode, leaving the tile index alone. The row
 * start is worked out from the source's own pixel width, eight pixels to the
 * tile, so the rectangle follows the source's stride rather than the screen's.
 *
 * Both extents are re-read from the request on every pass, which is what the
 * ROM does.
 *
 * ARM. The mode bits are worked out once into their own variable before the
 * loop, which is what puts the shift ahead of the empty-rectangle guard the way
 * the ROM has it; left inside the expression, mwcc hoists it only as far as the
 * loop. The halfword cast on the shift is the same lever as the surface row
 * fill - it emits the same instructions but orders the pack the ROM's way.
 */

void func_ov002_020548ec(int nUnused, unsigned char *pReq, int nMode)
{
    unsigned short *pHeader;
    unsigned short *pTile;
    unsigned short nModeBits;
    int i;
    int j;

    nModeBits = (unsigned short)((unsigned int)nMode << 12);
    for (i = 0; i < *(short *)(pReq + 0xc); i++) {
        pHeader = *(unsigned short **)(*(int *)(pReq + 0x18) + 8);
        pTile = (unsigned short *)((unsigned char *)pHeader + 0xc)
                + (*(unsigned short *)(pReq + 6)
                   + pHeader[0] * (*(unsigned short *)(pReq + 8) + i) / 8);
        for (j = 0; j < *(short *)(pReq + 0xa); j++) {
            *pTile = (unsigned short)(nModeBits | (*pTile & 0xfff));
            pTile++;
        }
    }
}
