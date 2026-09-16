/* func_ov017_0207fdb4 -- Ov017_DepositHit: hit handler of the deposit.  While the deposit has not been
 * hit yet (+0x4da == 0) a 16-byte type-1 message (kind 0x10) carrying the hit record's player byte
 * (+0xc) is queued on the piece (ov002 020766e0); once it goes out the hit byte is set to 1
 * and the hit accepted (0).  Otherwise the hit is refused with 8. */
typedef unsigned char  u8;

typedef struct Ov017HitInfo {
    u8   pad_00[0xc];
    u8   nPlayer;             /* 0x0c */
} Ov017HitInfo;

typedef struct Ov017DepositMessage {
    u8   nType;               /* 0x00: 1 */
    u8   pad_01[3];
    u8   nPlayer;             /* 0x04 */
    u8   pad_05[0x10 - 5];
} Ov017DepositMessage;

typedef struct Ov017Deposit {
    u8   pad_000[0x4da];
    u8   nHitState;           /* 0x4da: 0 intact, 1 hit sent, 2 hit acknowledged */
} Ov017Deposit;

extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */

int func_ov017_0207fdb4(Ov017Deposit *pSelf, Ov017HitInfo *pHit)
{
    Ov017DepositMessage message;

    if (pSelf->nHitState == 0) {
        message.nType = 1;
        message.nPlayer = pHit->nPlayer;
        if (func_ov002_020766e0(pSelf, &message, 0x10) != 0) {
            pSelf->nHitState = 1;
            return 0;
        }
    }
    return 8;
}
