/* func_ov026_0208cfc4 -- Ov008_BuildSlotPacketB: fill the kind-2 slot packet from
 * a slot entry: the entry's item id (record table lookup by index), three copied
 * words, then four (link, item) pairs -- a pair's item is the record item of its
 * link, or 0 without a link (a `!= 0 ? lookup : 0` ternary; the if/else form colours
 * the shared zero one register up).
 */
typedef unsigned char u8;

typedef struct Ov008ParamRecord {
    u8  pad_00[0xc];
    void *pItemDef;           /* 0x0c: item definition (Ov008ItemDef) */
    u8  pad_10[0x34 - 0x10];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[0x14];
    Ov008ParamRecord *pRecords; /* 0x14 */
} Ov008ParamTable;

typedef struct Ov008LinkPair {
    int nLinkIndex;           /* 0x00 */
    int nLink;                /* 0x04 */
} Ov008LinkPair;

typedef struct Ov008SlotEntryB {
    u8  pad_00[0xc];
    int nA;                   /* 0x0c */
    int nIndex;               /* 0x10 */
    int nB;                   /* 0x14 */
    int nC;                   /* 0x18 */
    Ov008LinkPair aPair[4];   /* 0x1c */
} Ov008SlotEntryB;

typedef struct Ov008SlotPacketB {
    int nKind;                /* 0x00 */
    int nA;                   /* 0x04 */
    int nC;                   /* 0x08 */
    void *pItemDef;           /* 0x0c: item definition (Ov008ItemDef) */
    int nB;                   /* 0x10 */
    Ov008LinkPair aPair[4];   /* 0x14: nLinkIndex = item id, nLink = link */
} Ov008SlotPacketB;

#define PACKET_KIND_B 2
#define PAIR_COUNT    4

extern Ov008ParamTable *data_ov026_0209136c;

void func_ov026_0208cfc4(Ov008SlotPacketB *pOut, Ov008SlotEntryB *pIn)
{
    int i;
    int nLink;

    pOut->pItemDef = data_ov026_0209136c->pRecords[pIn->nIndex - 1].pItemDef;
    pOut->nKind = PACKET_KIND_B;
    pOut->nA = pIn->nA;
    pOut->nC = pIn->nC;
    pOut->nB = pIn->nB;
    for (i = 0; i < PAIR_COUNT; i++) {
        nLink = pIn->aPair[i].nLink;
        pOut->aPair[i].nLink = nLink;
        pOut->aPair[i].nLinkIndex = nLink != 0 ? (int)data_ov026_0209136c->pRecords[pIn->aPair[i].nLinkIndex - 1].pItemDef : 0;
    }
}
