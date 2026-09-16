/* func_ov015_0207ffd0 -- Ov015_PickupTakenStep: the taken flow of a model-less pickup.
 * State 2 collects it (0207fcec); an invisible pickup (bit 2 of +0x12 clear) is finished at
 * once, a visible one rewinds its sequence (ov002 0207c618 track 0 frame 0), disables the
 * node (0202af2c), marks the taken sequence playing (bit 0 of +0x14d) and moves to state 3.
 * State 3 waits for the taken sequence (0207fdc4, again finished at once when invisible).
 * Finishing clears the playing bit, enters state 4, marks the GameState field collected
 * (bit 1, keeping bit 0), retires the piece (ov002 02076bd8 mode 0) and hands back the
 * vanish step (ov002 0207cea4); otherwise 0 is returned.
 * Codegen: the done flag is zeroed after the delta call and the case-3 result is folded
 * through an if (not `!= 0`); both are needed for the parameter to stay in r5. */
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
typedef void *Ov015StateFn(void *pPiece);
extern Ov015StateFn func_ov002_0207cea4;                            /* the vanish step */

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

Ov015StateFn *func_ov015_0207ffd0(Ov015Pickup *pPickup)
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
            func_ov002_0207c618(&pPickup->sequence, 0, 0);
            func_0202af2c(&pPickup->sequence);
            pPickup->nStateBits |= 1;
            pPickup->nState = 3;
        }
        break;
    case 3:
        if (pPickup->nFlags & 4) {
            if (func_ov015_0207fdc4(pPickup, nDelta)) {
                bDone = 1;
            }
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
        return func_ov002_0207cea4;
    }
    return 0;
}
