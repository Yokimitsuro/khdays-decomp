typedef struct Ov002CrawlBlock {
    char pad0000[0x1b];
    signed char aSlotIndex[5];      /* +0x1b, root +0x8caf */
    short aAmount[4];               /* +0x20, root +0x8cb4 */
    void *aPauseSlots[10];          /* +0x28, root +0x8cbc */
    signed char nLastPostedSlot;          /* +0x50, root +0x8ce4 */
} Ov002CrawlBlock;

typedef struct Ov002RootContext {
    char pad0000[0x8b58];
    int nPhase;                     /* +0x8b58 */
    char pad8b5c[0x8c94 - 0x8b5c];
    Ov002CrawlBlock crawl;          /* +0x8c94 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_ov002_020573cc(void);           /* something is still busy */
extern void func_ov002_0206aeb8(int nId, int nAmount, int nSlot, int nFlags);
extern void func_ov002_02056fa0(void);          /* request the crawl skip */

/* Post the score line for one entry of the crawl.
 *
 * A negative slot index means the entry has nothing to post: unless the phase
 * has already reached 7 the crawl is asked to skip and the last-posted slot is
 * cleared.  Otherwise the entry's amount is posted against the slot's object,
 * except that repeating the slot that was posted last time sends -1 instead.
 * Nothing is posted while the busy check is still true, and that is the only
 * path that answers 0.
 */
int func_ov002_0206ce00(int nIndex)
{
    Ov002RootContext *pRoot;
    Ov002CrawlBlock *pBlock;
    int nAmount;

    pRoot = data_ov002_0207fa00;
    pBlock = &pRoot->crawl;
    if (pBlock->aSlotIndex[nIndex] >= 0) {
        nAmount = pBlock->aAmount[nIndex];
        if (pBlock->nLastPostedSlot == pBlock->aSlotIndex[nIndex]) {
            nAmount = -1;
        }
        if (func_ov002_020573cc() != 0) {
            return 0;
        }
        func_ov002_0206aeb8((int)pBlock->aPauseSlots[pBlock->aSlotIndex[nIndex]],
                            nAmount, 1, 9);
        pBlock->nLastPostedSlot = pBlock->aSlotIndex[nIndex];
    } else {
        if (pRoot->nPhase != 7) {
            func_ov002_02056fa0();
            pBlock->nLastPostedSlot = -1;
        }
    }
    return 1;
}
