#pragma thumb on

/* Ov022_BuildNodeGraph -- lay out the three node pools of a graph and wire them.
 *
 * Each pool gets one allocation, sized by its count, and keeps that count. The
 * first entry point is the head of the first pool, and the next four are the
 * nodes the caller's index table names inside it.
 *
 * Then every pool is filled from its own table: each node takes the table's
 * value, starts with both of its links and both of their alternates empty, and
 * is wired by the two indices the table entry carries. An index inside the pool
 * points at that node; the marker index instead points at the graph's own entry
 * for that side, and picks up the matching pool as the alternate when there is
 * one.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Node {
    int nValue;                      /* 0x00 */
    struct Node *pLeft;              /* 0x04 */
    struct Node *pLeftAlt;           /* 0x08 */
    struct Node *pRight;             /* 0x0c */
    struct Node *pRightAlt;          /* 0x10 */
    int nField14;                    /* 0x14 */
};

struct NodeDesc {
    int nValue;                      /* 0x00 */
    short nLeft;                     /* 0x04 */
    short nRight;                    /* 0x06 */
};

struct Graph {
    struct Node *aEntry[5];          /* 0x00 */
    int nKind;                       /* 0x14 */
    struct Node *aPool[3];           /* 0x18 */
    unsigned int aCount[3];          /* 0x24 */
};

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);

#define POOLS 3
#define ENTRIES 4
#define LINK_TO_ENTRY 0x80

void func_ov022_020afe88(struct Graph *pGraph, int nUnused, u16 *pCounts,
                         struct NodeDesc **pTables, short *pIndex, int nKind)
{
    struct Node *pNode;
    u16 *pCount;
    short *pIdx;
    struct Node **ppEntry;
    struct NodeDesc *pDesc;
    struct NodeDesc **pTable;
    struct Node **ppSlot;
    int nSlot;
    int nPool;
    int nNode;
    int nOffset;
    int nLink;

    nPool = 0;
    do {
        if (pCounts[nPool] != 0) {
            pGraph->aPool[nPool] = (struct Node *)
                NNSi_FndAllocFromDefaultExpHeap(pCounts[nPool] * sizeof(struct Node));
        }
        pGraph->aCount[nPool] = pCounts[nPool];
        nPool++;
    } while (nPool < POOLS);

    nSlot = 0;
    pGraph->aEntry[0] = pGraph->aPool[0];
    pIdx = pIndex;
    ppEntry = pGraph->aEntry;
    do {
        if (*pIdx >= 0) {
            ppEntry[1] = &pGraph->aPool[0][*pIdx];
        }
        nSlot++;
        pIdx++;
        ppEntry++;
    } while (nSlot < ENTRIES);
    pGraph->nKind = nKind;

    pCount = pCounts;
    pTable = pTables;
    ppSlot = pGraph->aEntry;
    for (nSlot = 0; nSlot < POOLS; nSlot++) {
        pDesc = *pTable;
        nNode = 0;
        if (nNode < *pCount) {
            nOffset = 0;
            do {
                /* ppSlot walks the graph's own word array, so [6] is the
                 * pool for this pass -- the ROM keeps one base register for it */
                pNode = (struct Node *)((u8 *)ppSlot[6] + nOffset);
                pNode->nValue = pDesc->nValue;
                pNode->pLeft = 0;
                pNode->pRight = 0;
                pNode->pLeftAlt = 0;
                pNode->pRightAlt = 0;
                pNode->nField14 = 0;
                nLink = pDesc->nLeft;
                if (nLink >= 0) {
                    if (nLink != LINK_TO_ENTRY) {
                        pNode->pLeft = &ppSlot[6][nLink];
                    } else {
                        pNode->pLeft = pGraph->aEntry[1];
                        if (pGraph->aPool[1] != 0) {
                            pNode->pLeftAlt = pGraph->aPool[1];
                        }
                    }
                }
                nLink = pDesc->nRight;
                if (nLink >= 0) {
                    if (nLink != LINK_TO_ENTRY) {
                        pNode->pRight = &ppSlot[6][nLink];
                    } else {
                        pNode->pRight = pGraph->aEntry[3];
                        if (pGraph->aPool[2] != 0) {
                            pNode->pRightAlt = pGraph->aPool[2];
                        }
                    }
                }
                nNode++;
                pDesc++;
                nOffset += sizeof(struct Node);
            } while (nNode < *pCount);
        }
        pTable++;
        pCount++;
        ppSlot++;
    }
}
