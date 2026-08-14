/* Repaint a stopwatch entry as MM:SS.cc, right-aligned in its buffer.
 *
 * The value shown depends on the kind: kind 3 asks the sampler directly, kind 1
 * counts up and clamps at the limit, and everything else counts down from the
 * limit to zero. It is converted from ticks to milliseconds, and kind 2 also
 * lowers the glyph row once under a minute.
 *
 * The two centisecond digits and their separator are dropped when the display
 * settings ask for the short form; the value is then rounded up to the next
 * whole second instead. The leading minutes digit is blanked rather than drawn
 * as a zero.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[1];
    u8 bWidth;                          /* +0x01 */
    u8 pad0002[2];
    int nKind;                          /* +0x04 */
    int nTarget;                        /* +0x08 */
    int nSize;                          /* +0x0c */
    void *pBufferA;                     /* +0x10 */
    u8 pad0014[0x10];
    unsigned long long qwLimit;         /* +0x24 */
    unsigned long long qwAccum;         /* +0x2c */
    u8 pad0034[0x18];
    long long (*pfnSample)(void);       /* +0x4c */
} Ov002PoolEntry;

typedef struct {
    u8 pad0000[0xc];
    int nQueue;                         /* +0x0c */
} Ov002EntryPool;

extern Ov002EntryPool *data_ov002_0207f61c;
extern u8 data_0204c240;

extern unsigned long long func_02020368(unsigned long long value,
                                        unsigned int divisor, int arg3);
extern void MI_CpuFill8(void *pDest, int nValue, unsigned int nSize);
extern void func_ov002_0205979c(Ov002PoolEntry *pEntry, int nColumn, char cGlyph,
                                int bLower, int nWords);
extern void GFXi_EnqueueCommand(int nQueue, int nTarget, void *pSrc, int nSize);

void func_ov002_020598d8(Ov002PoolEntry *pEntry) {
    Ov002EntryPool *pPool = data_ov002_0207f61c;
    unsigned long long qwValue;
    unsigned int v;
    unsigned int nCol;
    unsigned int nSep;
    int bLower = 0;

    if (pEntry->nKind == 3) {
        qwValue = pEntry->pfnSample();
    } else {
        unsigned long long qwLimit = pEntry->qwLimit;
        unsigned long long qwAccum = pEntry->qwAccum;

        if (qwAccum < qwLimit) {
            if (pEntry->nKind == 1) {
                qwValue = qwAccum;
            } else {
                qwValue = qwLimit - qwAccum;
            }
        } else {
            if (pEntry->nKind != 1) {
                qwLimit = 0;
            }
            qwValue = qwLimit;
        }
    }

    v = (unsigned int)func_02020368(qwValue << 6, 0x82ea, 0);

    if (pEntry->nKind == 2 && v < 60000) {
        bLower = 1;
    }

    v = v / 10;
    nCol = pEntry->bWidth - 1;
    MI_CpuFill8(pEntry->pBufferA, 0, pEntry->nSize);

    if ((data_0204c240 & 0xc) == 4 || (data_0204c240 & 8) != 0) {
        nCol -= 3;
        v = (v + 99) / 100;
    } else {
        func_ov002_0205979c(pEntry, nCol, v % 10, bLower, 1);
        v = v / 10;
        func_ov002_0205979c(pEntry, nCol - 1, v % 10, bLower, 1);
        v = v / 10;
        nSep = nCol - 2;
        nCol -= 3;
        func_ov002_0205979c(pEntry, nSep, 10, bLower, 1);
    }

    func_ov002_0205979c(pEntry, nCol, v % 10, bLower, 1);
    v = v / 10;
    func_ov002_0205979c(pEntry, nCol - 1, v % 6, bLower, 1);
    v = v / 6;
    func_ov002_0205979c(pEntry, nCol - 2, 10, bLower, 1);
    func_ov002_0205979c(pEntry, nCol - 3, v % 10, bLower, 1);

    if (v / 10 != 0) {
        func_ov002_0205979c(pEntry, nCol - 4, (v / 10) % 10, bLower, 1);
    } else {
        func_ov002_0205979c(pEntry, nCol - 4, -1, bLower, 1);
    }

    GFXi_EnqueueCommand(pPool->nQueue, pEntry->nTarget, pEntry->pBufferA,
                        pEntry->nSize);
}
