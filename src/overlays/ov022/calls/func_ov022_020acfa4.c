/* Ov022_ResolveTargetPick -- turn a stored pick back into the thing it names.
 *
 * A pick says what kind of thing it points at and how to find it again. Kind 1
 * walks the owner's node list for the named node, checks the node is neither
 * retired nor closed, and counts down its own list to the numbered item; kind 2
 * asks the world for the entity in a slot and keeps it only while it still has a
 * body; kind 3 takes the entry by id and keeps it only while it is still
 * standing.
 *
 * A pick that resolves to nothing is wiped, so nobody reads a stale pointer.
 */

typedef unsigned char u8;

struct ActorSub {
    u8 pad00[4];
    void *pTable;                    /* 0x04: node table walked by func_ov107_020c2b50 */
};

struct Node {
    u8 pad000[0x60];
    unsigned short nOpen : 8;        /* 0x060 bits 0 to 7 */
    unsigned short nSpare60 : 8;
    u8 pad062[0x14a];
    unsigned short nFlags1ac;        /* 0x1ac */
    u8 pad1ae[0x7e];
    u8 list[4];                      /* 0x22c */
};

struct Entry {
    u8 pad00[0x12];
    unsigned short nHp;              /* 0x12 */
};

struct Target {                      /* Ov022Actor, pick view */
    u8 pad000[0x4ec];
    struct ActorSub *pSub;           /* 0x4ec */
    u8 nKind;                        /* 0x4f0 */
    u8 nId;                          /* 0x4f1 */
    u8 nIndex;                       /* 0x4f2 */
    u8 pad4f3[5];
    void *pEntity;                   /* 0x4f8 */
    struct Node *pNode;              /* 0x4fc */
    void *pItem;                     /* 0x500 */
    struct Entry *pEntry;            /* 0x504 */
};

extern struct Node *func_ov107_020c2b50(void *pList, int nId);
extern void *func_01fffd70(u8 *pList);
extern void *func_01fffd8c(u8 *pList);
extern void *func_ov002_0207679c(int nSlot, int nId);
extern int func_ov002_02076d24(void *pEntity);
extern struct Entry *func_01fffde0(int nId);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);

#define PICK_NODE_ITEM 1
#define PICK_ENTITY 2
#define PICK_ENTRY 3

#define NODE_RETIRED 2
#define NODE_OPEN 1
#define PICK_SIZE 0x18

void func_ov022_020acfa4(struct Target *pTarget)
{
    int bFound;
    unsigned int nIndex;
    struct Node *pNode;
    void *pItem;
    void *pList;

    bFound = 0;
    switch (pTarget->nKind) {
    case PICK_NODE_ITEM:
        nIndex = 0;
        pList = pTarget->pSub->pTable;
        if (pList == 0) {
            break;
        }
        {
            struct Node *pFound;

            pFound = func_ov107_020c2b50(pList, pTarget->nId);
            if (pFound == 0) {
                break;
            }
            pNode = pTarget->pNode = pFound;
        }
        if ((pNode->nFlags1ac & NODE_RETIRED) != 0) {
            break;
        }
        if ((pNode->nOpen & NODE_OPEN) == 0) {
            break;
        }
        pItem = func_01fffd70(pNode->list);
        while (pItem != 0) {
            if (nIndex == pTarget->nIndex) {
                pTarget->pItem = pItem;
                bFound = 1;
                break;
            }
            nIndex++;
            pItem = func_01fffd8c(pNode->list);
        }
        break;
    case PICK_ENTITY:
        pTarget->pEntity = func_ov002_0207679c(pTarget->nIndex, pTarget->nId);
        if (pTarget->pEntity != 0) {
            if (func_ov002_02076d24(pTarget->pEntity) != 0) {
                bFound = 1;
            }
        }
        break;
    case PICK_ENTRY:
        pTarget->pEntry = func_01fffde0(pTarget->nId);
        if (pTarget->pEntry->nHp != 0) {
            bFound = 1;
        }
        break;
    }
    if (bFound == 0) {
        MI_CpuFill8(&pTarget->nKind, 0, PICK_SIZE);
        pTarget->nKind = 0;
    }
}
