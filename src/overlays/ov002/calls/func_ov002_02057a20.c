typedef struct {
    unsigned char pad0000[0x20];
    void *pDisplayRows;
    void *pWorkRows;
} Ov002GaugeGridContext;

extern Ov002GaugeGridContext *data_ov002_0207f618;
extern const unsigned char data_ov002_0207dd7c;
extern const unsigned char data_ov002_0207dd9c;
extern const unsigned char data_ov002_0207dda2;
extern const unsigned char data_ov002_0207dd74;

extern void func_ov002_020578c4(void *pRows, int nRow, const void *pPattern);
extern void MIi_CpuCopyFast(const void *pSource, void *pDest, unsigned int nSize);

void func_ov002_02057a20(int nLeadingRows)
{
    Ov002GaugeGridContext *pContext = data_ov002_0207f618;
    int nRow = 0;
    int nNextRow;

    while (nRow < nLeadingRows) {
        func_ov002_020578c4(pContext->pWorkRows, nRow,
                            &data_ov002_0207dd7c);
        nRow++;
    }
    func_ov002_020578c4(pContext->pWorkRows, nRow,
                        &data_ov002_0207dd9c);
    nNextRow = nRow + 1;
    nRow += 2;
    func_ov002_020578c4(pContext->pWorkRows, nNextRow,
                        &data_ov002_0207dda2);
    while (nRow <= 47) {
        func_ov002_020578c4(pContext->pWorkRows, nRow,
                            &data_ov002_0207dd74);
        nRow++;
    }
    MIi_CpuCopyFast(pContext->pWorkRows, pContext->pDisplayRows, 0xc0);
}
