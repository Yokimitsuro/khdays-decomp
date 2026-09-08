/* Ov022_EndPartRun -- end a slot part's run by posting the hit it landed.
 *
 * Only while the session is up and the slot is still open. The message is four
 * bytes of packed fields: a kind the messenger hands out, the actor's own id,
 * the slot the part belongs to, a class, the part's index and the reaction the
 * caller worked out.
 *
 * The slot at index five is the odd one: it goes out under a different class
 * and without a part index at all.
 *
 * What comes back is the slot's new open handle, which is also what closes the
 * slot to further hits until it is reopened.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_OPEN 0xffff
#define MSG_PORT 0xc

/* the four bytes posted when a part's run ends */
struct EndMessage {
    u16 nKind : 3;               /* bits 0..2 */
    u16 nOwner : 2;              /* bits 3..4 */
    u16 nSlot : 5;               /* bits 5..9 */
    u16 nClass : 3;              /* bits 10..12 */
    u16 nSpare : 3;
    u8 nIndex;                   /* 0x02 */
    u8 nReaction;                /* 0x03 */
};

/* Ov022SlotPart */
struct SlotPart {
    u8 pad000[0x14d];
    u8 nGroup : 3;               /* 0x14d */
    u8 nIndex : 5;
    u8 pad14e[2];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000[0x114];
    u16 nOpen;                   /* 0x114 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[9];
    u8 nId;                      /* 0x0009 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x14];
    struct Actor *pActor;        /* 0x58 */
};

extern int func_02030694(void);
extern int func_01fffe14(void);
extern int func_02031384(int nPort, struct EndMessage *pMsg, int nSize);

void func_ov022_0208a50c(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                         int nReaction)
{
    struct EndMessage msg;
    struct ActorSlot *pSlot;
    struct Actor *pActor;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    if (func_02030694() == 0) {
        return;
    }
    if (pSlot->nOpen != SLOT_OPEN) {
        return;
    }
    msg.nKind = func_01fffe14();
    msg.nOwner = pActor->nId;
    msg.nClass = 2;
    msg.nSlot = pCtx->nSlot;
    if (msg.nSlot != 5) {
        msg.nIndex = pPart->nIndex;
    } else {
        msg.nIndex = 0;
        msg.nClass = 4;
    }
    msg.nReaction = (u8)nReaction;
    pSlot->nOpen = (u16)func_02031384(MSG_PORT, &msg, 4);
}
