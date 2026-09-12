/* func_ov008_0208a4b0 -- Ov008_SortParamRecordsByItemOrder: in-place quicksort of
 * an array of param-record pointers by their item definition's u16 sort key
 * (+0x90, ascending).  Middle-element pivot, Hoare partition, recursion on both
 * halves; written with bare while loops so the pivot key is re-read in the low
 * scan and CSE'd into the high scan, as in the ROM.
 */
typedef unsigned short u16;
typedef unsigned char  u8;

typedef struct Ov008ItemDef {
    u8  pad_00[0x90];
    u16 nSortKey;             /* 0x90 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8               pad_00[0xc];
    Ov008ItemDef *pItemDef; /* 0x0c */
} Ov008ParamRecord;

void func_ov008_0208a4b0(Ov008ParamRecord **apRecord, int nCount)
{
    Ov008ParamRecord *pPivot;
    Ov008ParamRecord *pLow;
    int nLow;
    int nHigh;

    if (nCount == 1) {
        return;
    }
    pPivot = apRecord[nCount >> 1];
    nLow = 0;
    nHigh = nCount - 1;
    for (;;) {
        while (apRecord[nLow]->pItemDef->nSortKey < pPivot->pItemDef->nSortKey) {
            nLow++;
        }
        while (apRecord[nHigh]->pItemDef->nSortKey > pPivot->pItemDef->nSortKey) {
            nHigh--;
        }
        if (nLow >= nHigh) {
            break;
        }
        pLow = apRecord[nLow];
        apRecord[nLow] = apRecord[nHigh];
        apRecord[nHigh] = pLow;
        nLow++;
        nHigh--;
    }
    func_ov008_0208a4b0(apRecord, nLow);
    func_ov008_0208a4b0(apRecord + nLow, nCount - nLow);
}
