/* ov022: start walking one of the action table's groups.
 *
 * Resets whatever walk was running, points the cursor pair at the group asked
 * for and marks which one it is in the flags. The walk runs forwards from the
 * group's head, except that a group with nothing to walk through, or one asked
 * for in reverse, starts from the second list and steps backwards instead.
 * Whichever entry it lands on has its count handed straight to the step call.
 */

typedef unsigned char u8;
typedef unsigned int u32;

#define GROUP_COUNT 2
#define FLAG_GROUP0 2
#define FLAG_GROUP1 4
#define FLAG_WALKING 0x10
#define FLAG_DONE 8

struct Group {
    struct Group *pHead;         /* 0x00 */
    u8 pad0004[0x10];
    int nCount;                  /* 0x14 */
    struct Group *apLists[3];    /* 0x18 */
    int aCounts[3];              /* 0x24 */
};

struct ActionTable {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[0x24];
    struct Group aGroups[GROUP_COUNT];   /* 0x0028 */
    u8 pad0088[0x3e0];
    struct Group *pGroup;        /* 0x0468 */
    struct Group **ppLists;      /* 0x046c */
    struct Group *pCurrent;      /* 0x0470 */
    int nStep;                   /* 0x0474 */
    u32 nField0478;              /* 0x0478 */
};

extern void func_ov022_020b09c4(struct ActionTable *pTable);   /* clear the node state */
extern void func_ov022_020b064c(int nCount);                   /* reset the channel grid */

void func_ov022_020b08f4(struct ActionTable *pTable, int bReverse, int nGroup)
{
    func_ov022_020b09c4(pTable);
    pTable->nStep = 1;
    pTable->pCurrent = 0;
    pTable->pGroup = &pTable->aGroups[nGroup];
    pTable->ppLists = pTable->aGroups[nGroup].apLists;
    pTable->nField0478 = 0;
    pTable->nFlags &= ~FLAG_DONE;
    if (nGroup == 0) {
        pTable->nFlags |= FLAG_GROUP0;
    } else if (nGroup == 1) {
        pTable->nFlags |= FLAG_GROUP1;
    }
    pTable->nFlags |= FLAG_WALKING;
    if (pTable->pGroup->nCount <= 1 || bReverse != 0) {
        pTable->pCurrent = pTable->ppLists[1];
        pTable->nStep = -1;
    } else {
        pTable->pCurrent = pTable->pGroup->pHead;
    }
    func_ov022_020b064c(pTable->pCurrent->nCount);
}
