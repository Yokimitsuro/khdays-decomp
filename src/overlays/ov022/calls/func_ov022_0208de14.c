/* Ov022_EnterReactionAtActor -- arm a reaction state on the context's slot.
 *
 * The sibling of the block entry, for the state that keeps its aim point in the
 * slot instead of on the stack: the actor's position is staged across the three
 * words the running slot later uses for its power, its reach and its pending
 * flag, run through the notifier from there, and only then copied into the aim
 * field. Nothing raises it, so the slot is aimed at the actor's feet. The local
 * vector below is how those three words are addressed as one object; the names
 * they carry once the reaction is running are in the Ghidra type.
 *
 * As in the block entry the slot takes the actor's slot index and a fresh
 * sequence number, the node angle makes its round trip through the field's
 * bias, and the state ends up armed with the timer cleared.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad000[0x80];
    u16 nAngle;                  /* 0x0080 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad024[0x42];
    short nSlotIndex;            /* 0x0066 */
    u8 pad068[0x424];
    struct VecFx32 vecPos;       /* 0x048c */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                    /* 0x000 */
    u8 pad001;
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0x7a];
    u16 nAngle;                  /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;       /* 0x0ac */
    u8 pad0b8[0x58];
    u8 nSlotIndex;               /* 0x110 */
    u8 pad111[7];
    u8 nState;                   /* 0x118 */
    u8 pad119[3];
    int nTimer;                  /* 0x11c */
    struct VecFx32 vecScratch;   /* 0x120 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0x44];
    struct ActorSlot *pSlot;     /* 0x44 */
    u8 pad48[0xc];
    int nTrack;                  /* 0x54 */
    struct Actor *pActor;        /* 0x58 */
};

#define ANGLE_UNBIAS(a) ((u16)((a) - 0x8000))
#define ANGLE_BIAS(a) ((a) + 0x8000)

extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, int nTrack, u16 *pFlags,
                                int nBinding);
extern int func_ov022_0208acc4(int nKind, int nMode);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAim,
                                int nReaction);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);

void func_ov022_0208de14(struct ReactionCtx *pCtx)
{
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    u16 nAngle;
    int nReaction;

    pActor = pCtx->pActor;
    pSlot = pCtx->pSlot;
    nAngle = pActor->pNode->nAngle;
    pSlot->nSlotIndex = (u8)pActor->nSlotIndex;
    pSlot->nSeq = pSlot->nSeq + 1;
    pSlot->vecScratch = pActor->vecPos;
    func_ov022_0208a8bc(pCtx, pCtx->nTrack + 4, &pSlot->nSlotFlags, 0);
    nReaction = func_ov022_0208acc4(pSlot->nKind, 0);
    func_ov022_0208acdc(pCtx, &pSlot->vecScratch, nReaction);
    pSlot->vecAim = pSlot->vecScratch;
    pSlot->nAngle = ANGLE_BIAS(ANGLE_UNBIAS(nAngle));
    pSlot->nSlotFlags |= 0x20;
    func_ov022_0208a6b0(pCtx);
    pSlot->nState = 2;
    pSlot->nTimer = 0;
}
