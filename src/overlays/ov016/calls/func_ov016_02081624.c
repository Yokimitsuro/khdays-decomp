/* func_ov016_02081624 -- Ov016_DoorAckPeer: record peer nPeer's acknowledgement in the ack
 * mask (+0x61d); once every connected peer (01fff974 = the session's peer mask) has
 * answered, drop the "waiting" bit (bit 4 of +0x61c), clear the mask and report 1. */
typedef unsigned char u8;

typedef struct Ov016Door {
    u8 pad_000[0x61c];
    u8 nSyncFlags;            /* 0x61c: bit 4 = waiting for the peers */
    u8 nAckMask;              /* 0x61d: one bit per peer */
} Ov016Door;

extern int func_01fff974(void);   /* Session_GetPeerMask */

int func_ov016_02081624(Ov016Door *pSelf, int nPeer)
{
    pSelf->nAckMask |= 1 << nPeer;
    if ((pSelf->nAckMask & 0xf) == func_01fff974()) {
        pSelf->nSyncFlags &= ~0x10;
        pSelf->nAckMask = 0;
        return 1;
    }
    return 0;
}
