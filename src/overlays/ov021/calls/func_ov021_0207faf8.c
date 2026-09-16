/* func_ov021_0207faf8 -- Ov021_PrizeBoxHandleMessage: the prize box's message handler.  Type 1
 * (the open request was accepted): state 2.  Type 2 (the prize was taken): state 7.  Type 3
 * (opened): state 5, the spawn id for an item prize (+0x1bb, six bits of the message byte at
 * +4) and the prize index (+0x1be, the byte at +5); the host also posts one point of kind 3
 * to the opening player (the top two bits of that byte; ov002 0206bbb8).  Any other type does
 * nothing. */
typedef unsigned char  u8;

typedef struct Ov021PrizeBoxMessage {
    u8   nType;               /* 0x00: 1 accepted, 2 taken, 3 opened */
    u8   pad_01[3];
    u8   nSpawnId : 6;        /* 0x04 */
    u8   nPlayer : 2;
    char nPrize;              /* 0x05 */
} Ov021PrizeBoxMessage;

typedef struct Ov021PrizeBox {
    u8   pad_000[0x1b8];
    u8   nState;              /* 0x1b8 */
    u8   pad_1b9[2];
    u8   nSpawnId;            /* 0x1bb */
    u8   pad_1bc[2];
    u8   nPrize;              /* 0x1be: index into the class's prize list */
} Ov021PrizeBox;

extern int  func_02030788(void);                                      /* Session_GetLocalPlayerIndex */
extern void func_ov002_0206bbb8(int nPlayer, int nKind, int nCount);  /* post to the mission tally */

void func_ov021_0207faf8(Ov021PrizeBox *pSelf, Ov021PrizeBoxMessage *pMessage)
{
    switch (pMessage->nType) {
    case 1:
        pSelf->nState = 2;
        break;
    case 2:
        pSelf->nState = 7;
        break;
    case 3:
        pSelf->nState = 5;
        pSelf->nSpawnId = pMessage->nSpawnId;
        pSelf->nPrize = pMessage->nPrize;
        if (func_02030788() != 0) {
            return;
        }
        func_ov002_0206bbb8(pMessage->nPlayer, 3, 1);
        break;
    }
}
