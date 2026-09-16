/* func_ov021_0207fd98 -- Ov021_PrizeBoxHit: hit handler of the prize box (a player touching
 * it), accepted only in states 0..3.  A hit with bit 5 of its flags (+0x14, an open action)
 * queues a type-3 message (kind 6) carrying the player (two bits of the hit's +0xc) and the
 * prize index (+0x1be); for an item prize (type 0 in the class list at +0x78) the box first
 * takes a spawn id from the low band (ov002 02077b30) if it has none (+0x1bb == -1) and puts
 * it in the message's six low bits; once the message goes out the state becomes 4 and the hit
 * is accepted (0).  Any other hit, in state 0 only, sends gate message 5 {1, the byte at
 * +0x11, the box's index in its class} (02031258) and moves to state 1, accepting the hit.
 * Otherwise 8. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov021HitInfo {
    u8   pad_00[0xc];
    u8   nPlayer;             /* 0x0c */
    u8   pad_0d[7];
    int  nFlags;              /* 0x14: bit 5 = open */
} Ov021HitInfo;

typedef struct Ov021OpenMessage {
    u8   nType;               /* 0x00: 3 */
    u8   pad_01[3];
    u8   nSpawnId : 6;        /* 0x04 */
    u8   nPlayer : 2;
    char nPrize;              /* 0x05 */
} Ov021OpenMessage;

typedef struct Ov021GateMessage {
    u8   nType;               /* 0x00: 1 */
    u8   nByte11;             /* 0x01 */
    u16  nIndex;              /* 0x02 */
} Ov021GateMessage;

typedef struct Ov021Prize {
    char  nType;              /* 0x00: 0 item, 1 munny, 2 keyed object, 3 nothing */
    u8    pad_01;
    short nValue;             /* 0x02 */
    u8    bFlag;              /* 0x04 */
    u8    pad_05;
} Ov021Prize;

typedef struct Ov021PrizeBoxDef {
    u8   pad_00[0x4e];
    u16  nStride;             /* 0x4e */
    u8   pad_50[4];
    u8  *pBase;               /* 0x54 */
    u8   pad_58[0x78 - 0x58];
    Ov021Prize aPrize[1];     /* 0x78 */
} Ov021PrizeBoxDef;

typedef struct Ov021PrizeBox {
    u8   pad_000[8];
    Ov021PrizeBoxDef *pDef;   /* 0x008 */
    u8   pad_00c[5];
    u8   nByte11;             /* 0x011 */
    u8   pad_012[0x1b8 - 0x12];
    u8   nState;              /* 0x1b8 */
    u8   pad_1b9[2];
    char nSpawnId;            /* 0x1bb: -1 until taken */
    u8   pad_1bc[2];
    char nPrize;              /* 0x1be */
} Ov021PrizeBox;

extern int  func_ov002_02077b30(void);                                /* take a spawn id from the low band */
extern int  func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern int  func_02020400(int nNumerator, int nDenominator);          /* _s32_div_f */
extern void func_02031258(int nGate, void *pMessage, int nSize);      /* MsgQueue_SendGate */

int func_ov021_0207fd98(Ov021PrizeBox *pSelf, Ov021HitInfo *pHit)
{
    Ov021OpenMessage open;
    Ov021GateMessage gate;
    Ov021PrizeBoxDef *pDef;

    pDef = pSelf->pDef;
    if (pSelf->nState <= 3) {
        if (pHit->nFlags & 0x20) {
            open.nType = 3;
            open.nPlayer = pHit->nPlayer;
            open.nPrize = pSelf->nPrize;
            if (pDef->aPrize[pSelf->nPrize].nType == 0) {
                if (pSelf->nSpawnId == -1) {
                    pSelf->nSpawnId = func_ov002_02077b30();
                }
                open.nSpawnId = pSelf->nSpawnId;
            }
            if (func_ov002_020766e0(pSelf, &open, 6) != 0) {
                pSelf->nState = 4;
                return 0;
            }
        } else if (pSelf->nState == 0) {
            gate.nType = 1;
            gate.nByte11 = pSelf->nByte11;
            gate.nIndex = func_02020400((u8 *)pSelf - pSelf->pDef->pBase, pSelf->pDef->nStride);
            func_02031258(5, &gate, 4);
            pSelf->nState = 1;
            return 0;
        }
    }
    return 8;
}
