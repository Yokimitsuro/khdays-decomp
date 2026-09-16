/* NOT MATCHING -- 456 bytes, exact size, instruction count and relocations except the
 * 64-bit shift, which mwcc emits as `_ll_shl` (the ROM's func_020203d0: an alias line
 * `_ll_shl kind:label(arm) addr:0x020203d0` in config/arm9/symbols.txt resolves it).  The
 * residue is 6 bytes in the link-collect loop: the entry address sum and the two field
 * offset constants swap r1 / r2 (ROM: adds r2,r1,r7 / movs r1,#2; build 139: movs r2,#2 /
 * adds r1,r1,r7).  Initialising the inner counter before the entry load fixes the choice
 * but the scheduler then hoists that movs above the load, which the ROM keeps inside the
 * if.  ~260 cells swept (declaration orders, entry pointer / cached entries / pointer
 * arithmetic, nKind local, continue / while / switch forms, block-scoped or reused
 * counters, unsigned counters, prototypes).  Notes: build/held/func_ov015_02080df8.md. */
typedef signed char        s8;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    s8  aLink[4];             /* 0x03 */
    u8  pad_07[0x14 - 0x07];
    s8  nLinkTable;           /* 0x14 */
    s8  nLinkId;              /* 0x15 */
    u8  pad_16[2];
} Ov015SpotEntry;

typedef struct Ov015SpotTable {
    s8  nCount;               /* 0x00 */
    u8  pad_01[3];
    Ov015SpotEntry *aEntry;   /* 0x04 */
    u64 aMask[2];             /* 0x08: id bits 0..63 / 64..127 */
    s8  aLink[4];             /* 0x18: linked table ids, -1 = none */
} Ov015SpotTable;

typedef struct Ov015SpotDef {
    void *apHandler[0x13];    /* 0x000: class handler slots */
    u16  nKind;               /* 0x04c */
    u8   pad_04e[0x58 - 0x4e];
    Ov015SpotTable aTable[9]; /* 0x058 */
    u8   pad_154[0x178 - 0x154];
    s8   nLinkTable;          /* 0x178 */
    s8   nCurrent;            /* 0x179 */
    u8   pad_17a[2];
    Ov015SpotEntry *pCurrentEntry; /* 0x17c */
    s8   nPlayer;             /* 0x180 */
    u8   pad_181[3];
} Ov015SpotDef;

typedef struct Ov015SpotSpecRow {
    s8  nTable;               /* 0x00 */
    s8  nCount;               /* 0x01 */
    u8  pad_02[2];
    Ov015SpotEntry *aEntry;   /* 0x04 */
} Ov015SpotSpecRow;

typedef struct Ov015SpotSpec {
    s8  nRows;                /* 0x00 */
    u8  pad_01[3];
    Ov015SpotSpecRow aRow[1]; /* 0x04 */
} Ov015SpotSpec;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx); /* build a class table */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern u64   func_020203d0(u64 nValue, int nShift);                             /* 64-bit shift left */
extern int   func_ov002_0206b84c(void);                                         /* current mission */
extern void  func_ov015_020807cc(void);
extern void  func_ov015_02080684(void);
extern void  func_ov015_0208069c(void);
extern void  func_ov015_02080ad0(void);
extern void  func_ov015_0208075c(void);
extern void  func_ov015_02080794(void);
extern void  func_ov015_02080734(void);
extern void  func_ov015_0208073c(void);

Ov015SpotDef *func_ov015_02080df8(void *pCtx, Ov015SpotSpec *pSpec)
{
    int nId;
    int m;
    Ov015SpotDef *pDef;
    Ov015SpotSpecRow row;
    int bHigh;
    int k;
    Ov015SpotTable *pTable;
    int i;
    int nTable;
    int j;
    pDef = func_ov002_020769b0(sizeof(Ov015SpotDef), 0x58, pCtx);
    for (i = 0; i < pSpec->nRows; i++) {
        row = pSpec->aRow[i];
        nTable = row.nTable;
        pTable = &pDef->aTable[nTable];
        pTable->aLink[0] = -1;
        pTable->aLink[1] = -1;
        pTable->aLink[2] = -1;
        pTable->aLink[3] = -1;
        pTable->aMask[0] = 0;
        pTable->aMask[1] = 0;
        pTable->nCount = row.nCount;
        pTable->aEntry = NNSi_FndAllocFromDefaultExpHeap(row.nCount * sizeof(Ov015SpotEntry));
        MI_CpuCopy8(row.aEntry, pTable->aEntry, pTable->nCount * sizeof(Ov015SpotEntry));
        for (j = 0; j < pTable->nCount; j++) {
            bHigh = 0;
            nId = pTable->aEntry[j].nId;
            if (nId >= 0x40) {
                bHigh = 1;
                nId -= 0x40;
            }
            pTable->aMask[bHigh] |= 1ULL << nId;
        }
    }
    pTable = pDef->aTable;
    for (k = 0; k < 9; k++) {
        for (j = 0; j < pTable[k].nCount; j++) {
            if (pTable[k].aEntry[j].nKind == 1) {
                nId = pTable[k].aEntry[j].nLinkTable;
                for (m = 0; m < 4; m++) {
                    if (nId == pTable[k].aLink[m]) {
                        break;
                    }
                    if (pTable[k].aLink[m] == -1) {
                        pTable[k].aLink[m] = nId;
                        break;
                    }
                }
            }
        }
    }
    pDef->apHandler[0] = 0;
    pDef->apHandler[1] = (void *)func_ov015_020807cc;
    pDef->apHandler[2] = 0;
    pDef->apHandler[3] = (void *)func_ov015_02080684;
    pDef->apHandler[4] = 0;
    pDef->apHandler[5] = 0;
    pDef->apHandler[6] = (void *)func_ov015_0208069c;
    pDef->apHandler[7] = 0;
    pDef->apHandler[8] = (void *)func_ov015_02080ad0;
    pDef->apHandler[9] = (void *)func_ov015_0208075c;
    pDef->apHandler[10] = (void *)func_ov015_02080794;
    pDef->apHandler[11] = (void *)func_ov015_02080734;
    pDef->apHandler[12] = (void *)func_ov015_0208073c;
    pDef->apHandler[14] = 0;
    pDef->apHandler[16] = 0;
    pDef->apHandler[17] = 0;
    pDef->apHandler[15] = 0;
    pDef->nKind = 0xe;
    pDef->pCurrentEntry = 0;
    pDef->nPlayer = -1;
    pDef->nCurrent = -1;
    pDef->nLinkTable = 1;
    if (func_ov002_0206b84c() == 0x25a) {
        pDef->nLinkTable = 5;
    }
    return pDef;
}
