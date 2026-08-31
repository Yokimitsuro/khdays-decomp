typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 wSortValue;
    u16 aCounters[3];
} Ov003RankRow;

typedef struct {
    u16 nPlayerCount;                   /* +0x00 */
    u8 pad0002[8];
    Ov003RankRow aRankRows[4];          /* +0x0a, stride 8 */
    u8 pad002a[2];
    int aRankGroups[4];                 /* +0x2c */
    int nFirstRankedPlayer;             /* +0x3c */
} Ov003SceneContext;

typedef struct {
    u16 nPlayer;
    u16 wSortValue;
} Ov003SortPair;

typedef struct {
    u8 pad0000[0x1974];
    u16 aRankCounters[3][4];             /* +0x1974 */
} Ov003GameState;

typedef struct {
    u8 pad0000[0x4d];
    u8 nLocalRankGroup;                  /* +0x4d */
} Ov003UiState;

extern Ov003SceneContext *data_ov003_0204f9a0;
extern Ov003GameState *data_0204be18;
extern Ov003UiState data_0204c300;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pMemory);
extern void func_0200fc00(void *pBase, int nCount, unsigned int nWidth,
                          int (*pCompare)(const void *, const void *), void *pWork);
extern unsigned int func_02030788(void);
extern int func_ov003_0204d73c(const void *pLeft, const void *pRight);

/* Authorized single-instruction exception; this source is not pure C. */
static inline unsigned int Clz(unsigned int nValue)
{
    asm { clz nValue, nValue }
    return nValue;
}

void func_ov003_0204d74c(void)
{
    int nGroup;
    void *pSortWork;
    unsigned int nPlayerCount;
    int nWorkSize;
    int i;
    Ov003SortPair aPairs[4];
    unsigned int nLocalPlayer;
    u16 *pCounter;

    nGroup = 0;
    nPlayerCount = data_ov003_0204f9a0->nPlayerCount;
    if ((int)(31 - Clz(nPlayerCount)) <= 0) {
        nWorkSize = 4;
    } else {
        nWorkSize = 31 - Clz(nPlayerCount);
        nWorkSize = nWorkSize + 1;
        nWorkSize = nWorkSize << 2;
        nWorkSize = nWorkSize << 1;
    }
    pSortWork = NNSi_FndAllocFromDefaultExpHeap(nWorkSize);

    for (i = 0; i < data_ov003_0204f9a0->nPlayerCount; i++) {
        aPairs[i].nPlayer = (u16)i;
        aPairs[i].wSortValue = data_ov003_0204f9a0->aRankRows[i].wSortValue;
    }

    func_0200fc00(aPairs, data_ov003_0204f9a0->nPlayerCount, sizeof(Ov003SortPair),
                  func_ov003_0204d73c, pSortWork);
    NNSi_FndFreeFromDefaultHeap(pSortWork);

    for (i = 0; i < data_ov003_0204f9a0->nPlayerCount; i++) {
        data_ov003_0204f9a0->aRankGroups[aPairs[i].nPlayer] = nGroup;
        if (nGroup == 0) {
            data_ov003_0204f9a0->nFirstRankedPlayer = aPairs[i].nPlayer;
        }
        if (i < data_ov003_0204f9a0->nPlayerCount - 1 &&
            aPairs[i].wSortValue > aPairs[i + 1].wSortValue) {
            nGroup++;
        }
    }

    if (nGroup > 0) {
        for (i = 0; i < data_ov003_0204f9a0->nPlayerCount; i++) {
            if (data_ov003_0204f9a0->aRankGroups[i] == nGroup) {
                data_ov003_0204f9a0->aRankGroups[i] = 3;
            }
        }
    }

    for (i = 0; i < data_ov003_0204f9a0->nPlayerCount; i++) {
        nGroup = data_ov003_0204f9a0->aRankGroups[i];
        if (nGroup < 3) {
            pCounter = &data_ov003_0204f9a0->aRankRows[i].aCounters[nGroup];
            (*pCounter)++;
            if (*pCounter > 999) {
                *pCounter = 999;
            }
        }
    }

    nLocalPlayer = func_02030788();
    nGroup = data_ov003_0204f9a0->aRankGroups[nLocalPlayer];
    pCounter = &data_0204be18->aRankCounters[data_ov003_0204f9a0->nPlayerCount - 2][nGroup];
    (*pCounter)++;
    if (*pCounter > 999) {
        *pCounter = 999;
    }
    data_0204c300.nLocalRankGroup = (u8)nGroup;
}
