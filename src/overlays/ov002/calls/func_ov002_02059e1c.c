/* Per-frame tick over the entry pool. Nothing runs while the panel field is
 * busy. Each entry is dispatched on its kind; the next link is taken before the
 * body runs, so an entry may release itself.
 *
 * Kinds 1 and 2 arm a sampler: the first time the input gate opens they latch
 * the sampler's reading into both the current and previous slots and stamp the
 * tick, and they disarm again once the gate closes.
 */
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
} Ov002EntryPos;

typedef struct {
    u8 pad0000[4];
    int nKind;                          /* +0x04 */
    u8 pad0008[0x2c];
    long long qwSample;                 /* +0x34 */
    long long qwLatched;                /* +0x3c */
    unsigned long long qwSampledAt;     /* +0x44 */
    long long (*pfnSample)(void);       /* +0x4c */
    int bSampling;                      /* +0x50 */
} Ov002PoolEntry;

typedef struct {
    u8 pad0000[0x10];
    u8 listEntries[8];                  /* +0x10 */
} Ov002EntryPool;

extern Ov002EntryPool *data_ov002_0207f61c;

extern Ov002PoolEntry *NNS_FndGetNextListObject(void *pList,
                                                Ov002PoolEntry *pPrev);
extern int func_ov002_0205724c(void);
extern int func_ov002_0206f578(void);
extern int func_ov002_0206f59c(void);
extern void func_ov002_02059cb0(Ov002PoolEntry *pEntry, int nFlag);
extern void func_ov002_020598d8(Ov002PoolEntry *pEntry);
extern void func_ov002_02059d48(Ov002PoolEntry *pEntry);
extern unsigned long long func_020031d4(void);

int func_ov002_02059e1c(void) {
    Ov002EntryPool *pPool = data_ov002_0207f61c;
    Ov002PoolEntry *pEntry;
    Ov002PoolEntry *pNext;

    pEntry = NNS_FndGetNextListObject(pPool->listEntries, 0);

    if (func_ov002_0205724c() == 0) {
        while (pEntry != 0) {
            pNext = NNS_FndGetNextListObject(pPool->listEntries, pEntry);

            switch (pEntry->nKind) {
            case 1:
            case 2:
                if (pEntry->bSampling == 0 &&
                    func_ov002_0206f578() != 0 &&
                    func_ov002_0206f59c() == 0) {
                    pEntry->bSampling = 1;
                    pEntry->qwSample = pEntry->pfnSample();
                    pEntry->qwLatched = pEntry->qwSample;
                    pEntry->qwSampledAt = func_020031d4();
                }
                func_ov002_02059cb0(pEntry, 1);
                if (pEntry->bSampling != 0 && func_ov002_0206f59c() != 0) {
                    pEntry->bSampling = 0;
                }
                break;

            case 3:
                if (pEntry->bSampling != 0) {
                    func_ov002_020598d8(pEntry);
                }
                break;

            case 0:
                func_ov002_02059d48(pEntry);
                break;
            }

            pEntry = pNext;
        }
    }
    return 0;
}
