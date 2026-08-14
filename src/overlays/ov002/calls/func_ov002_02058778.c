typedef unsigned short u16;

typedef void (*Ov002CellFn)(int nTarget, int nCell, int bClearing);

/* The quotient is the low half of the helper's long long return; writing `/`
 * emits _s32_div_f, which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);

int func_ov002_02058778(int nTarget, int nValue, int nScale, u16 *pPair,
                        Ov002CellFn pDraw, int bRebuild) {
    /* The total has to be touched before the previous count is read: the
     * allocator walks these two in order of first use, and only that order puts
     * the total in the register the ROM uses. */
    u16 wTotal = pPair[0];
    int nDivisor = wTotal;
    u16 wPrevious = pPair[1];
    int nNew;
    int nOld;
    int bClearing;
    int i;

    nOld = (u16)func_02020400(wPrevious * nScale, nDivisor);
    nNew = (u16)func_02020400(nValue * nScale, nDivisor);

    if (wPrevious == 0) {
        if (nValue != 0 && nNew == 0) { nNew = 1; }
    } else if (nNew == 0) {
        if (nOld == 0) { nOld = 1; }
        if (nValue != 0) { nNew = 1; }
    }
    pPair[1] = (u16)nValue;

    if (bRebuild != 0) {
        if (nTarget != 0) {
            for (i = 0; i < nNew; i++) {
                pDraw(nTarget, i, 0);
            }
        }
    } else {
        if (nOld == nNew) { return 0; }
        if ((unsigned int)nNew > (unsigned int)nOld) {
            bClearing = 0;
        } else {
            nOld = nOld ^ nNew;
            nNew = nNew ^ nOld;
            nOld = nOld ^ nNew;
            bClearing = 1;
        }
        if (nTarget != 0) {
            for (; nOld < nNew; nOld++) {
                pDraw(nTarget, nOld, bClearing);
            }
        }
    }
    return 1;
}
