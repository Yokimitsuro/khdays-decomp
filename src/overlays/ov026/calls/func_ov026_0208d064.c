/* func_ov026_0208d064 -- Ov008_FillRewardRecord: build a kind-3 param record from
 * a raw reward db record (Ov008_LoadParamRecords fill callback for the db 0x18
 * and 0x17 lists).  Copies the index, whether the raw kind is not 0x18, the
 * level byte, the two flag fields and the price; a record without its own text refers to the item definition of the
 * shop record it names (1-based) and takes that record's text pointers, while
 * one with text allocates one buffer for both UTF-16 strings and copies them.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define RECORD_KIND_REWARD 3
#define RAW_KIND_ITEM      0x18

typedef struct Ov008ItemDef {
    u8    pad_00[0xc];
    void *pName;              /* 0x0c */
    void *pDescription;       /* 0x10 */
} Ov008ItemDef;

typedef struct Ov008RewardRecord {          /* 0x34, kind 3 (db 0x18 / 0x17 lists) */
    int   nKind;              /* 0x00 */
    u16   nIndex;             /* 0x04 */
    u16   bNotItem;           /* 0x06 */
    int   nPrice;             /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u16   nLevel;             /* 0x10 */
    u8    bFlag;              /* 0x12 */
    u8    nOwnText;           /* 0x13 */
    int   nShopIndex;         /* 0x14 */
    void *pName;              /* 0x18 */
    void *pDescription;       /* 0x1c */
    int   bEnabled;           /* 0x20 */
    u8    pad_24[0x34 - 0x24];
} Ov008RewardRecord;

typedef struct Ov008ParamRecord {           /* 0x34, kind 0 shop record (db 0x15) */
    u8    pad_00[0xc];
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8    pad_10[0x34 - 0x10];
} Ov008ParamRecord;

typedef struct Ov008RawRewardRecord {
    u8    pad_00[2];
    u16   nRawKind;           /* 0x02 */
    u8    pad_04[8];
    u16   nPrice;             /* 0x0c */
    u8    bFlag : 1;          /* 0x0e bit 0 */
    u8    nOwnText : 7;       /*      bits 1..7: 0 = use the shop record's text */
    u8    nLevel;             /* 0x0f */
    int   nShopIndex;         /* 0x10: 1-based shop record */
    u16  *pName;              /* 0x14 */
    u16  *pDescription;       /* 0x18 */
    int   nNameLen;           /* 0x1c */
    int   nDescriptionLen;    /* 0x20 */
} Ov008RawRewardRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[0x14];
    Ov008ParamRecord *pRecords; /* 0x14: shop records (db 0x15) */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov026_0209136c;
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);              /* AllocDefault */
extern void MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);

void func_ov026_0208d064(Ov008RewardRecord *pOut, Ov008RawRewardRecord *pRaw, u16 nIndex)
{
    pOut->nKind = RECORD_KIND_REWARD;
    pOut->nIndex = nIndex;
    pOut->bNotItem = pRaw->nRawKind != RAW_KIND_ITEM;
    pOut->nLevel = pRaw->nLevel;
    pOut->bFlag = pRaw->bFlag;
    pOut->nOwnText = pRaw->nOwnText;
    if (pRaw->nOwnText == 0) {
        pOut->pItemDef = data_ov026_0209136c->pRecords[pRaw->nShopIndex - 1].pItemDef;
        pOut->pName = pOut->pItemDef->pName;
        pOut->pDescription = pOut->pItemDef->pDescription;
    } else {
        void *pBuffer = NNSi_FndAllocFromDefaultExpHeap((pRaw->nNameLen + pRaw->nDescriptionLen) * 2);
        pOut->pItemDef = 0;
        pOut->pName = pBuffer;
        pOut->pDescription = (u8 *)pBuffer + pRaw->nNameLen * 2;
        MI_CpuCopy8(pRaw->pName, pOut->pName, pRaw->nNameLen << 1);
        MI_CpuCopy8(pRaw->pDescription, pOut->pDescription, pRaw->nDescriptionLen << 1);
        pOut->nShopIndex = pRaw->nShopIndex;
    }
    pOut->nPrice = pRaw->nPrice;
}
