/* Claim entry `index` of the pool: only a free entry (flags 0 at +0x12) can be
 * claimed. A claimed entry is zeroed, marked live, back-pointed at the pool, and
 * stamped with its own slot number and an unset key. Reports the entry, or 0
 * when it was already in use.
 *
 * The pool's stride at +0x4e and base at +0x54 are the same descriptor fields
 * Ov002_GetElementKindAndIndex divides by.
 *
 * The slot number stamped at +0x11 is the POOL'S slot in the list table, not the
 * entry's -- the lookup is called with r0 still holding the pool, which is also
 * what was just stored at +8. */
extern int func_ov002_02076738(void *listEntry);

typedef struct {
    char pad0000[8];
    void *pPool;                /* +8 */
    char pad000c[5];
    unsigned char bSlot;        /* +0x11 */
    unsigned short wFlags;      /* +0x12 */
    unsigned short wKey;        /* +0x14 */
    unsigned char bKind;        /* +0x16 */
} Ov002Entry;

typedef struct {
    char pad0000[0x4e];
    unsigned short wStride;     /* +0x4e */
    char pad0050[4];
    char *pBase;                /* +0x54 */
} Ov002PoolDesc;

void *func_ov002_02076a38(Ov002PoolDesc *pool, int index) {
    Ov002Entry *entry = (Ov002Entry *)(pool->pBase + pool->wStride * index);

    if (entry->wFlags != 0) {
        return 0;
    }

    *(int *)entry = 0;
    *(int *)((char *)entry + 4) = 0;
    entry->wFlags = 1;
    entry->pPool = pool;

    entry->bSlot = (unsigned char)func_ov002_02076738(pool);
    entry->wKey = 0xffff;
    entry->bKind = 0;

    return entry;
}
