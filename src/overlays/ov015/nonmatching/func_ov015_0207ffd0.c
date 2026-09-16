/* NOT MATCHING -- 260 bytes, exact size, instruction count and relocations; the only
 * residue is the r4 / r5 pair: the ROM keeps the pickup parameter in r5 and the done flag
 * in r4, mwccarm 3.0 build 139 the other way round (20 renamed lines, nothing else).
 *
 * Swept without effect: switch vs if-chain (the switch is needed for the dispatch), branch
 * orders, the flag initialised before / after the delta call, all declaration orders, the
 * flag and delta types (u32 / u8 / char / short / u16), the flag reused as the field value,
 * a block-scoped flag (also C99 `int bDone = 0`), an explicit parameter copy (two
 * positions), a void parameter with a typed local, a second pointer variable for the
 * retire / collect calls, const / register on both, 2 / 3 / 4 parameters, int and state-
 * function-pointer returns, an early-return tail, no field local, a volatile dummy, the
 * delta variable taking the case-3 result, every callee prototype x return type and x
 * parameter type (retsweep / protosweep), the C++ lane.  Notes: build/held. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int  func_ov002_0207687c(void);                              /* frame delta */
extern int  func_ov015_0207fcec(void *pPickup);                     /* Ov015_PickupCollect */
extern void func_ov002_0207c618(u16 *pNode, int nTrack, int nFrame); /* rewind a sequence */
extern void func_0202af2c(u16 *pNode);                              /* SceneNode_Disable */
extern int  func_ov015_0207fdc4(void *pPickup, int nDelta);         /* Ov015_PickupPlayTakenSequence */
extern int  func_020235d0(u16 nField, u8 nBit);                     /* GameState_GetField */
extern void func_020235e8(u16 nField, u8 nBit, u16 nValue);         /* GameState_SetField */
extern void func_ov002_02076bd8(void *pPiece, int nMode);           /* retire the piece */
extern void func_ov002_0207cea4(void);                              /* the vanish step */

typedef struct Ov015Pickup {
    u8   pad_000[0x12];
    u16  nFlags;              /* 0x012: bit 2 visible */
    u16  nStateField;         /* 0x014 */
    u8   nStateBit;           /* 0x016 */
    u8   pad_017[0x30 - 0x17];
    u16  sequence;            /* 0x030 */
    u8   pad_032[0x14c - 0x32];
    u8   nState;              /* 0x14c */
    u8   nStateBits;          /* 0x14d */
} Ov015Pickup;

void *func_ov015_0207ffd0(Ov015Pickup *pPickup)
{
    int nDelta;
    int bDone;
    u32 nField;

    nDelta = func_ov002_0207687c();
    bDone = 0;
    switch (pPickup->nState) {
    case 2:
        func_ov015_0207fcec(pPickup);
        if ((pPickup->nFlags & 4) == 0) {
            bDone = 1;
        } else {
            func_ov002_0207c618(&pPickup->sequence, bDone, bDone);
            func_0202af2c(&pPickup->sequence);
            pPickup->nStateBits |= 1;
            pPickup->nState = 3;
        }
        break;
    case 3:
        if (pPickup->nFlags & 4) {
            bDone = func_ov015_0207fdc4(pPickup, nDelta) != 0;
        } else {
            bDone = 1;
        }
        break;
    }
    if (bDone) {
        pPickup->nStateBits &= ~1;
        pPickup->nState = 4;
        nField = func_020235d0(pPickup->nStateField, pPickup->nStateBit);
        func_020235e8(pPickup->nStateField, pPickup->nStateBit, (nField & 0xffff0001) | 2);
        func_ov002_02076bd8(pPickup, 0);
        return (void *)func_ov002_0207cea4;
    }
    return 0;
}
