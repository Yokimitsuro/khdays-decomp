/* Build a pool entry from a descriptor and link it into the pool's list.
 *
 * A counter descriptor (kind 0) first tries to fold itself into an existing free
 * entry; if that works the function returns early. Otherwise a fresh 0x60-byte
 * entry is allocated, its tile buffer sized from the width, and the kind decides
 * what else is set up: counters latch a value, an owner and a one-second
 * deadline, kind 4 only latches the value, and the timer kinds seed the sampler
 * and clear the sampling state.
 *
 * The early return hands back whatever the counter bump returned, which is its
 * 0/1 flag rather than an entry pointer. That is what the ROM does.
 */
typedef unsigned char u8;

typedef struct {
    u8 bKey;                            /* +0x00 */
    u8 bWidth;                          /* +0x01 */
    u8 pad0002[2];
    int nKind;                          /* +0x04 */
    int nTarget;                        /* +0x08 */
    u8 bPalette;                        /* +0x0c */
    u8 bColour;                         /* +0x0d */
    u8 pad000e[2];
    int nValue;                         /* +0x10 */
    int nValueHi;                       /* +0x14 */
    int nOwner;                         /* +0x18 */
    u8 pad001c[4];
    long long (*pfnSample)(void);       /* +0x20 */
    int nExtra;                         /* +0x24 */
} Ov002EntryDesc;

typedef struct {
    u8 bKey;                            /* +0x00 */
    u8 bWidth;                          /* +0x01 */
    u8 pad0002[2];
    int nKind;                          /* +0x04 */
    int nTarget;                        /* +0x08 */
    int nSize;                          /* +0x0c */
    void *pBufferA;                     /* +0x10 */
    u8 pad0014[8];
    int nInitial;                       /* +0x1c */
    int nRequest;                       /* +0x20 */
    long long qwLimit;                  /* +0x24 */
    long long qwAccum;                  /* +0x2c */
    long long qwSample;                 /* +0x34 */
    long long qwLatched;                /* +0x3c */
    long long qwSampledAt;              /* +0x44 */
    long long (*pfnSample)(void);       /* +0x4c */
    int bSampling;                      /* +0x50 */
} Ov002PoolEntry;

typedef struct {
    u8 pad0000[0x10];
    u8 listEntries[8];                  /* +0x10 */
} Ov002EntryPool;

extern Ov002EntryPool *data_ov002_0207f61c;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void MI_CpuFill8(void *pDest, int nValue, unsigned int nSize);
extern void NNS_FndAppendListObject(void *pList, Ov002PoolEntry *pObject);
extern unsigned long long func_020031d4(void);
extern void *func_ov002_02059c04(void);
extern void *func_ov002_02059c4c(void *pEntry, int nDelta, int nOwner);
extern int func_ov002_02053558(int nId);
extern void func_ov002_02053578(int nEntry, short nField, unsigned short nColour);
extern void func_ov002_020535a4(int nEntry);
extern void func_ov002_0205a248(Ov002PoolEntry *pEntry, int nValue);
extern void func_ov002_020598d8(Ov002PoolEntry *pEntry);
extern void func_ov002_02059848(Ov002PoolEntry *pEntry, int nPalette, int nColour,
                                int nExtra);

void *func_ov002_02059f3c(Ov002EntryDesc *pDesc) {
    Ov002EntryPool *pPool = data_ov002_0207f61c;
    Ov002PoolEntry *pEntry;
    int nKey = pDesc->bKey;
    int nRequest;
    int nBufSize;

    if (pDesc->nKind == 0) {
        void *pFree = func_ov002_02059c04();

        if (pFree != 0) {
            void *pBumped = func_ov002_02059c4c(pFree, pDesc->nValue,
                                                pDesc->nOwner);

            if (pBumped != 0) {
                return pBumped;
            }
            nKey = 0xff;
        } else {
            nKey = 0xff;
        }
    }

    pEntry = (Ov002PoolEntry *)NNSi_FndAllocFromDefaultExpHeap(0x60);
    MI_CpuFill8(pEntry, 0, 0x60);

    nBufSize = pDesc->bWidth << 5;
    pEntry->bKey = (u8)nKey;
    pEntry->nKind = pDesc->nKind;
    pEntry->bWidth = pDesc->bWidth;
    pEntry->nTarget = pDesc->nTarget << 5;
    pEntry->nSize = nBufSize;
    pEntry->pBufferA = NNSi_FndAllocFromDefaultExpHeap(nBufSize);

    switch (pEntry->nKind) {
    case 0:
        pEntry->nInitial = pDesc->nValue;
        nRequest = func_ov002_02053558(0x47);
        func_ov002_02053578(nRequest, *(short *)(nRequest + 2), pDesc->bColour);
        func_ov002_020535a4(nRequest);
        pEntry->nRequest = nRequest;
        pEntry->qwLimit = func_020031d4() + 523656;
        *(int *)&pEntry->qwAccum = pDesc->nValue;
        *((int *)&pEntry->qwAccum + 1) = pDesc->nOwner;
        func_ov002_0205a248(pEntry, pDesc->nValue);
        func_ov002_02059848(pEntry, pDesc->bPalette, pDesc->bColour,
                            pDesc->nExtra);
        break;

    case 4:
        nRequest = func_ov002_02053558(0x47);
        func_ov002_02053578(nRequest, *(short *)(nRequest + 2), pDesc->bColour);
        func_ov002_020535a4(nRequest);
        pEntry->nRequest = nRequest;
        *(int *)&pEntry->qwAccum = pDesc->nValue;
        func_ov002_0205a248(pEntry, pDesc->nValue);
        func_ov002_02059848(pEntry, pDesc->bPalette, pDesc->bColour,
                            pDesc->nExtra);
        break;

    default:
        pEntry->nInitial = pDesc->nValue;
        nRequest = func_ov002_02053558(0x46);
        func_ov002_02053578(nRequest, *(short *)(nRequest + 2), pDesc->bColour);
        func_ov002_020535a4(nRequest);
        pEntry->nRequest = nRequest;

        if (pDesc->nKind == 3) {
            pEntry->qwLimit = pDesc->pfnSample();
            pEntry->bSampling = 1;
            pEntry->pfnSample = pDesc->pfnSample;
        } else {
            pEntry->qwLimit = *(long long *)&pDesc->nValue;
            pEntry->qwAccum = pDesc->pfnSample();
            pEntry->bSampling = 0;
            pEntry->qwLatched = 0;
            pEntry->qwSample = 0;
            pEntry->qwSampledAt = 0;
            pEntry->pfnSample = pDesc->pfnSample;
        }

        func_ov002_020598d8(pEntry);
        func_ov002_02059848(pEntry, pDesc->bPalette, pDesc->bColour,
                            pDesc->nExtra);
        break;
    }

    NNS_FndAppendListObject(pPool->listEntries, pEntry);
    return pEntry;
}
