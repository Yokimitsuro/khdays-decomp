/* func_ov008_0208a078 -- Ov008_BuildSlotPacketA: fill the kind-0 slot packet from
 * a slot entry.  The packet gets the entry's item id (looked up in the shared
 * record table by the entry's index) and its fields copied over; the link word is
 * -1 when the entry has none, else the entry's link minus two (a `== -1 ? -1 :`
 * ternary after the item lookup -- the `!=` polarity defers the subtract); the tail word is
 * cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008ParamRecord {
    u8  pad_00[0xc];
    int nItemId;              /* 0x0c */
    u8  pad_10[0x34 - 0x10];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[0x14];
    Ov008ParamRecord *pRecords; /* 0x14 */
} Ov008ParamTable;

typedef struct Ov008SlotEntry {
    u8  pad_00[0xc];
    int nA;                   /* 0x0c */
    int nIndex;               /* 0x10 */
    int nB;                   /* 0x14 */
    int nC;                   /* 0x18 */
    int nD;                   /* 0x1c */
    int nLink;                /* 0x20 */
    int nE;                   /* 0x24 */
    u16 nF;                   /* 0x28 */
    u8  nG;                   /* 0x2a */
    u8  nH;                   /* 0x2b */
} Ov008SlotEntry;

typedef struct Ov008SlotPacket {
    int nKind;                /* 0x00 */
    int nA;                   /* 0x04 */
    int nB;                   /* 0x08 */
    int nItemId;              /* 0x0c */
    int nB2;                  /* 0x10 */
    int nC;                   /* 0x14 */
    int nD;                   /* 0x18 */
    int nLink;                /* 0x1c */
    int nE;                   /* 0x20 */
    u16 nF;                   /* 0x24 */
    u8  nG;                   /* 0x26 */
    u8  nH;                   /* 0x27 */
    int nTail;                /* 0x28 */
} Ov008SlotPacket;

#define NO_LINK (-1)

extern Ov008ParamTable *data_ov008_02090fb0;

void func_ov008_0208a078(Ov008SlotPacket *pOut, Ov008SlotEntry *pIn)
{
    int nItemId = data_ov008_02090fb0->pRecords[pIn->nIndex - 1].nItemId;
    int nLink = pIn->nLink == NO_LINK ? NO_LINK : pIn->nLink - 2;

    pOut->nKind = 0;
    pOut->nItemId = nItemId;
    pOut->nA = pIn->nA;
    pOut->nB = pIn->nB;
    pOut->nF = pIn->nF;
    pOut->nB2 = pIn->nB;
    pOut->nG = pIn->nG;
    pOut->nC = pIn->nC;
    pOut->nD = pIn->nD;
    pOut->nE = pIn->nE;
    pOut->nLink = nLink;
    pOut->nH = pIn->nH;
    pOut->nTail = 0;
}
