/*
 * Ov002_StepGaugePair - advance one frame of the gauge tween pair and say
 * whether anything is still moving.
 *
 * The two records are the growing side and the draining side of the same
 * gauge. Each holds a step in ticks and the tick it last stepped at, so the
 * number of steps this frame is the elapsed time divided by the step - a frame
 * that arrives late applies several steps at once rather than drifting.
 *
 * The growing side adds its steps, moves its stamp on by exactly the time it
 * consumed, and stops when it reaches the target. The draining side subtracts
 * instead and stops the same way; before that it also closes itself out when
 * the growing side has caught up with it, and on setup 0 that is what tells the
 * cell it is empty.
 *
 * Whether the row map has to be rebuilt is decided by comparing which row the
 * count sat on before and after, so a move inside one row costs nothing. The
 * rebuild carries a column and a row count: on the growing side the column is
 * the whole row unless the count has passed the last full row, and on the
 * draining side it is the row after the target's, or none when the count is
 * already inside the target's row.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 wCount;                         /* +0x00 */
    u16 wDrawn;                         /* +0x02 */
    u16 wTarget;                        /* +0x04 */
    u16 wSpan;                          /* +0x06 */
    long long qStepTicks;               /* +0x08 */
    long long qStampTicks;              /* +0x10 */
    int bActive;                        /* +0x18 */
} Ov002PanelRecord;                     /* 0x1c */

typedef struct {
    int nField0000;
    int nRowWidth;                      /* +0x04 */
    u8 pad0008[0x14];
} Ov002GaugeSetup;                      /* 0x1c */

typedef struct {
    u8 pad0000[0x44];
    int nUnitCost;                      /* +0x44 */
    u8 pad0048[0xa4];
    u16 wTotalUnits;                    /* +0xec */
} Ov002GaugeCountContext;

extern Ov002GaugeCountContext *data_ov002_0207f618;
extern Ov002GaugeSetup data_ov002_0207e98c[];

extern long long func_020031d4(void);
extern long long func_02020368(long long qValue, long long qDivisor);
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_02057260(int nIndex, int nMode);
extern void func_ov002_02057a20(int nColumn, int nRows);
extern void func_ov002_02057ad0(int nFilledUnits);
extern void func_ov002_020593b4(int nIndex, int nShown);

int func_ov002_02057f60(Ov002PanelRecord *pDst, Ov002PanelRecord *pSrc,
                        int nSetup)
{
    Ov002GaugeCountContext *pContext;
    Ov002GaugeSetup *pSetup;
    long long nNow;
    long long nQuotient;
    int nSteps;
    int bRebuild;
    int nRowWidth;
    int nWas;
    int nCount;
    int nTotal;
    int nRows;
    int nColumn;
    int bRowChanged;
    int bMoved;
    int nSpare;
    int nEnd;
    int nLimit;
    int bChangedB;
    int nCountB;
    int nWidthB;

    pContext = data_ov002_0207f618;
    nNow = func_020031d4();
    pSetup = &data_ov002_0207e98c[nSetup];
    bMoved = 0;
    bRebuild = 0;

    if (pDst->bActive != 0) {
        nSteps = (int)func_02020368(nNow - pDst->qStampTicks, pDst->qStepTicks);
        nRowWidth = pSetup->nRowWidth;
        nWas = pDst->wDrawn;
        bRowChanged = (int)func_02020400(nWas - 1, nRowWidth) + 1
                      != (int)func_02020400(nWas + nSteps - 1, nRowWidth) + 1;
        pDst->wDrawn = (u16)(pDst->wDrawn + nSteps);
        pDst->qStampTicks += (long long)nSteps * pDst->qStepTicks;
        if (pDst->wDrawn >= pDst->wTarget) {
            pDst->wDrawn = pDst->wTarget;
            pDst->bActive = 0;
        }
        if (nSetup == 1 && pSrc->bActive == 0 && bRowChanged) {
            nTotal = (int)func_02020400(pContext->wTotalUnits * 0x2e,
                                        pContext->nUnitCost * 0xfa);
            nRows = nTotal / 0x2e;
            nColumn = 0x2e;
            if ((int)pDst->wDrawn > nRows * 0x2e) {
                nColumn = nTotal - nRows * 0x2e;
            }
            func_ov002_02057ad0(pDst->wDrawn + 1);
            nSpare = 0;
            bRebuild = 1;
        }
        pDst->qStampTicks = nNow;
        bMoved = 1;
    }

    if (pSrc->bActive != 0) {
        if (pDst->wDrawn >= pSrc->wDrawn + pSrc->wSpan
            || (pDst->wDrawn >= pSrc->wDrawn && pSrc->wSpan == 0)) {
            pSrc->wSpan = 0;
            pSrc->bActive = 0;
            if (nSetup == 0) {
                if (pSrc->wDrawn == 0) {
                    func_ov002_020593b4(0, 0);
                    func_ov002_02057260(0, 2);
                } else {
                    func_ov002_02057260(0, 0);
                }
            }
        }
        if (pSrc->wDrawn == pSrc->wTarget && pSrc->wSpan != 0) {
            pSrc->wSpan = (u16)(pSrc->wSpan - 1);
        }

        nSteps = (int)func_02020368(nNow - pSrc->qStampTicks, pSrc->qStepTicks);
        nWas = pSrc->wDrawn;
        nLimit = pSrc->wTarget;
        if (nWas - nSteps > nLimit) {
            pSrc->wDrawn = (u16)(nWas - nSteps);
            pSrc->qStampTicks += (long long)nSteps * pSrc->qStepTicks;
        } else {
            pSrc->wDrawn = (u16)nLimit;
        }

        nWidthB = pSetup->nRowWidth;
        nCountB = pSrc->wDrawn;
        bChangedB = 0;
        if ((int)func_02020400(nWas - 1, nWidthB) + 1
            != (int)func_02020400(nCountB - 1, nWidthB) + 1) {
            bChangedB = 1;
        }
        if (nSetup == 1 && bChangedB && nCountB != 0) {
            nRows = pSrc->wTarget;
            nTotal = nWidthB
                     * (int)func_02020400(nRows != 0 ? nRows - 1 : 0, nWidthB);
            nEnd = nTotal + nWidthB;
            if (nTotal <= nCountB && nCountB < nEnd) {
                nSpare = (int)(func_02020400(nRows - 1, nWidthB) >> 32) + 1;
            } else {
                nSpare = 0;
            }
            func_ov002_02057ad0(nCountB);
            nColumn = 0x2e;
            bRebuild = 1;
        }
        bMoved = 1;
    }

    if (bRebuild) {
        func_ov002_02057a20(nColumn, nSpare);
    }
    return bMoved;
}
