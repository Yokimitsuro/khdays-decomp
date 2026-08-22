/*
 * Ov002_DrawFlatRect - stream one flat black rectangle through the GX FIFO.
 *
 * Sets the polygon attributes (full alpha, both faces), a black vertex colour
 * and a begin, then sends the four corners of the axis-aligned rectangle
 * (nX0,nY0)-(nX1,nY1) at a common depth, before the end command. Used for the
 * screen-covering fade quad.
 *
 * ARM. Each coordinate is packed as (unsigned short)(v << 22 >> 16): a signed
 * shift that keeps the low ten bits, scaled into the 16-bit vertex format. The
 * packing must stay INLINE at each corner - hoisting the five distinct values
 * into named locals gives the same 79 instructions but a different colouring,
 * and no statement or declaration order recovers it.
 */

extern void func_01ff9f00(unsigned int nCmd, const void *pSrc,
                          unsigned int nWords);   /* GX_SendFifoWords */

#define PACK(v) ((unsigned int)(unsigned short)((v) << 22 >> 16))

void func_ov002_02051528(int nX0, int nY0, int nX1, int nY1, int nZ)
{
    unsigned int nAttr;
    unsigned int nColour;
    unsigned int nBegin;
    unsigned int nVtxA[2];
    unsigned int nVtxB[2];
    unsigned int nVtxC[2];
    unsigned int nVtxD[2];

    nAttr = 0x1f00c0;
    func_01ff9f00(0x29, &nAttr, 1);
    nColour = 0;
    func_01ff9f00(0x20, &nColour, 1);
    nBegin = 1;
    func_01ff9f00(0x40, &nBegin, 1);

    nVtxA[0] = PACK(nX0) | PACK(nY0) << 16;
    nVtxA[1] = PACK(nZ);
    func_01ff9f00(0x23, nVtxA, 2);

    nVtxB[0] = PACK(nX1) | PACK(nY0) << 16;
    nVtxB[1] = PACK(nZ);
    func_01ff9f00(0x23, nVtxB, 2);

    nVtxC[0] = PACK(nX1) | PACK(nY1) << 16;
    nVtxC[1] = PACK(nZ);
    func_01ff9f00(0x23, nVtxC, 2);

    nVtxD[0] = PACK(nX0) | PACK(nY1) << 16;
    nVtxD[1] = PACK(nZ);
    func_01ff9f00(0x23, nVtxD, 2);

    func_01ff9f00(0x41, 0, 0);
}
