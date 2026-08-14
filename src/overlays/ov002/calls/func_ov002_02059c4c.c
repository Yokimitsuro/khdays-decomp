/* Add to a counter entry on behalf of its owner. A mismatched owner releases the
 * entry instead and reports that it is gone. On a match the running total grows,
 * the entry's deadline is pushed one second out, and the new total is redrawn.
 *
 * The 0x24 and 0x2c slots are shared with the stopwatch kinds, which read the
 * same bytes as one 64-bit accumulator; here they are a deadline and a pair of
 * 32-bit fields.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x24];
    unsigned long long qwDeadline;      /* +0x24 */
    int nValue;                         /* +0x2c */
    int nOwner;                         /* +0x30 */
} Ov002PoolEntry;

extern unsigned long long func_020031d4(void);
extern void func_ov002_0205a1d4(Ov002PoolEntry *pEntry, int bNotify);
extern void func_ov002_0205a248(Ov002PoolEntry *pEntry, int nValue);

int func_ov002_02059c4c(Ov002PoolEntry *pEntry, int nDelta, int nOwner) {
    int bAlive = 1;

    if (pEntry->nOwner != nOwner) {
        func_ov002_0205a1d4(pEntry, bAlive);
        bAlive = 0;
    } else {
        pEntry->nValue = pEntry->nValue + nDelta;
        pEntry->qwDeadline = func_020031d4() + 523656;
        func_ov002_0205a248(pEntry, pEntry->nValue);
    }
    return bAlive;
}
