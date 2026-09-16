/* func_ov021_02080540 -- Ov021_EmblemHandleMessage: the emblem's message handler; only type 0
 * (a player reached it) does anything.  Records the player (+0x2bc, the message byte at +4),
 * resets the spiral (+0x2be = 0) and picks its direction (+0x2bd): +1 in a session (02030670),
 * otherwise +1 or -1 at random (Rand16NextScaled 02023e80); state 2.  Then, inside a running
 * scene (ov002 0206b758): when the player is the local peer (01fffe14) the pickup sound plays
 * (02033b24 pair 0 / 0xf); otherwise, if the local peer's owner slot (ov022 02088474) is the
 * bucket's current piece kind (ov002 02072754), the pickup effect (slot 0 / kind 0xf) is
 * spawned where that peer sits (ov022 020881f8; 02033d0c). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov021EmblemMessage {
    u8   nType;               /* 0x00: 0 = reached */
    u8   pad_01[3];
    char nPlayer;             /* 0x04 */
} Ov021EmblemMessage;

typedef struct Ov021Emblem {
    u8   pad_000[0x10];
    u8   nBucket;             /* 0x010 */
    u8   pad_011[0x2b4 - 0x11];
    u8   nState;              /* 0x2b4 */
    u8   pad_2b5[7];
    char nPlayer;             /* 0x2bc */
    char nDirection;          /* 0x2bd: +1 / -1 */
    u16  nSpiral;             /* 0x2be */
} Ov021Emblem;

extern int   func_02030670(void);                                     /* Session_IsActive */
extern int   func_02023e80(int nRange);                               /* Rand16NextScaled */
extern int   func_ov002_0206b758(void);                               /* scene running? */
extern int   func_01fffe14(void);                                     /* the local peer */
extern void  func_02033b24(int nPair, int nArg);                      /* PlaySoundChecked */
extern int   func_ov022_02088474(int nSeat);                          /* seat -> owner slot */
extern int   func_ov002_02072754(void);                               /* current piece kind */
extern VecFx32 *func_ov022_020881f8(int nSeat);                       /* where the seat is */
extern int   func_02033d0c(int nSlot, int nId, VecFx32 *pPos, u16 nFlags); /* Slot_Spawn */

void func_ov021_02080540(Ov021Emblem *pSelf, Ov021EmblemMessage *pMessage)
{
    if (pMessage->nType != 0) {
        return;
    }
    pSelf->nPlayer = pMessage->nPlayer;
    pSelf->nSpiral = 0;
    pSelf->nDirection = func_02030670() != 0 ? 1 : (func_02023e80(2) != 0 ? -1 : 1);
    pSelf->nState = 2;
    if (func_ov002_0206b758() == 0) {
        return;
    }
    if (pSelf->nPlayer == func_01fffe14()) {
        func_02033b24(0, 0xf);
        return;
    }
    func_ov022_02088474(func_01fffe14());
    if (pSelf->nBucket != func_ov002_02072754()) {
        return;
    }
    func_02033d0c(0, 0xf, func_ov022_020881f8(func_01fffe14()), 0);
}
