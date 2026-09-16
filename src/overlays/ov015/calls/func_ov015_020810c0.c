/* func_ov015_020810c0 -- Ov015_SpotInstallTable: hand table nTable of the spot's class
 * (+0x58, 0x1c bytes each) to the spot's actor (+0x3c) as a heap block: header {spot, four
 * callback slots, entry count}, then one 0x24-byte record per entry {kind (low half), 64-bit
 * id bit (ids below 0x40 in the first mask, the rest in the second; runtime shift
 * 020203d0), position (the pickup's for kind 2, ov002 02076cc8, else the entry's +0x8) and
 * four link bytes relative to the table's first id (-1 kept)}; a link entry (kind 1) ORs
 * the masks of the tables reachable from its link table (+0x14) into its id bit
 * (02081030).  The actor's install handler (+0x38) fills the callback slots, which are
 * copied into the spot (+0x44..+0x50) before the block is freed; the actor then gets
 * status nStatus (ov107 020c5c14) and, when the class's current link table (+0x178) is
 * this spot's kind, the first callback (+0x44) runs on the actor, the spot is armed
 * (bit 0 of +0x40) and, without a player (+0x180 == -1), also live (bit 1). */
typedef signed char        s8;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    s8  aLink[4];             /* 0x03 */
    u8  pad_07;
    union {
        void *pPickup;        /* 0x08: pickup piece (kind 2) */
        VecFx32 position;     /* 0x08: point position */
    } u;
    s8  nLinkTable;           /* 0x14 */
    s8  nLinkId;              /* 0x15 */
    u8  pad_16[2];
} Ov015SpotEntry;

typedef struct Ov015SpotTable {
    s8  nCount;               /* 0x00 */
    u8  pad_01[3];
    Ov015SpotEntry *aEntry;   /* 0x04 */
    u64 nMaskA;               /* 0x08 */
    u64 nMaskB;               /* 0x10 */
    s8  aLink[4];             /* 0x18 */
} Ov015SpotTable;

typedef struct Ov015SpotDef {
    u8  pad_000[0x58];
    Ov015SpotTable aTable[9]; /* 0x58 */
    u8  pad_154[0x178 - 0x154];
    s8  nLinkTable;           /* 0x178 */
    s8  nCurrent;             /* 0x179 */
} Ov015SpotDef;

typedef struct Ov015SpotRecord {
    u32 nKind : 16;           /* 0x00 */
    u32 nHigh : 16;
    u64 nMaskA;               /* 0x04 */
    u64 nMaskB;               /* 0x0c */
    VecFx32 position;         /* 0x14 */
    s8  aLink[4];             /* 0x20 */
} Ov015SpotRecord;            /* 0x24 */

typedef struct Ov015SpotActor Ov015SpotActor;

typedef struct Ov015SpotCallbacks {
    void (*pfnInstalled)(Ov015SpotActor *pActor); /* 0x00 */
    void *apCallback[3];      /* 0x04 */
} Ov015SpotCallbacks;

typedef struct Ov015SpotBlock {
    void *pSpot;              /* 0x00 */
    Ov015SpotCallbacks callbacks; /* 0x04 */
    int  nCount;              /* 0x14 */
    Ov015SpotRecord aRecord[1]; /* 0x18 */
} Ov015SpotBlock;

struct Ov015SpotActor {
    u8  pad_00[0x38];
    void (*pfnInstall)(Ov015SpotActor *pActor, u32 nSize, Ov015SpotBlock *pBlock); /* 0x38 */
};

typedef struct Ov015Spot {
    u8  pad_00[8];
    Ov015SpotDef *pDef;       /* 0x08 */
    u8  pad_0c[4];
    u8  nKind;                /* 0x10 */
    u8  pad_11[0x3c - 0x11];
    Ov015SpotActor *pActor;   /* 0x3c */
    u8  nSpotFlags;           /* 0x40: bit 0 armed, bit 1 live */
    u8  pad_41[3];
    Ov015SpotCallbacks callbacks; /* 0x44 */
} Ov015Spot;

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern VecFx32 *func_ov002_02076cc8(void *pPiece);                        /* piece position */
extern u64   func_020203d0(u64 nValue, int nShift);                       /* 64-bit shift left */
extern void  func_ov015_02081030(Ov015Spot *pSpot, int nRoot, u32 nTable, int nDepth, u16 *pVisited, u64 *pMask); /* Ov015_SpotDefCollectLinkedMasks */
extern void  func_ov107_020c5c14(void *pActor, u8 nStatus);

void func_ov015_020810c0(Ov015Spot *pSpot, int nArg1, int nTable, u32 nStatus)
{
    u16 nVisited;
    Ov015SpotDef *pDef;
    int i;
    Ov015SpotBlock *pBlock;
    u32 nSize;
    Ov015SpotTable *pTable;
    Ov015SpotRecord *pRecord;
    s8  nFirstId;
    int j;
    s8  nLink;

    pDef = pSpot->pDef;
    pTable = &pDef->aTable[nTable];
    nSize = pDef->aTable[nTable].nCount * sizeof(Ov015SpotRecord) + 0x18;
    nFirstId = -1;
    pBlock = NNSi_FndAllocFromDefaultExpHeap(nSize);
    pBlock->pSpot = pSpot;
    pBlock->nCount = pDef->aTable[nTable].nCount;
    pRecord = pBlock->aRecord;   /* indexed below: the record cursor must be the induction temp created after the entry offset */
    if (pDef->aTable[nTable].nCount > 0) {
        nFirstId = pTable->aEntry->nId;
    }
    for (i = 0; i < pTable->nCount; i++) {
        pRecord[i].nKind = pTable->aEntry[i].nKind;
        if (pTable->aEntry[i].nKind == 2) {
            pRecord[i].position = *func_ov002_02076cc8(pTable->aEntry[i].u.pPickup);
        } else {
            pRecord[i].position = pTable->aEntry[i].u.position;
        }
        if (pTable->aEntry[i].nId < 0x40) {
            pRecord[i].nMaskA = func_020203d0(1, pTable->aEntry[i].nId);
            pRecord[i].nMaskB = 0;
        } else {
            pRecord[i].nMaskA = 0;
            pRecord[i].nMaskB = func_020203d0(1, pTable->aEntry[i].nId - 0x40);
        }
        if (pTable->aEntry[i].nKind == 1) {
            nVisited = 1 << nTable;
            func_ov015_02081030(pSpot, nTable, pTable->aEntry[i].nLinkTable, 0, &nVisited, &pRecord[i].nMaskA);
        }
        for (j = 0; j < 4; j++) {
            nLink = pTable->aEntry[i].aLink[j];
            if (nLink >= 0) {
                pRecord[i].aLink[j] = nLink - nFirstId;
            } else {
                pRecord[i].aLink[j] = -1;
            }
        }
    }
    if (pSpot->pActor->pfnInstall != 0) {
        pSpot->pActor->pfnInstall(pSpot->pActor, nSize, pBlock);
    }
    pSpot->callbacks = pBlock->callbacks;
    NNSi_FndFreeFromDefaultHeap(pBlock);
    func_ov107_020c5c14(pSpot->pActor, nStatus);
    if (pDef->nLinkTable == pSpot->nKind) {
        pSpot->callbacks.pfnInstalled(pSpot->pActor);
        pSpot->nSpotFlags |= 1;
        if (pDef->nCurrent == -1) {
            pSpot->nSpotFlags |= 2;
        }
    }
}
