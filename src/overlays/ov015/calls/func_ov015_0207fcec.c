/* func_ov015_0207fcec -- Ov015_PickupCollect: collect the pickup.  Unless bit 1 of the
 * session byte 0204c240 is set, the mission flag (class table base +0x86 plus the pickup's
 * offset +0x153) is set (020235a8); the piece is reported (ov002 020767ec); its GameState
 * field (+0x14 / +0x16) keeps only its bit 0 and gains bit 1 (the collected mark); the
 * collidable flag (bit 3 of +0x12) is dropped.  A pickup that reveals a linked object
 * (bit 7 of +0x14d clear) shows that object's node (first key +0x14e, ov002 02073ed0 show
 * 1 priority -1) and reports 1; otherwise its taken sequence (+0x30) is started (0207fa40,
 * spin 0x1e000) and 0 is reported.  The collected bit (bit 1 of +0x14d) is set either way. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern u8   data_0204c240;                                          /* session bits */
extern void func_020235a8(int nFlag);                               /* GameState_SetFlag */
extern void func_ov002_020767ec(void *pPiece);                      /* report a collected piece */
extern int  func_020235d0(u16 nField, u8 nBit);                     /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);         /* GameState_SetField */
extern void func_ov015_0207fa40(void *pPickup, void *pSequence, int nArg, int nSpin, int nRise); /* Ov015_StoreArgsRunTwoSubActionsIfFlag4 */
extern void func_ov002_02073ed0(int nKey, int bShow, int nPriority); /* show / hide a keyed object's node */

typedef struct Ov015PickupDef {
    u8   pad_00[0x86];
    u16  nFlagBase;           /* 0x86 */
} Ov015PickupDef;

typedef struct Ov015Pickup {
    u8   pad_000[8];
    Ov015PickupDef *pDef;     /* 0x008 */
    u8   pad_00c[6];
    u16  nFlags;              /* 0x012: bit 3 collidable */
    u16  nStateField;         /* 0x014 */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017[0x30 - 0x17];
    u16  sequence;            /* 0x030 */
    u8   pad_032[0x14d - 0x32];
    u8   nStateBits;          /* 0x14d: bit 1 collected, bit 7 no linked object */
    short aLinkKey[2];        /* 0x14e */
    u8   pad_152;
    u8   nFlagOffset;         /* 0x153 */
} Ov015Pickup;

int func_ov015_0207fcec(Ov015Pickup *pPickup)
{
    Ov015PickupDef *pDef;
    int nResult;
    u32 nField;

    pDef = pPickup->pDef;
    nResult = 1;
    if ((data_0204c240 & 2) == 0) {
        func_020235a8(pDef->nFlagBase + pPickup->nFlagOffset);
    }
    func_ov002_020767ec(pPickup);
    nField = func_020235d0(pPickup->nStateField, pPickup->nStateBit);
    func_020235e8(pPickup->nStateField, pPickup->nStateBit, (nField & 0xffff0001) | 2);
    pPickup->nFlags &= ~8;
    if (pPickup->nStateBits & 0x80) {
        func_ov015_0207fa40(pPickup, &pPickup->sequence, 0, 0x1e000, 0);
        nResult = 0;
    } else if (pPickup->aLinkKey[0] >= 0) {
        func_ov002_02073ed0(pPickup->aLinkKey[0], 1, -1);
    }
    pPickup->nStateBits |= 2;
    return nResult;
}
