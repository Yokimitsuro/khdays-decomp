/* Initialize the gauge scene and return its per-frame callback. The local
 * aggregate copy is load-bearing: it produces the original THUMB ldm/stm copy
 * and preserves the relocation to data_ov002_0207ddd0. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002GaugeSetup Ov002GaugeSetup;

typedef struct Ov002RowIds {
    int aIds[5];
} Ov002RowIds;

typedef struct Ov002PanelRecord {
    u16 wCount;
    u16 wDrawn;
    u16 wTarget;
    u16 wSpan;
    unsigned long long uStepTicks;
    unsigned long long uStartStamp;
    int bActive;
} Ov002PanelRecord;

typedef struct Ov002SceneContext {
    u8 gap0000[0x3c];
    int nQueued;
    int gap0040;
    int nUnitCost;
    u8 gap0048[0xac];
    Ov002PanelRecord aTweenRecords[2];
    Ov002PanelRecord aPanelRecords[2];
    int aGaugeRowStyles[5];
    u8 gap0178[0x10];
} Ov002SceneContext;

extern u8 data_0204c240;
extern Ov002SceneContext *data_ov002_0207f618;
extern const Ov002RowIds data_ov002_0207ddd0;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDest, int nValue, unsigned int nSize);
extern void func_ov002_020586bc(Ov002GaugeSetup *pSetup);
extern int func_ov002_02053558(int nId);
extern int func_ov002_02059010(void);

int (*func_ov002_02058f00(Ov002GaugeSetup *pSetup))(void)
{
    Ov002RowIds rowIds = data_ov002_0207ddd0;
    Ov002SceneContext *pContext;
    int i;

    pContext = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f618 = pContext;
    MI_CpuFill8(pContext, 0, sizeof(Ov002SceneContext));
    func_ov002_020586bc(pSetup);
    pContext->aTweenRecords[0].uStepTicks = 0x3d5d;
    pContext->aTweenRecords[1].uStepTicks = 0x28e9;
    pContext->aPanelRecords[0].uStepTicks = 0x3d5d;
    pContext->aPanelRecords[1].uStepTicks = 0x3d5d;
    pContext->nUnitCost = (data_0204c240 & 4) != 0 ? 3 : 1;
    if (pContext->nUnitCost < 1) {
        pContext->nUnitCost = 1;
    }
    pContext->nQueued = 0;
    for (i = 0; i < 5; i++) {
        pContext->aGaugeRowStyles[i] =
            func_ov002_02053558((u16)rowIds.aIds[i]);
    }
    return func_ov002_02059010;
}
