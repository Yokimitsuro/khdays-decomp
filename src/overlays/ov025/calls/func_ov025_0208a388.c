/* func_ov025_0208a388 -- Ov025_MergeSortedLists: the merge step of the NNS list merge sort
 * (Ov025_MergeSortList 0208a4bc).  While both sorted lists have a head, the one the compare
 * callback prefers (a true result takes the right head) is unlinked and appended to the
 * destination (NNS_FndRemoveListObject / NNS_FndAppendListObject); once a list is empty the
 * other one is spliced on whole: its head is linked after the destination's tail, the tail
 * and the count taken over.  The symbol table split the function's shared epilogue off as
 * 0208a4b8; the size is 0x134. */
typedef unsigned short u16;

typedef struct NNSFndList {
    void *head;               /* 0x00 */
    void *tail;               /* 0x04 */
    u16  count;               /* 0x08 */
    u16  linkOffset;          /* 0x0a */
} NNSFndList;

typedef struct NNSFndLink {
    void *prev;               /* 0x00 */
    void *next;               /* 0x04 */
} NNSFndLink;

typedef int (*NNSFndCompare)(void *pLeft, void *pRight);

extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void  NNS_FndRemoveListObject(NNSFndList *pList, void *pObject);
extern void  NNS_FndAppendListObject(NNSFndList *pList, void *pObject);

void func_ov025_0208a388(NNSFndList *pDest, NNSFndList *pLeftList, NNSFndList *pRightList, NNSFndCompare compare)
{
    void *pLeft;
    void *pRight;
    void *pFirst;

    for (;;) {
        pLeft = NNS_FndGetNextListObject(pLeftList, 0);
        pRight = NNS_FndGetNextListObject(pRightList, 0);
        if (pLeft == 0) {
            pFirst = NNS_FndGetNextListObject(pRightList, 0);
            if (pFirst == 0) {
                return;
            }
            ((NNSFndLink *)((char *)pDest->tail + pDest->linkOffset))->next = pFirst;
            ((NNSFndLink *)((char *)pFirst + pRightList->linkOffset))->prev = pDest->tail;
            pDest->tail = pRightList->tail;
            pDest->count += pRightList->count;
            return;
        }
        if (pRight == 0) {
            pFirst = NNS_FndGetNextListObject(pLeftList, 0);
            if (pFirst == 0) {
                return;
            }
            ((NNSFndLink *)((char *)pDest->tail + pDest->linkOffset))->next = pFirst;
            ((NNSFndLink *)((char *)pFirst + pLeftList->linkOffset))->prev = pDest->tail;
            pDest->tail = pLeftList->tail;
            pDest->count += pLeftList->count;
            return;
        }
        if (compare(pLeft, pRight)) {
            NNS_FndRemoveListObject(pRightList, pRight);
            NNS_FndAppendListObject(pDest, pRight);
        } else {
            NNS_FndRemoveListObject(pLeftList, pLeft);
            NNS_FndAppendListObject(pDest, pLeft);
        }
    }
}
