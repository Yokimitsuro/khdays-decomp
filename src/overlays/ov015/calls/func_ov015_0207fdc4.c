/* func_ov015_0207fdc4 -- Ov015_PickupPlayTakenSequence: while the pickup's "taken"
 * sequence is running (bit 0 of +0x14d), advance its tracks by nDelta; once it ends the
 * bit is cleared and 1 returned, otherwise the sequence node (+0x30) is drawn.  0 when
 * nothing was running or the sequence is still going. */
typedef unsigned char u8;
typedef unsigned int  u32;

extern u32  func_0202a818(void *pNode, int nDelta);   /* Sequence_UpdateTracks */
extern void func_0202aa9c(void *pNode);               /* Scene_DrawNode */

typedef struct Ov015Pickup {
    u8  pad_000[0x30];
    u8  sequence[0x14d - 0x30];  /* 0x030: scene node + sequence */
    u8  nStateBits;              /* 0x14d: bit 0 = the taken sequence is playing */
} Ov015Pickup;

int func_ov015_0207fdc4(Ov015Pickup *pPickup, int nDelta)
{
    if (pPickup->nStateBits & 1) {
        if (func_0202a818(pPickup->sequence, nDelta) != 0) {
            pPickup->nStateBits &= ~1;
            return 1;
        }
        func_0202aa9c(pPickup->sequence);
    }
    return 0;
}
