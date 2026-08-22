/*
 * Ov002_FillSurfaceRows - repaint the surface's rows outward from its centre.
 *
 * Clears the row buffer, then walks outward from the centre line filling both
 * sides at once: the inner rows get the base tile plus five, the outermost pair
 * plus eight, and one closing row plus two. When the span is odd and the source
 * is tall enough, that closing row sits one past the far edge instead of on it.
 * Every tile carries the surface's mode nibble in its top four bits.
 *
 * ARM. The tile word is rebuilt at each call rather than hoisted, which is what
 * the ROM does - it reloads the mode byte and the base for all five sites.
 *
 * Byte-exact lever, and it is the whole function: the mode nibble is placed by
 * casting the shifted byte to unsigned short, NOT by masking it. Both spellings
 * emit the same lsl #28 with the lsr #16 folded into the orr, but the cast is
 * what makes mwcc order the pack the ROM's way - the shift emitted before the
 * base's addition, with the or writing back into the shifted operand's
 * register. Written as (base + k) | (mode << 28 >> 16) the addition comes out
 * first; written as (mode << 28 >> 16) | (base + k) the two temporaries swap
 * registers. Only the halfword cast gives both at once, and the mode half must
 * still be written first.
 */

extern void MIi_CpuClearFast(unsigned int nValue, void *pDst,
                             unsigned int nSize);
extern void func_ov002_0205249c(unsigned char *pCtx, int nRow, int nCount,
                                unsigned short nTile);

void func_ov002_020524ec(unsigned char *pCtx)
{
    int nCount;
    int i;
    int nCentre;
    int nLast;

    MIi_CpuClearFast(0, *(void **)(pCtx + 0x28), 0x600);
    if (*(int *)(pCtx + 4) == 0) {
        return;
    }

    nCount = *(int *)(pCtx + 4);
    nCentre = *(int *)(pCtx + 0x1c) + *(int *)(pCtx + 0x24) / 2;
    nLast = nCount - 1;

    for (i = 0; i < nLast; i++) {
        func_ov002_0205249c(pCtx, nCentre + i, *(int *)(pCtx + 0x20),
                            (unsigned short)((unsigned short)
                            ((unsigned int)*(unsigned char *)(pCtx + 0xc) << 12)
                            | (*(int *)(pCtx + 0x14) + 5)));
        func_ov002_0205249c(pCtx, nCentre - i, *(int *)(pCtx + 0x20),
                            (unsigned short)((unsigned short)
                            ((unsigned int)*(unsigned char *)(pCtx + 0xc) << 12)
                            | (*(int *)(pCtx + 0x14) + 5)));
    }

    func_ov002_0205249c(pCtx, nCentre + nLast, *(int *)(pCtx + 0x20),
                        (unsigned short)((unsigned short)
                        ((unsigned int)*(unsigned char *)(pCtx + 0xc) << 12)
                        | (*(int *)(pCtx + 0x14) + 8)));

    if (*(int *)(pCtx + 4) >= (*(int *)(pCtx + 0x24) + 1) / 2
        && *(int *)(pCtx + 0x24) % 2 == 1) {
        func_ov002_0205249c(pCtx, (nCentre - nLast) + 1, *(int *)(pCtx + 0x20),
                            (unsigned short)((unsigned short)
                            ((unsigned int)*(unsigned char *)(pCtx + 0xc) << 12)
                            | (*(int *)(pCtx + 0x14) + 2)));
        return;
    }
    func_ov002_0205249c(pCtx, nCentre - nLast, *(int *)(pCtx + 0x20),
                        (unsigned short)((unsigned short)
                        ((unsigned int)*(unsigned char *)(pCtx + 0xc) << 12)
                        | (*(int *)(pCtx + 0x14) + 2)));
}
