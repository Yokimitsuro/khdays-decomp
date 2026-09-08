/* ov022: apply one packed state message to an actor's state block.
 *
 * The first byte carries three things: the actor's index, a small sub-value used
 * as a bit number, and the opcode. The actor is looked up by index and the
 * message is applied to its state block; an unknown opcode and a missing actor
 * are both ignored.
 *
 * Every opcode is gated on the session, but not all the same way: the reset and
 * the two flag writes only run while the session is down, whereas the sub-mask
 * set only runs while it is up.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor;
typedef void (*PfnState)(struct Actor *pActor);

struct Actor {
    u8 pad0000[0x12];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x678];
    PfnState pfnState;           /* 0x068c */
};

/* The state block that lives at the actor's 0x22f8. */
struct StateBlk {
    u32 nFlags;                  /* 0x0000 */
    int nPhase;                  /* 0x0004 */
    u8 pad0008[0x324];
    u32 nParam;                  /* 0x032c */
    u8 pad0330[5];
    u8 nByte335;                 /* 0x0335 */
    u16 nHpAtStart;              /* 0x0336 */
    u8 pad0338[6];
    u8 nSubMask;                 /* 0x033e */
};

/* The packed message: the head byte holds all three fields. */
struct Msg {
    u8 nIndex : 2;               /* 0x0000 bits 0-1 */
    u8 nSub : 3;                 /* bits 2-4 */
    u8 nOp : 3;                  /* bits 5-7 */
    u8 nByte1;                   /* 0x0001 */
    u8 pad0002[2];
    u32 nWord4;                  /* 0x0004 */
};

extern struct Actor *func_01fffde0(int nIndex);
extern int func_02030694(void);
extern void func_ov022_020b1bb4(u8 *pBlk);
extern void func_ov022_02094b40(struct StateBlk *pBlk);

void func_ov022_020942f0(struct Msg *pMsg)
{
    struct Actor *pActor;
    struct StateBlk *pBlk;

    pActor = func_01fffde0(pMsg->nIndex);
    if (pActor == 0) {
        return;
    }
    pBlk = (struct StateBlk *)((u8 *)pActor + 0x22f8);
    switch (pMsg->nOp) {
    case 0:
        if (func_02030694() != 0) {
            return;
        }
        func_ov022_020b1bb4((u8 *)pActor + 0xd90);
        pActor->pfnState(pActor);
        pBlk->nPhase = 3;
        func_ov022_02094b40(pBlk);
        break;
    case 1:
        if (func_02030694() == 0) {
            return;
        }
        pBlk->nSubMask |= 1 << pMsg->nSub;
        break;
    case 2:
        if (func_02030694() != 0) {
            return;
        }
        pBlk->nFlags |= 2;
        break;
    case 3:
        if (func_02030694() == 0) {
            pBlk->nParam = 0;
            pBlk->nFlags |= 0x80;
        }
        pBlk->nHpAtStart = pActor->nHp;
        break;
    case 4:
        if (func_02030694() == 0) {
            pBlk->nParam = pMsg->nWord4;
        }
        break;
    case 5:
        if (func_02030694() == 0) {
            pBlk->nByte335 = pMsg->nByte1;
        }
        break;
    }
}
