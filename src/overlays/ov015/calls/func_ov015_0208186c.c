/* func_ov015_0208186c -- Ov015_ChestHandleMessage: the chest's message handler.  Type 1
 * (open): the message's position (+0x4) becomes the target (+0x468), its player byte
 * (+0x10) the opener (+0x726) and the opening flag (bit 2 of +0x464) is raised.  Type 3
 * (acknowledge): unless the chest is being refreshed (bit 0 of +0x724), the message's
 * player byte (+0x4) is acknowledged (02081824).  Type 5 (open request): unless the chest
 * is refreshing or already opening / rising (bits 5 / 6), the opened bit is dropped, the
 * open-request bit raised and the player byte recorded as the opener. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int func_ov015_02081824(void *pChest, int nPlayer);        /* Ov015_ChestAckPlayer */

typedef struct Ov015Chest {
    u8   pad_000[0x464];
    u16  nChestFlags;         /* 0x464: bit 2 = opening */
    u8   pad_466[2];
    VecFx32 target;           /* 0x468 */
    u8   pad_474[0x724 - 0x474];
    u8   nStateBits;          /* 0x724: bit 0 refresh, bit 4 opened, bit 5 open request, bit 6 rising */
    u8   pad_725;
    s8   nOpener;             /* 0x726 */
} Ov015Chest;

typedef struct Ov015ChestMessage {
    u8   nType;               /* 0x00: 1 open, 3 acknowledge, 5 open request */
    u8   pad_01[3];
    union {
        VecFx32 position;     /* 0x04: type 1 */
        u8  nPlayer;          /* 0x04: type 3 */
        s8  nOpener5;         /* 0x04: type 5 */
    } u;
    s8   nOpener;             /* 0x10: type 1 */
} Ov015ChestMessage;

void func_ov015_0208186c(Ov015Chest *pChest, Ov015ChestMessage *pMessage)
{
    u8 nBits;

    switch (pMessage->nType) {
    case 1:
        pChest->nOpener = pMessage->nOpener;
        pChest->target = pMessage->u.position;
        pChest->nChestFlags |= 4;
        break;
    case 3:
        if (pChest->nStateBits & 1) {
            return;
        }
        func_ov015_02081824(pChest, pMessage->u.nPlayer);
        break;
    case 5:
        nBits = pChest->nStateBits;
        if (nBits & 1) {
            return;
        }
        if (nBits & 0x60) {
            return;
        }
        pChest->nStateBits &= ~0x10;
        pChest->nStateBits |= 0x20;
        pChest->nOpener = pMessage->u.nOpener5;
        break;
    }
}
