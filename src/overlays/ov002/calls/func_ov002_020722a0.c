/* One entry of the link session's node table. */
typedef struct Ov002LinkEntry {
    unsigned char aNode[0x108];         /* +0x000 */
    unsigned char bActive;              /* +0x108 */
    unsigned char aPad[3];              /* +0x109 */
} Ov002LinkEntry;

/* The single link session context this overlay renders from. */
typedef struct Ov002LinkCtx {
    unsigned char aHead[0x58];          /* +0x000 */
    void *apOwnedBlocks[8];             /* +0x058 */
    signed char nOwnedBlockCount;       /* +0x078 */
    unsigned char aTables[0x97];        /* +0x079 */
    signed char nEntryCount;            /* +0x110 */
    signed char nSeatSplit;             /* +0x111 */
    unsigned char aPad[2];              /* +0x112 */
    Ov002LinkEntry aEntries[32];        /* +0x114 */
} Ov002LinkCtx;

extern unsigned char data_0204be04;     /* which link seat this console drives */
extern unsigned char data_0204c240;     /* boot and session mode flags */
extern Ov002LinkCtx *data_ov002_0207fa10;

extern void func_0202aa9c(void *pNode);

/* Hand every node this console currently owns to the renderer.
 *
 * The entry table is partitioned between the two link seats at nSeatSplit, so
 * the seat index picks which half to walk: the first seat takes
 * [0, nSeatSplit) and the second takes [nSeatSplit, nEntryCount). Only entries
 * whose low active bit is set are drawn. When bit 2 of the mode flags is set
 * the context's owned-block list is drawn as well.
 */
void func_ov002_020722a0(void)
{
    Ov002LinkCtx *pCtx;
    int iEntry;
    Ov002LinkEntry *pEntry;
    int nEnd;
    int bFirstSeat;

    pCtx = data_ov002_0207fa10;
    bFirstSeat = (data_0204be04 == 0);
    iEntry = bFirstSeat ? 0 : pCtx->nSeatSplit;
    nEnd = bFirstSeat ? pCtx->nSeatSplit : pCtx->nEntryCount;

    if (iEntry < nEnd) {
        pEntry = &pCtx->aEntries[iEntry];
        do {
            if ((pEntry->bActive & 1) != 0) {
                func_0202aa9c(pEntry);
            }
            iEntry++;
            pEntry++;
        } while (iEntry < nEnd);
    }

    if ((data_0204c240 & 4) == 0) {
        return;
    }

    iEntry = 0;
    if (pCtx->nOwnedBlockCount <= 0) {
        return;
    }
    do {
        func_0202aa9c(pCtx->apOwnedBlocks[iEntry]);
        iEntry++;
    } while (iEntry < pCtx->nOwnedBlockCount);
}
