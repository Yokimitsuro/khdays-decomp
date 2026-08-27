typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov002NodePair {
    u16 a;
    u16 b;
} Ov002NodePair;

typedef int (*Ov002NodeSampleFn)(int nValue, int nArg, int bReady);

typedef struct Ov002TaskNode {
    void *pHook0;
    void *pHook1;
    void *pHook2;
    int nThreshold;
    s8 nResult;             /* -2 not satisfied, -1 satisfied */
    s8 nLap;
    char pad012[2];
    s16 nKind;
    s16 nResolved;
    s16 nCount;
    char pad01a[2];
    Ov002NodePair *pPairs;
    s16 nArg;
    char pad022[2];
    Ov002NodeSampleFn pfnSample;
    u8 bMode;
} Ov002TaskNode;

extern int func_020235d0(int a, int b);         /* read one progress pair */
extern int func_ov002_0206f6e4(int bStart, int nLap);
extern void func_ov002_0206f04c(void);
extern void func_ov002_0207087c(void);
extern void func_ov002_02070a00(void);
extern void func_ov002_0206f0c8(void);

/* Writes a hook slot only when the caller hands over something other than -1,
   which is how a caller says "leave this one alone". */
static inline void Ov002_SetHooks(Ov002TaskNode *pNode, void *pA, void *pB,
                                  void *pC)
{
    if (pA != (void *)-1) {
        pNode->pHook0 = pA;
    }
    if (pB != (void *)-1) {
        pNode->pHook1 = pB;
    }
    if (pC != (void *)-1) {
        pNode->pHook2 = pC;
    }
}

/* Walks the node's pairs, feeding each reading to the node's own sampler, and
   leaves the verdict in nResult.  If the node ended up satisfied it then hands
   itself to the next pair of hooks: with a positive threshold it starts a lap
   first and reports -2 so the caller keeps waiting, otherwise it settles for
   good and reports the verdict. */
int func_ov002_02070890(Ov002TaskNode *pNode)
{
    int i;
    int nValue;

    pNode->nResult = (s8)((pNode->bMode == 0) ? -2 : -1);

    if (pNode->nKind != -1 && pNode->nResolved < 0) {
        return -2;
    }

    for (i = 0; i < pNode->nCount; i++) {
        nValue = (s16)func_020235d0(pNode->pPairs[i].a, pNode->pPairs[i].b);
        pNode->nResult = (s8)(pNode->pfnSample(nValue, pNode->nArg,
                                               (pNode->nResult != -2) ? 1 : 0)
                              ? -1 : -2);
    }

    if (pNode->nResult != -2) {
        if (pNode->nThreshold > 0) {
            pNode->nLap = (s8)func_ov002_0206f6e4(1, -1);
            if (pNode->nLap < 0) {
                return -2;
            }
            Ov002_SetHooks(pNode, (void *)func_ov002_0206f04c,
                           (void *)func_ov002_0207087c,
                           (void *)func_ov002_02070a00);
            return -2;
        }
        Ov002_SetHooks(pNode, (void *)func_ov002_0206f0c8,
                       (void *)func_ov002_0207087c,
                       (void *)func_ov002_02070a00);
    }
    return pNode->nResult;
}
