/* func_ov015_020804a4 -- Ov015_TriggerUpdate: the trigger's per-frame handler.  Disabled
 * while its GameState field (+0x14 / +0x16) is clear.  An untouched trigger (+0x50 == 0)
 * whose match word (+0x4c) accepts the actor's two masks (actor +0x14 / +0x18, ov002
 * 0207c788) arms the session's leave request (ov002 0206b88c) and queues a 4-byte type-1
 * message on itself (ov002 020766e0); if the message is refused the request is cleared
 * again, otherwise the trigger is marked fired (+0x50 = 1).  Always returns 8. */
typedef unsigned char  u8;
typedef unsigned short u16;

extern int func_020235d0(u16 nField, u8 nBit);                   /* GameState_GetField */
extern int func_ov002_0207c788(int nMatch, int nMaskHi, int nMaskLo); /* packed hi / lo mask match */
extern int func_ov002_0206b88c(int bOn);                         /* arm / clear the leave request */
extern int func_ov002_020766e0(void *pPiece, void *pMessage, int nKind); /* queue a message on the piece */

typedef struct Ov015Trigger {
    u8  pad_00[0x14];
    u16 nStateField;          /* 0x14 */
    u8  nStateBit;            /* 0x16 */
    u8  pad_17[0x4c - 0x17];
    int nParam;               /* 0x4c: packed hi / lo match masks */
    u8  nState;               /* 0x50: 1 once fired */
} Ov015Trigger;

typedef struct Ov015TriggerActor {
    u8  pad_00[0x14];
    int nMaskHi;              /* 0x14 */
    int nMaskLo;              /* 0x18 */
} Ov015TriggerActor;

int func_ov015_020804a4(Ov015Trigger *pTrigger, Ov015TriggerActor *pActor, int nArg2, int nArg3)
{
    int bEnabled;
    u8 message[4];

    if ((func_020235d0(pTrigger->nStateField, pTrigger->nStateBit) & 1) != 0) {
        bEnabled = 1;
    } else {
        bEnabled = 0;
    }
    if (bEnabled == 0) {
        return 8;
    }
    if (pTrigger->nState == 0
        && func_ov002_0207c788(pTrigger->nParam, pActor->nMaskHi, pActor->nMaskLo) != 0
        && func_ov002_0206b88c(1) != 0) {
        message[0] = 1;
        if (func_ov002_020766e0(pTrigger, message, 4) == 0) {
            func_ov002_0206b88c(0);
        } else {
            pTrigger->nState = 1;
        }
    }
    return 8;
}
