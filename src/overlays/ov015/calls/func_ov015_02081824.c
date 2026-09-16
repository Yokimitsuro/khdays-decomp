/* func_ov015_02081824 -- Ov015_ChestAckPlayer: record player nPlayer's acknowledgement in
 * the chest's ack mask (+0x725); once the low nibble equals the session's expected ack mask
 * (01fff974) the "opening" flag (bit 2 of +0x464) is cleared and the mask reset.  Returns
 * the expected mask (the callers ignore it; the non-void result is what keeps the mask's
 * register out of the store tail). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern u16 func_01fff974(void);                        /* expected-ack mask of the session */

typedef struct Ov015Chest {
    u8  pad_000[0x464];
    u16 nChestFlags;          /* 0x464: bit 2 = opening / busy */
    u8  pad_466[0x725 - 0x466];
    u8  nAckMask;             /* 0x725: players that acknowledged */
} Ov015Chest;

int func_ov015_02081824(Ov015Chest *pChest, int nPlayer)
{
    int nExpected;

    pChest->nAckMask |= 1 << nPlayer;
    nExpected = func_01fff974();
    if ((pChest->nAckMask & 0xf) == nExpected) {
        pChest->nChestFlags &= ~4;
        pChest->nAckMask = 0;
    }
    return nExpected;
}
