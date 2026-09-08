/* Ov022_AimSlotPartAtAngle -- put a slot's first waiting part on its way.
 *
 * The entry is rebuilt first, then the part still waiting to be sent is found
 * and switched to the flying state. The owner gets a fresh window, its turn
 * count from the entry, and a mark to steer by.
 *
 * The aim point is the actor's own mark raised a little, pushed along the
 * heading the actor faces; the heading itself comes from the sine table at the
 * facing angle, and what is left after the push becomes the direction the part
 * is handed to the mover with.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022AnimBlock */
struct AnimBlock {
    u16 nFlags;                  /* 0x00 */
    u8 pad02[0xa2];
    struct VecFx32 vecAt;        /* 0xa4 */
    int aEntryFlags[3];          /* 0xb0 */
};

/* Ov022SlotTail */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01;
    short nTag;                  /* 0x02 */
    u8 pad04[0x14];
    int nWindow;                 /* 0x18 */
    u8 pad1c[0xc];
    int nMark;                   /* 0x28 */
};

/* Ov022SlotPart */
struct SlotPart {
    int nTimer;                  /* 0x000 */
    struct VecFx32 vecPos;       /* 0x004 */
    struct VecFx32 vecVel;       /* 0x010 */
    struct AnimBlock anim;       /* 0x01c */
    u8 pad0d8[0x70];
    void *pOwner;                /* 0x148 */
    u8 nState;                   /* 0x14c */
    u8 pad14d[3];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001 */
    u8 pad002[0x116];
    struct SlotTail tail;        /* 0x118 */
    u8 pad144[0x24];
    struct SlotPart *pParts;     /* 0x168 */
    u8 pad16c[8];
    s8 nTurns;                   /* 0x174 */
    u8 pad175[3];
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
};

struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x020 */
    u8 pad024[0x468];
    struct VecFx32 vecMark;      /* 0x48c */
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

/* Two signed halfwords per angle step: the sine first, then the cosine. */
extern short data_0203d210[];

extern void func_ov022_0208b848(struct ReactionCtx *pCtx, void *pRow,
                                int nArg2, int nArg3);
extern void VEC_MultAdd(int nScale, struct VecFx32 *pA, struct VecFx32 *pB,
                        struct VecFx32 *pOut);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);

#define AIM_WINDOW 0x5a000
#define AIM_MARK 0xc000
#define AIM_RISE 0xc00
#define AIM_PUSH 0x800

#define PART_WAITING 1
#define PART_FLYING 2

void func_ov022_0208c420(struct ReactionCtx *pCtx, int nUnused, int nArg2,
                         int nArg3)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDir;
    struct ActorSlot *pSlot;
    struct Actor *pActor;
    int nPart;
    struct SlotTail *pTail;
    int nIndex;
    int nAngle;
    struct SlotPart *pWalk;
    struct SlotPart *pBase;
    int nCount;
    struct SlotPart *pPart;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pTail = &pSlot->tail;
    func_ov022_0208b848(pCtx, (int *)pCtx + pCtx->nSlot, nArg2, nArg3);
    pPart = 0;
    nCount = pSlot->nParts;
    nPart = 0;
    if (nCount > 0) {
        pBase = pSlot->pParts;
        pWalk = pBase;
        do {
            if (pWalk->nState == PART_WAITING) {
                pPart = &pBase[nPart];
                break;
            }
            nPart++;
            pWalk++;
        } while (nPart < nCount);
    }
    pTail->nWindow = AIM_WINDOW;
    pTail->nTag = pSlot->nTurns;
    pTail->nMark = AIM_MARK;
    pPart->nState = PART_FLYING;
    pActor = pCtx->pActor;
    nAngle = pActor->pNode->nAngle;
    vecAt = pActor->vecMark;
    nIndex = (u16)(nAngle - 0x8000) >> 4;
    vecAt.y = vecAt.y + AIM_RISE;
    vecDir.x = data_0203d210[nIndex * 2];
    vecDir.y = 0;
    vecDir.z = data_0203d210[nIndex * 2 + 1];
    VEC_MultAdd(AIM_PUSH, &vecDir, &vecAt, &vecAt);
    VEC_Subtract(&pPart->anim.vecAt, &vecAt, &vecDir);
    func_ov022_0208b400(pCtx, pPart, &vecAt, &vecDir);
}
