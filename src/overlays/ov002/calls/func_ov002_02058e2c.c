typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef void (*Ov002CellFn)(int nHandle, int nCell, int nMode);

typedef struct Ov002PanelRecord {
    u16 wCount;
    u16 wDrawn;
    u16 wTarget;
    u16 wSpan;
    u8 gap0008[8];
    unsigned long long uStamp;
    int bActive;
} Ov002PanelRecord;

typedef struct Ov002SceneContext {
    u8 gap0000[0x20];
    int nGaugeHandle;
    u8 gap0024[4];
    u8 bStateFlags;
    u8 gap0029[0x1b];
    int nUnitCost;
    u8 gap0048[0xa6];
    u16 wCurrentUnits;
    u8 gap00f0[0x3c];
    Ov002PanelRecord aPanelRecords[2];
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f618;

extern unsigned long long func_02020400(u32 nNumerator, u32 nDenominator);
extern void func_ov002_02057888(int nHandle, int nCell, int nMode);
extern void func_ov002_02057d74(Ov002PanelRecord *pDst,
                                Ov002PanelRecord *pSrc, u32 nValue,
                                Ov002CellFn pDraw, int nHandle,
                                int bNotify, int nSetup);

void func_ov002_02058e2c(u32 nUnits)
{
    Ov002SceneContext *pContext = data_ov002_0207f618;
    u32 nRemainder = (u16)(func_02020400(nUnits,
                                        pContext->nUnitCost * 0xfa) >> 32);
    u32 nValue;

    if (pContext->wCurrentUnits == nUnits) {
        return;
    }
    if (nRemainder == 0 && nUnits != 0) {
        nRemainder = (u16)(pContext->nUnitCost * 0xfa);
    }
    nValue = (u16)func_02020400(nUnits * 0x2e,
                                pContext->nUnitCost * 0xfa);
    if (nValue == 0 && nRemainder != 0) {
        nValue = 1;
    }
    pContext->wCurrentUnits = (u16)nUnits;
    func_ov002_02057d74(&pContext->aPanelRecords[1],
                        &pContext->aPanelRecords[0], nValue,
                        func_ov002_02057888, pContext->nGaugeHandle, 0, 1);
    pContext->bStateFlags |= 2;
}
