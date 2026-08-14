/* Advance one armed entry. Re-reads the sampler: while the reading is unchanged
 * the accumulator collects the elapsed ticks, and the moment it changes both the
 * accumulator and the stored reading are reset to the new value. The stamp is
 * always refreshed. Passing a non-zero flag also repaints the entry.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x2c];
    long long qwAccum;                  /* +0x2c */
    long long qwSample;                 /* +0x34 */
    u8 pad003c[8];
    unsigned long long qwSampledAt;     /* +0x44 */
    long long (*pfnSample)(void);       /* +0x4c */
    int bSampling;                      /* +0x50 */
} Ov002PoolEntry;

extern unsigned long long func_020031d4(void);
extern void func_ov002_020598d8(Ov002PoolEntry *pEntry);

void func_ov002_02059cb0(Ov002PoolEntry *pEntry, int bRefresh) {
    long long qwNow = pEntry->pfnSample();
    unsigned long long qwTick = func_020031d4();

    if (pEntry->bSampling == 0) {
        return;
    }

    if (pEntry->qwSample == qwNow) {
        pEntry->qwAccum = pEntry->qwAccum + (qwTick - pEntry->qwSampledAt);
    } else {
        pEntry->qwAccum = qwNow;
        pEntry->qwSample = qwNow;
    }
    pEntry->qwSampledAt = qwTick;

    if (bRefresh == 0) {
        return;
    }
    func_ov002_020598d8(pEntry);
}
