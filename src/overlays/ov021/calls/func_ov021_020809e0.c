/* func_ov021_020809e0 -- Ov021_EmblemStep: state function of the emblem.  Every frame the
 * timer runs down and the model shrinks with it (Ov021_EmblemTickTimer 020804d0 with the
 * frame delta, ov002 0207687c).  State 0 (lying): the host (02030788 == 0) looks for a player
 * within reach (Ov021_EmblemFindPlayer 02080758) and queues a type-0 message (kind 6) naming
 * it (ov002 020766e0), state 1 once it goes out.  State 2 (reached): the host posts the score
 * to the player (+0x2bc; ov002 0206bbb8): kind 3 worth 10 while the timer (+0x2b8) still runs,
 * 8 once it has expired, and in session mode (bit 2 of 0204c240) kind 7 worth 20 / 5; the
 * other emblems' timers are reset (Ov021_EmblemResetOthers 02080c40), state 3 and the model
 * (+0x124) is hidden (0202bedc 0) while the model is bound (bit 2 of +0x12).  State 3
 * (flying): once Ov021_EmblemFlyToPlayer (02080828) reports arrival, state 4 and the terminal
 * state (ov002 0207cea4).  Finally, unless collected (state 4), the sequence node (+0x1c) is
 * drawn (0202aa9c) while the model is bound.  Returns 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov021EmblemMessage {
    u8   nType;               /* 0x00: 0 = reached */
    u8   pad_01[3];
    char nPlayer;             /* 0x04 */
    u8   pad_05;
} Ov021EmblemMessage;

typedef struct Ov021Emblem {
    u8   pad_000[0x12];
    u16  nPieceFlags;         /* 0x012: bit 2 = model bound */
    u8   pad_014[0x1c - 0x14];
    u16  nSeqFlags;           /* 0x01c: the sequence node */
    u8   pad_01e[0x124 - 0x1e];
    u8   modelNode[0x2b4 - 0x124]; /* 0x124 */
    u8   nState;              /* 0x2b4 */
    u8   pad_2b5[3];
    int  nTimer;              /* 0x2b8 */
    char nPlayer;             /* 0x2bc */
} Ov021Emblem;

extern int   func_ov002_0207687c(void);                               /* frame delta */
extern void  func_ov021_020804d0(Ov021Emblem *pSelf, int nDelta);     /* Ov021_EmblemTickTimer */
extern int   func_02030788(void);                                     /* Session_GetLocalPlayerIndex */
extern int   func_ov021_02080758(Ov021Emblem *pSelf);                 /* Ov021_EmblemFindPlayer */
extern int   func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */
extern void  func_ov002_0206bbb8(int nPlayer, int nKind, int nCount); /* post to the mission tally */
extern void  func_ov021_02080c40(Ov021Emblem *pSelf);                 /* Ov021_EmblemResetOthers */
extern void  func_0202bedc(void *pNode, int nFlag);                   /* Obj_SetFlagBit3 */
extern int   func_ov021_02080828(Ov021Emblem *pSelf);                 /* Ov021_EmblemFlyToPlayer */
extern void  func_0202aa9c(void *pNode);                              /* Scene_DrawNode */
extern void *func_ov002_0207cea4(void *pPiece);                       /* terminal state */
extern u8    data_0204c240;                                           /* session bits */

void *func_ov021_020809e0(Ov021Emblem *pSelf)
{
    Ov021EmblemMessage message;
    int nPlayer;

    func_ov021_020804d0(pSelf, func_ov002_0207687c());
    switch (pSelf->nState) {
    case 0:
        if (func_02030788() == 0) {
            nPlayer = func_ov021_02080758(pSelf);
            if (nPlayer >= 0) {
                message.nPlayer = nPlayer;
                message.nType = 0;
                if (func_ov002_020766e0(pSelf, &message, 6) != 0) {
                    pSelf->nState = 1;
                }
            }
        }
        break;
    case 2:
        if (func_02030788() == 0) {
            func_ov002_0206bbb8(pSelf->nPlayer, 3, pSelf->nTimer > 0 ? 10 : 8);
            if (data_0204c240 & 4) {
                func_ov002_0206bbb8(pSelf->nPlayer, 7, pSelf->nTimer > 0 ? 20 : 5);
            }
        }
        func_ov021_02080c40(pSelf);
        pSelf->nState = 3;
        if (pSelf->nPieceFlags & 4) {
            func_0202bedc(pSelf->modelNode, 0);
        }
        break;
    case 3:
        if (func_ov021_02080828(pSelf) != 0) {
            pSelf->nState = 4;
            return func_ov002_0207cea4;
        }
        break;
    }
    if (pSelf->nState != 4 && (pSelf->nPieceFlags & 4)) {
        func_0202aa9c(&pSelf->nSeqFlags);
    }
    return 0;
}
