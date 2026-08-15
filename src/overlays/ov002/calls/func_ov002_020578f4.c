typedef unsigned short u16;

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOL;

typedef struct {
    short nOrigin;
    short nRowLimit;
    short nColour;
} Ov002RowStyle;

typedef struct {
    unsigned char pad0000[0x3c];
    int nVisibleRows;
    unsigned char pad0040[0x124];
    Ov002RowStyle *aRowStyles[5];
} Ov002GaugeLayoutContext;

extern Ov002GaugeLayoutContext *data_ov002_0207f618;
extern BOOL data_ov002_0207e988;

extern int func_ov002_020534e4(Ov002RowStyle *pStyle, u16 nRow, int nKind);
extern int func_ov002_02053510(int nHandle, Ov002RowStyle *pStyle);
extern int func_ov002_02053558(u16 nRow);
extern int func_ov002_02053578(int nHandle, short nOffset, short nColour);
extern void func_ov002_020535a4(int nHandle);

void func_ov002_020578f4(int nRow, BOOL bFilled, BOOL bLast)
{
    int nParity = nRow % 2;
    Ov002GaugeLayoutContext *pContext = data_ov002_0207f618;
    int nHandle;
    int nHalfRow;
    u16 nEncodedRow;

    if (nParity == 1) {
        if (data_ov002_0207e988 != 3) {
            if (data_ov002_0207e988 == 4) {
                data_ov002_0207e988 = 2;
            }
        } else {
            data_ov002_0207e988 = bFilled ? FALSE : TRUE;
        }
    } else {
        data_ov002_0207e988 = bFilled != 0 ? 3 : 4;
    }

    if (bLast == 0 && nParity != 1) {
        return;
    }

    nHalfRow = nRow / 2;
    nEncodedRow = (u16)(nHalfRow + 50000);
    if (pContext->nVisibleRows > 0 &&
        nHalfRow <= pContext->nVisibleRows / 2) {
        nHandle = func_ov002_02053558(nEncodedRow);
        func_ov002_02053510(nHandle,
                            pContext->aRowStyles[data_ov002_0207e988]);
    } else {
        short nLimit = pContext->aRowStyles[0]->nRowLimit;
        nHandle = func_ov002_020534e4(
            pContext->aRowStyles[data_ov002_0207e988], nEncodedRow, 0xb);
        func_ov002_02053578(nHandle, (short)(nLimit - nHalfRow),
                            pContext->aRowStyles[0]->nColour);
    }
    func_ov002_020535a4(nHandle);
    data_ov002_0207e988 = -1;
}
