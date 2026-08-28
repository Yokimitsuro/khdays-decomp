typedef signed char s8;

/* One entry of the context's big table: 0x10c bytes with a live flag near the
 * end.  Only the flag and the stride are established here. */
typedef struct Ov002LinkEntry {
    char pad0000[0x108];
    s8 bActive;                     /* 0x108 */
    char pad0109[3];
} Ov002LinkEntry;

typedef struct Ov002LinkCtx {
    char pad0000[0x34];
    void *apNodes[8];               /* 0x34 */
    s8 nNodeCount;                  /* 0x54 */
    char pad0055[3];
    void *apOwnedBlocks[8];         /* 0x58 */
    s8 nOwnedBlockCount;            /* 0x78 */
    char pad0079[0x97];
    s8 nEntryCount;                 /* 0x110 */
    s8 field0111;                   /* 0x111 */
    char pad0112[2];
    Ov002LinkEntry aEntries[32];    /* 0x114 */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

extern void func_0202a7dc(void *pOwner);
extern void func_0202bedc(void *pNode, int nValue);
extern void func_0202bc30(void *pNode);
extern void func_0202ba18(void *pNode);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

/* Empties the link context's three collections and puts their counts back to
 * zero: the table entries in place, then the nodes and the records, which are
 * heap blocks and are freed.
 *
 * A node is taken apart in four steps -- its flag cleared, its resources let
 * go, its render item released, and only then the block itself freed.  Each
 * count is re-read every turn of its loop, since the calls in the body can
 * reach the context.
 *
 * The blocks at +0x58 go through the same release routine as the entries the
 * context carries inline, so they are very likely the same kind of object held
 * on the heap instead; nothing here proves it, and their name says only what
 * this function does with them.  The byte at +0x111 is zeroed alongside the
 * entry count and is left unnamed for the same reason.
 */
void func_ov002_0207209c(void)
{
    Ov002LinkCtx *pCtx;
    Ov002LinkEntry *pEntry;
    int i;

    i = 0;
    pCtx = data_ov002_0207fa10;
    if (pCtx->nEntryCount > 0) {
        pEntry = pCtx->aEntries;
        do {
            func_0202a7dc(pEntry);
            pEntry->bActive = 0;
            pEntry++;
            i++;
        } while (i < pCtx->nEntryCount);
    }

    i = 0;
    pCtx->nEntryCount = 0;
    pCtx->field0111 = 0;
    if (pCtx->nNodeCount > 0) {
        do {
            func_0202bedc(pCtx->apNodes[i], 0);
            func_0202bc30(pCtx->apNodes[i]);
            func_0202ba18(pCtx->apNodes[i]);
            NNSi_FndFreeFromDefaultHeap(pCtx->apNodes[i]);
            pCtx->apNodes[i] = 0;
            i++;
        } while (i < pCtx->nNodeCount);
    }

    i = 0;
    pCtx->nNodeCount = 0;
    if (pCtx->nOwnedBlockCount > 0) {
        do {
            func_0202a7dc(pCtx->apOwnedBlocks[i]);
            NNSi_FndFreeFromDefaultHeap(pCtx->apOwnedBlocks[i]);
            pCtx->apOwnedBlocks[i] = 0;
            i++;
        } while (i < pCtx->nOwnedBlockCount);
    }
    pCtx->nOwnedBlockCount = 0;
}
