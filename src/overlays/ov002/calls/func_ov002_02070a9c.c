/* Ov002_CreatePairCompareNode: instantiate a progress-pair comparison node. */
typedef unsigned short u16;
typedef struct Ov002NodePair { u16 a, b; } Ov002NodePair;
typedef int (*Ov002NodeSampleFn)(int nValue, int nArg, int bReady);
typedef struct Ov002TaskNode {
    void *pHook0, *pHook1, *pHook2;
    int nThreshold;
    signed char nResult, nLap;
    char pad012[2];
    short nKind, nResolved, nCount;
    char pad01a[2];
    Ov002NodePair *pPairs;
    short nArg;
    char pad022[2];
    Ov002NodeSampleFn pfnSample;
    unsigned char bMode;
} Ov002TaskNode;
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern int func_ov002_020707c8(int,int,int);
extern int func_ov002_02070728(int,int,int);
extern int func_ov002_020707e8(int,int,int);
extern int func_ov002_02070744(int,int,int);
extern int func_ov002_02070808(int,int,int);
extern int func_ov002_02070760(int,int,int);
extern int func_ov002_02070828(int,int,int);
extern int func_ov002_0207077c(int,int,int);
extern int func_ov002_02070848(int,int,int);
extern int func_ov002_02070798(int,int,int);
extern int func_ov002_02070868(int,int,int);
extern int func_ov002_020707b4(int,int,int);
extern int func_ov002_02070890(Ov002TaskNode *);
extern void func_ov002_0207087c(Ov002TaskNode *);
extern int func_ov002_02070a00(Ov002TaskNode *,int);

static inline void Ov002_SetHooks(Ov002TaskNode *pNode, void *pA, void *pB, void *pC)
{
    if (pA != (void *)-1) pNode->pHook0 = pA;
    if (pB != (void *)-1) pNode->pHook1 = pB;
    if (pC != (void *)-1) pNode->pHook2 = pC;
}

Ov002TaskNode *func_ov002_02070a9c(int nKind, int nMode, int nCount,
    const u16 *pValueKeys, const u16 *pValueWidths, unsigned char nCompareOp,
    short nArg, int nThreshold)
{
    Ov002TaskNode *pNode;
    int i;
    pNode = NNSi_FndAllocFromDefaultExpHeap(0x2c);
    pNode->pPairs = NNSi_FndAllocFromDefaultExpHeap(nCount * 4);
    pNode->nKind = nKind;
    pNode->nResolved = -1;
    pNode->nCount = nCount;
    pNode->nArg = nArg;
    pNode->bMode = nMode;
    pNode->nThreshold = nThreshold;
    switch (nCompareOp) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: break;
    case 7: pNode->pfnSample = nMode == 0 ? func_ov002_020707c8 : func_ov002_02070728; break;
    case 8: pNode->pfnSample = nMode == 0 ? func_ov002_020707e8 : func_ov002_02070744; break;
    case 9: pNode->pfnSample = nMode == 0 ? func_ov002_02070808 : func_ov002_02070760; break;
    case 10: pNode->pfnSample = nMode == 0 ? func_ov002_02070828 : func_ov002_0207077c; break;
    case 11: pNode->pfnSample = nMode == 0 ? func_ov002_02070848 : func_ov002_02070798; break;
    case 12: pNode->pfnSample = nMode == 0 ? func_ov002_02070868 : func_ov002_020707b4; break;
    }
    for (i = 0; i < nCount; i++) {
        pNode->pPairs[i].a = pValueKeys[i];
        pNode->pPairs[i].b = pValueWidths[i];
    }
    Ov002_SetHooks(pNode, (void *)func_ov002_02070890,
        (void *)func_ov002_0207087c, (void *)func_ov002_02070a00);
    return pNode;
}
