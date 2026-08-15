typedef struct {
    unsigned char pad0000[0x44];
    int nUnitCost;
    unsigned char pad0048[0xa4];
    unsigned short wTotalUnits;
} Ov002GaugeCountContext;

extern Ov002GaugeCountContext *data_ov002_0207f618;
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_020578f4(int nRow, int bFilled, int bLast);

void func_ov002_02057ad0(int nFilledUnits)
{
    Ov002GaugeCountContext *pContext = data_ov002_0207f618;
    long long nQuotient = func_02020400(pContext->wTotalUnits * 0x2e,
                                       pContext->nUnitCost * 0xfa);
    int nTotalRows;
    int nFilledRows;
    int nRow;

    if ((int)nQuotient <= 0) {
        nTotalRows = 0;
    } else {
        nTotalRows = ((int)nQuotient - 1) / 0x2e;
    }
    if (nFilledUnits <= 0) {
        nFilledRows = 0;
    } else {
        nFilledRows = (nFilledUnits - 1) / 0x2e;
    }
    if (nTotalRows <= 0) {
        return;
    }

    for (nRow = 0; nRow < nTotalRows - 1; nRow++) {
        func_ov002_020578f4(nRow, nRow < nFilledRows, 0);
    }
    func_ov002_020578f4(nTotalRows - 1,
                        nTotalRows - 1 < nFilledRows, 1);
}
