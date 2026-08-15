typedef struct {
    unsigned char pad0000[0x3c];
    int nRequestValue;
    unsigned char pad0040[0x14c];
    int nPanelMode;
} Ov002PanelContext;

typedef struct {
    int fields[9];
} Ov002Request;

extern Ov002PanelContext *data_ov002_0207f614;

extern void func_ov002_0205f220(Ov002Request *pRequest, int nZero,
                                int nRequestKind,
                                Ov002PanelContext *pContext);
extern void func_ov002_020537bc(int nHandle, int nMode, int nDuration);

int func_ov002_02057300(Ov002Request *pRequest, int nValue)
{
    Ov002PanelContext *pContext = data_ov002_0207f614;

    if (pContext == 0) {
        goto fail;
    }
    if (pContext->nPanelMode == 0) {
        goto submit;
    }

fail:
    return 0;

submit:
    pContext->nPanelMode = 9;
    pContext->nRequestValue = nValue;
    pRequest->fields[7] = 2;
    pRequest->fields[8] = 0;
    func_ov002_0205f220(pRequest, 0, 9, pContext);
    func_ov002_020537bc(-1, 0, 300);
    return 1;
}
