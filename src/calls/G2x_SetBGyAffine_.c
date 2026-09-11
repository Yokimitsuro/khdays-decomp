typedef struct Mtx22 {
    int m[4];
} Mtx22;

/* Hardware BG affine register block: PA/PB packed into one 32-bit write,
 * PC/PD packed into another, then the 32-bit X/Y reference points. */
typedef struct GXAffineReg {
    unsigned int paPb;
    unsigned int pcPd;
    int x;
    int y;
} GXAffineReg;

void G2x_SetBGyAffine_(GXAffineReg *pReg, const Mtx22 *pMtx,
                        int nCentreX, int nCentreY, int nX, int nY)
{
    {
        short a16 = (short)(pMtx->m[0] >> 4);
        short b16 = (short)(pMtx->m[1] >> 4);
        pReg->paPb = (unsigned short)a16 | ((unsigned int)(unsigned short)b16 << 16);
    }
    {
        short c16 = (short)(pMtx->m[2] >> 4);
        short d16 = (short)(pMtx->m[3] >> 4);
        pReg->pcPd = (unsigned short)c16 | ((unsigned int)(unsigned short)d16 << 16);
    }

    {
        int dx = nX - nCentreX;
        int dy = nY - nCentreY;
        int y = pMtx->m[2] * dx + pMtx->m[3] * dy;
        int x = pMtx->m[0] * dx + pMtx->m[1] * dy;
        y += nCentreY << 12;
        x += nCentreX << 12;
        pReg->x = x >> 4;
        pReg->y = y >> 4;
    }
}
