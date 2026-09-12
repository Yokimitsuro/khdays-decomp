/* Ov022_LinkActionAnims -- build the action table's entry table from the
 * animation archive and link every group's animation links to it.
 *
 * The archive starts with a count and that many offsets; each offset names
 * a record. Every link of the two groups' three lists is collected once by
 * id into a local set. The entry table gets one 0x80-byte entry per unique
 * link, unpacked from the record whose first word carries the link's id (or
 * from nothing) and given its tag slot. Then every link is pointed at the
 * entry whose id it names. The record pointers go back.
 */

typedef unsigned char u8;
typedef unsigned int u32;

#define GROUP_COUNT 2
#define LIST_COUNT 3
#define LINK_MAX 64

/* Ov022AnimFile */
struct AnimFile {
    u32 nHeader;                 /* 0x00, low byte the record count */
    u32 aOffsets[1];             /* 0x04 */
};

/* Ov022AnimLink */
struct Link {
    int nId;                     /* 0x00 */
    int nField04;                /* 0x04 */
    int nField08;                /* 0x08 */
    int nField0c;                /* 0x0c */
    int nField10;                /* 0x10 */
    struct Entry *pEntry;        /* 0x14 */
};

/* Ov022ActionGroup */
struct Group {
    u8 pad0000[0x18];
    struct Link *apLists[LIST_COUNT];    /* 0x18 */
    int aCounts[LIST_COUNT];     /* 0x24 */
};

/* Ov022Ent / Ov022ChannelGrid */
struct Entry {
    short nId;                   /* 0x00 */
    u8 nMode;                    /* 0x02 */
    u8 nField03;                 /* 0x03 */
    u8 pad0004[0x34];
    void *pData;                 /* 0x38 */
    u8 pad003c[0x44];
};

/* Ov022ActionTable */
struct ActionTable {
    u8 pad0000[4];
    u8 nSlotBase;                /* 0x04 */
    u8 pad0005[0x23];
    struct Group aGroups[GROUP_COUNT];   /* 0x28 */
    struct Entry *pEntries;      /* 0x88 */
    int nEntryCount;             /* 0x8c */
};

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void func_ov022_020b0160(struct Entry *pEntry, int nSlotBase, int *pRecord);   /* Ov022_UnpackChannelGrid */
extern void *func_ov022_020b02a4(struct ActionTable *pTable, int nTag);        /* Ov022_FindOrClaimTagSlot */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov022_020aff84(struct ActionTable *pTable, struct AnimFile *pFile)
{
    struct Link aUnique[LINK_MAX];
    u32 *pCursor;
    int **apRecords;
    int nRecords;
    int nUnique;
    int nList;
    int nOuter;
    int nLink;
    int n;
    int bFound;
    int *pRecord;
    struct Group *pGroup;
    struct Link *pLink;
    struct Entry *pEntry;

    pCursor = (u32 *)pFile;
    nRecords = *pCursor++ & 0xff;
    apRecords = NNSi_FndAllocFromDefaultExpHeap(nRecords * sizeof(int *));
    for (nOuter = 0; nOuter < nRecords; nOuter++) {
        apRecords[nOuter] = (int *)((u8 *)pFile + *pCursor);
        pCursor++;
    }
    nUnique = 0;
    for (nOuter = 0; nOuter < GROUP_COUNT; nOuter++) {
        /* Reuse the cursor through a typed Group view; keep this index form. */
        pCursor = (u32 *)&pTable->aGroups[nOuter];
        for (nList = 0; nList < LIST_COUNT; nList++) {
            for (nLink = 0; nLink < ((struct Group *)pCursor)->aCounts[nList]; nLink++) {
                pLink = &((struct Group *)pCursor)->apLists[nList][nLink];
                bFound = 0;
                for (n = 0; n < nUnique; n++) {
                    /* MWCC ARM32: pointer-domain comparison preserves the target
                     * cmp operand order. IDs remain numeric; neither cast value
                     * is dereferenced. Use integer equality for a portable port. */
                    if ((void *)aUnique[n].nId == (void *)pLink->nId) {
                        bFound = 1;
                        break;
                    }
                }
                if (!bFound) {
                    aUnique[nUnique] = *pLink;
                    nUnique++;
                }
            }
        }
    }
    pTable->nEntryCount = nUnique;
    pTable->pEntries = NNSi_FndAllocFromDefaultExpHeap(nUnique * sizeof(struct Entry));
    for (nOuter = 0; nOuter < nUnique; nOuter++) {
        pEntry = &pTable->pEntries[nOuter];
        pRecord = 0;
        for (n = 0; n < nRecords; n++) {
            if (aUnique[nOuter].nId == *apRecords[n]) {
                pRecord = apRecords[n];
                break;
            }
        }
        func_ov022_020b0160(pEntry, pTable->nSlotBase, pRecord);
        pEntry->pData = func_ov022_020b02a4(pTable, pEntry->nField03);
    }
    for (nOuter = 0, pGroup = pTable->aGroups; nOuter < GROUP_COUNT; nOuter++) {
        for (nList = 0; nList < LIST_COUNT; nList++) {
            for (nLink = 0; nLink < pGroup->aCounts[nList]; nLink++) {
                pLink = &pGroup->apLists[nList][nLink];
                for (n = 0; n < pTable->nEntryCount; n++) {
                    pEntry = &pTable->pEntries[n];
                    if (pEntry->nId == pLink->nId) {
                        pLink->pEntry = pEntry;
                        break;
                    }
                }
            }
        }
        pGroup++;
    }
    NNSi_FndFreeFromDefaultHeap(apRecords);
}
