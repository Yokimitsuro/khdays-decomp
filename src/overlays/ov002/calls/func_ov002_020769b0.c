/* Build an entry pool: one zeroed block holding the caller's header followed by
 * `count` entries, each rounded up to a multiple of four bytes. The descriptor
 * records the rounded stride at +0x4e, the count at +0x50 and the base of the
 * entry area at +0x54 -- the fields Ov002_ClaimPoolEntry and
 * Ov002_GetElementKindAndIndex read back. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int value, void *dest,
                                        unsigned int size);

typedef struct {
    char pad0000[0x4e];
    unsigned short wStride;     /* +0x4e */
    unsigned short wCount;      /* +0x50 */
    char pad0052[2];
    char *pBase;                /* +0x54 */
} Ov002PoolDesc;

void *func_ov002_020769b0(int headerSize, int entrySize, int count) {
    int stride = ((entrySize + 3) / 4) * 4;
    int bytes = stride * count;
    Ov002PoolDesc *pool;

    pool = (Ov002PoolDesc *)NNSi_FndAllocFromDefaultExpHeap(headerSize + bytes);
    INITi_CpuClear32_0x01ff86fc(0, pool, headerSize + bytes);

    pool->wStride = (unsigned short)stride;
    pool->wCount = (unsigned short)count;
    pool->pBase = (char *)pool + headerSize;

    return pool;
}
