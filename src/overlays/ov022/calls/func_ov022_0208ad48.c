/* ov022: step one part of a reaction, aiming it before it is moved.
 *
 * Where the part is aimed depends on whether it has run at all yet. On its very
 * first step it is aimed at a point in front of the actor: the actor's facing is
 * turned into a table index, the sine and cosine there become a horizontal unit
 * step, and that step is walked one unit out from the actor's live position
 * raised by a fixed amount. On every step after that the part is aimed along its
 * own velocity, normalised, from where it already is.
 *
 * Either way the mover is handed the point and the aim and does the rest. One
 * owner state opts out of being aimed and moved at all, and only advances the
 * clock.
 *
 * The clock runs afterwards. Once it passes the owner's part delay, a part still
 * in the delayed state is restarted at zero in the running one. The animation is
 * stepped last, whatever happened.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

#define KIND_UNAIMED 0x19
#define ANGLE_BIAS 0x8000
#define ANGLE_SHIFT 4
#define AIM_RAISE 0xc00
#define AIM_REACH 0x800
#define PART_DELAYED 1
#define PART_RUNNING 2

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022AnimBlock */
struct AnimBlock {
    u8 pad00[0xa4];
    struct VecFx32 vecAt;        /* 0x00a4 */
    int aEntryFlags[3];          /* 0x00b0 */
};

/* Ov022SlotTail -- the owning slot's tail block, at slot+0x118 */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01[0x23];
    int nPartDelay;              /* 0x24 */
};

/* Ov022SlotPart */
struct SlotPart {
    int nTimer;                  /* 0x0000 */
    struct VecFx32 vecPos;       /* 0x0004 */
    struct VecFx32 vecVel;       /* 0x0010 */
    struct AnimBlock anim;       /* 0x001c */
    u8 pad0d8[0x70];
    struct SlotTail *pOwner;     /* 0x0148 */
    u8 nState;                   /* 0x014c */
    u8 pad14d[3];
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
    u8 pad82[2];
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad024[0x468];
    struct VecFx32 vecPos;       /* 0x048c */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0x58];
    struct Actor *pActor;        /* 0x58 */
};

/* kFxSinCosTable, 512 entries of a sine and a cosine; the ROM walks it as one
 * flat array of halfwords rather than as pairs, so the index is doubled here
 * the same way. */
extern s16 data_0203d210[];

extern int func_ov022_02090978(struct ReactionCtx *pCtx, int nKind);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern int func_01ff8d18(struct VecFx32 *pSrc, struct VecFx32 *pDst);
extern void func_0202a818(struct AnimBlock *pAnim, int nDelta);
extern void VEC_MultAdd(int nFactor, struct VecFx32 *pStep,
                        struct VecFx32 *pFrom, struct VecFx32 *pOut);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);

int func_ov022_0208ad48(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecAim;
    struct SlotTail *pOwner;
    struct Actor *pActor;
    int nIndex;
    int bLapsed;

    pOwner = pPart->pOwner;
    bLapsed = 0;
    if (func_ov022_02090978(pCtx, pOwner->nState) != KIND_UNAIMED) {
        if (pPart->nTimer == 0) {
            pActor = pCtx->pActor;
            nIndex = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) >> ANGLE_SHIFT;
            vecAt = pActor->vecPos;
            vecAt.y = vecAt.y + AIM_RAISE;
            vecAim.x = data_0203d210[nIndex * 2];
            vecAim.y = 0;
            vecAim.z = data_0203d210[nIndex * 2 + 1];
            VEC_MultAdd(AIM_REACH, &vecAim, &vecAt, &vecAt);
            VEC_Subtract(&pPart->anim.vecAt, &vecAt, &vecAim);
        } else {
            vecAt = pPart->anim.vecAt;
            func_01ff8d18(&pPart->vecVel, &vecAim);
        }
        func_ov022_0208b400(pCtx, pPart, &vecAt, &vecAim);
    }
    pPart->nTimer = pPart->nTimer + nDelta;
    if (pPart->nTimer >= pOwner->nPartDelay) {
        bLapsed = 1;
    }
    if (bLapsed != 0) {
        if (pPart->nState == PART_DELAYED) {
            pPart->nTimer = 0;
            pPart->nState = PART_RUNNING;
        }
    }
    func_0202a818(&pPart->anim, nDelta);
    return 0;
}
